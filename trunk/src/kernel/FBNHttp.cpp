//	fbNotify: A Facebook notification system.
//	Copyright (C) 2006 fbNotify Team.
//
//	This program is free software; you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation; either version 2 of the License, or
//	(at your option) any later version.
//
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License along
//	with this program; if not, write to the Free Software Foundation, Inc.,
//	51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

#include "FBNHttp.h"

FBNHttp::FBNHttp(FBNLogger *logger)
{
	this->log = logger;

#ifndef QT_NO_DEBUG
	log->writeLine("fbNotify Http Class created");
#endif

	curlResult = curl_global_init(CURL_GLOBAL_ALL);
	if (curlResult != 0)
	{
		if (this->log)
			this->log->writeData("cUrl global init failure", curlResult);
		throw false;
	}
	handle = curl_easy_init();
	if (handle == 0)
	{
		if (this->log)
			this->log->writeData("cUrl easy init failure", handle);
		throw false;
	}
}

FBNHttp::~FBNHttp()
{
	curl_easy_cleanup(handle);
	curl_global_cleanup();
#ifndef QT_NO_DEBUG
	log->writeLine("fbNotify Http Class destroyed");
#endif
}

QString FBNHttp::buildQueryString(const QHash<QString, QString> &pairs, bool insertMark)
{
	QString retval;
	if (insertMark)
		retval = "?";
	QList<QString> keys = pairs.uniqueKeys();
	qSort(keys.begin(), keys.end());
	for (int i = 0; i < keys.size(); i++)
	{
		if (i > 0)
			retval += "&";
		retval += keys[i] + "=";
		retval += pairs.value(keys[i]);
	}
	return retval;
}
void FBNHttp::post(const QUrl &url, const QString &values)
{
	doCurl(url.toString().toStdString(), values.toStdString(), true);
}
void FBNHttp::post(const QUrl &url, const QHash<QString, QString> &values)
{
	post(url, buildQueryString(values));
}
void FBNHttp::post(const QString &url, const QString &values)
{
	QUrl newurl(url);
	post(newurl, values);
}
void FBNHttp::post(const QString &url, const QHash<QString, QString> &values)
{
	QUrl newurl(url);
	post(newurl, buildQueryString(values));
}

void FBNHttp::get(const QUrl &url, const QString &values)
{
	doCurl(url.toString().toStdString(), values.toStdString());
}
void FBNHttp::get(const QUrl &url, const QHash<QString, QString> &values)
{
	get(url, buildQueryString(values, true));
}
void FBNHttp::get(const QString &url, const QString &values)
{
	QUrl newurl(url);
	get(newurl, values);
}
void FBNHttp::get(const QString &url, const QHash<QString, QString> &values)
{
	QUrl newurl(url);
	get(newurl, buildQueryString(values, true));
}


void FBNHttp::doCurl(const std::string &url, const std::string &values, bool doHttpPost)
{

#ifndef QT_NO_DEBUG
	log->enter("doCurl()");
#endif

	curl_easy_reset(handle);
#ifndef QT_NO_DEBUG
	log->writeLine("cUrl handle reset");
#endif


	curl_easy_setopt(handle, CURLOPT_URL, url.c_str());

	if (doHttpPost)
	{
		curl_easy_setopt(handle, CURLOPT_POST, true);
		curl_easy_setopt(handle, CURLOPT_POSTFIELDS, values.c_str());
	}
	else if (values.size())
	{
		std::string newurl = url;
		newurl.append(values);
		curl_easy_setopt(handle, CURLOPT_URL, newurl.c_str());
	}
		
	curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, FBNHttp::writeCallback);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, &response);
	curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, false); 

#ifndef QT_NO_DEBUG
	log->writeLine("cUrl options set");
#endif

	response = "";

	curlResult = curl_easy_perform(handle);
#ifndef QT_NO_DEBUG
	log->writeLine("cUrl request peformed");
#endif

	if (!curlResult)
		emit responseReady(response.c_str());
	else
	{	
		emit responseError(curlResult, "");
#ifndef QT_NO_DEBUG
		this->log->writeData("cUrl Error", (int)curlResult);	
#endif
	}
#ifndef QT_NO_DEBUG
	log->leave("doCurl()");
#endif
}
int FBNHttp::writeCallback(char *data, size_t size, size_t nmemb, std::string *buffer)
{
  int result = 0;
  if (buffer != NULL)
  {
    buffer->append(data, size * nmemb);
    result = size * nmemb;
  }
  return result;
}
