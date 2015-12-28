#include "FBNotifyKernel.h"
#include <qurl.h>

QSemaphore FBNotifyKernel::static_semaphore;
CURL * FBNotifyKernel::curl = curl_easy_init( );;
CURLcode FBNotifyKernel::res;


FBNotifyKernel::FBNotifyKernel(Logger * log)
{
	log->enter("FBNotifyKernel::FBNotifyKernel");

	this->log = log;


	baseURL = QString("https://api.facebook.com/restserver.php");


	buffer = new QBuffer();
	buffer->open(QIODevice::ReadWrite);

	http = new QHttp();


	QObject::connect(http, SIGNAL(requestFinished(int, bool)), this, SLOT(handleRequest(int, bool)));
	
	log->leave("FBNotifyKernel::FBNotifyKernel");
}


FBNotifyKernel::~FBNotifyKernel(void)
{
	log->enter("FBNotifyKernel::~FBNotifyKernel()");
  
	log->leave("FBNotifyKernel::~FBNotifyKernel()");
}

void FBNotifyKernel::initCall()
{
	buffer->reset();
	current = -1;
	success = false;
	errorCode = -1;


}

bool FBNotifyKernel::get(const char * url, QString & content)
{
	log->enter("FBNotifyKernel::get()");

	initCall();

	QUrl * u = new QUrl(QString(url));

	http->setHost(u->host());


	current = http->get(u->path(), buffer);


	delete u;

	log->write("Acquiring semaphore...");
	semaphore.acquire();

	content = QString(buffer->readAll());

	log->leave("FBNotifyKernel::get()");

	return success;

}


bool FBNotifyKernel::post(const char * url, QString& fields, QString & content)
{
	log->enter("FBNotifyKernel::post()");

	initCall();

	QUrl * u = new QUrl(QString(url));

	http->setHost(u->host());

	QString data;


	data.append(fields);

	QByteArray ba(data.toUtf8());

	QHttpRequestHeader header;
	header.setRequest("POST", u->path());
	header.setValue("host", u->host());
	header.setValue("connection", "Keep-Alive");
	header.setValue("content-length", QString("%1").arg(data.length()));
	header.setValue("Content-Type", "application/x-www-form-urlencoded");

	

	current = http->request(header, ba, buffer);	

	delete u;

	log->write("Acquiring semaphore...");
	semaphore.acquire();

	content = QString(buffer->readAll());

	log->leave("FBNotifyKernel::post()");

	return success;
}

bool FBNotifyKernel::postHTTPS(const char * url, QString & data, QString & output)
{
	if(curl) {

		curl_easy_setopt(curl, CURLOPT_URL, url);

		#ifdef SKIP_PEER_VERIFICATION
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, FALSE);
		#endif

		#ifdef SKIP_HOSTNAME_VERFICATION
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
		#endif

		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.toStdString().c_str());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(data.toStdString().c_str()));
		curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, FBNotifyKernel::handleCurlWrite );
		curl_easy_setopt( curl, CURLOPT_WRITEDATA, &output );	

		res = curl_easy_perform(curl);

		qDebug(data.toAscii());
		qDebug("aquired lock");
		static_semaphore.acquire();

		return (FBNotifyKernel::res == 0);
	}
	else
	{
		
		return false;
	}
}

size_t FBNotifyKernel::handleCurlWrite( void *ptr, size_t size, size_t nmemb, void *userp )
{ 
	qDebug("release lock");
	string *str = (string *) userp;
	str->append( (char *) ptr, size*nmemb );
	return size*nmemb;
}


void FBNotifyKernel::handleRequest(int id, bool err)
{
	log->enter("FBNotifyKernel::handleRequest()");

	if(current == id)
	{
		if(!err)
		{
			buffer->reset();
			success = true;
		}
		else
		{
			success = false;
			errorCode = http->error();
			log->error("HTTP Error");
			
		}
		
		// critical that this semaphore be released!
		semaphore.release();
		log->write("Semaphore released...");
	}

	log->leave("FBNotifyKernel::handleRequest()");
	
}


bool FBNotifyKernel::auth_createToken(QString key, QString secret,  QString & token)
{
	log->enter("FBNotifyKernel::auth_createToken");

	QString data;
	QString cdata;

	data.append("api_key=").append(key);
	data.append("method=").append("facebook.auth.createToken");

	cdata.append("api_key=").append(key).append("&");
	cdata.append("method=").append("facebook.auth.createToken").append("&");


	QString sig;
	
	md5(data.append(secret), sig);
	cdata.append("sig=").append(sig);

	QString xml;

	bool success = post(baseURL.toStdString().c_str(), cdata, xml);

	if(success)
	{
	
		QDomDocument doc;
		doc.setContent(xml);

		QDomNodeList list = doc.elementsByTagName(QString("token"));

		if(list.length() == 1)
		{
			QDomNode n = list.item(0).childNodes().item(0);

			token = n.nodeValue();
		}
		else
		{
			success = false;
			log->error("API Error");
		}
	}
	
	log->leave("FBNotifyKernel::auth_createToken()");

	return success;
}

bool FBNotifyKernel::auth_getSession(QString key, QString secret, QString token, QString & session, QString & uid, QString & s_secret)
{

	QString data;
	QString cdata;

	data.append("api_key=").append(key);
	data.append("auth_token=").append(token);
	data.append("method=").append("facebook.auth.getSession");

	cdata.append("api_key=").append(key).append("&");
	cdata.append("auth_token=").append(token).append("&");
	cdata.append("method=").append("facebook.auth.getSession").append("&");

	
	QString sig;
	
	md5(data.append(secret), sig);
	cdata.append("sig=").append(sig);


	QString xml;

	bool success = post(baseURL.toStdString().c_str(), cdata, xml);	

	qDebug(xml.toAscii());

	if(success)
	{
		QDomDocument doc;
		doc.setContent(xml);

		QDomNodeList list = doc.elementsByTagName(QString("session_key"));

		if(list.length() == 1)
		{
			QDomNode n = list.item(0).childNodes().item(0);

			session = n.nodeValue();
		}
		else
		{
			success = false;
			log->error("API Error");
		}


		list = doc.elementsByTagName(QString("uid"));

		if(list.length() == 1)
		{
			QDomNode n = list.item(0).childNodes().item(0);

			uid = n.nodeValue();
		}
		else
		{
			success = false;
			log->error("API Error");
		}

		list = doc.elementsByTagName(QString("secret"));

		if(list.length() == 1)
		{
			QDomNode n = list.item(0).childNodes().item(0);

			secret = n.nodeValue();
		}
		else
		{
			success = false;
			log->error("API Error");
		}


	}

	return success;
}

void FBNotifyKernel::md5(QString text, QString& dig)
{
	std::string str = text.toStdString();

	md5_state_t state;
	md5_byte_t digest[16];
	char hex_output[16*2 + 1];
	int di;
	md5_init( &state );
	md5_append( &state, (const md5_byte_t *) str.c_str( ), (int) strlen( str.c_str( ) ) );
	md5_finish( &state, digest );
	for( di = 0; di < 16; ++di )
		sprintf( hex_output+di * 2, "%02x", digest[di] );
	dig = QString( hex_output );

}