#include "FBNotificationThread.h"


FBNotificationThread::FBNotificationThread(Logger * log)
{
	log->enter("FBNotificationThread::FBNotificationThread()");

	this->log = log;
	
	this->maxGetSessionAttempts = 10;

	this->active = true;
	this->kernel  = new FBNotifyKernel(this->log);

	this->api_key = QString("b53e6b61a1d7da92147d46c61d31f45c");
	this->secret = QString("d6473c52ded5d1ffbec8398815f4f90e");

	log->leave("FBNotificationThread::FBNotificationThread()");
	

}

FBNotificationThread::~FBNotificationThread(void)
{
	log->enter("FBNotificationThread::~FBNotificationThread()");
	log->leave("FBNotificationThread::~FBNotificationThread()");

}

bool FBNotificationThread::login()
{
	bool success = true;
	

	if(success)
	{
		if(!this->kernel->auth_createToken(this->api_key, this->secret,  this->auth_token))
		{
			success = false;
		}
	}


	if(success)
	{
		this->browserLogin(this->api_key , this->auth_token);
	}

	if(success)
	{
		int tries = 0;

		success = false;

		while(tries < this->maxGetSessionAttempts || success)
		{
			if(this->kernel->auth_getSession(this->api_key, this->secret, this->auth_token, this->session_key, this->uid, this->secret))
			{
				success = true;
			}
			else
			{
				tries++;
			}

			this->sleep(2);
		}

	}

	return success;

}


void FBNotificationThread::browserLogin(QString key, QString token)
{
    //QProcess process(QString("C:\\Program Files\\Internet Explorer\\IEXPLORE.EXE"));
    //process.addArgument("c:\\qt\\3.3.4\\doc\\html\\qpushbutton.html");

}


void FBNotificationThread::run(void)
{
	log->enter("FBNotificationThread::run()");

	while(true)
	{	
		QString s;
		
		qDebug("auth_token...");
	
		bool success = this->kernel->auth_createToken(this->api_key, this->secret,  this->auth_token);

		qDebug(auth_token.toAscii());

		if(success) qDebug("successfully retrieved content...\n\n");

		sleep(1);

		int k = 0;

		while(k < 100)
		{

			qDebug("get_session...");
		
			success = this->kernel->auth_getSession(this->api_key, this->secret,  this->auth_token, this->session_key, this->uid , this->session_secret);

			qDebug(session_key.toAscii());
			if(success) qDebug("successfully session...\n\n");
			pollPause();
			
			sleep(1);
			k++;
		}

		pollPause();


	}

	log->leave("FBNotificationThread::run()");

	
}

void FBNotificationThread::pollPause()
{

		while(!this->active)
		{
			sleep(1);
		}	
}