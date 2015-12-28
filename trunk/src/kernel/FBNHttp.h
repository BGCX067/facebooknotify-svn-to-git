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

#ifndef FBNHTTP_H
#define FBNHTTP_H

#include <QtCore>
#include <String>
#include <curl/curl.h>

#include "../core/FBNLogger.h"

class FBNHttp : public QObject
{

	Q_OBJECT

public:
	FBNHttp(FBNLogger *log = 0);
	~FBNHttp(void);

	QString buildQueryString(const QHash<QString, QString> &pairs, bool insertMark = false);

	void post(const QUrl &url, const QString &values);
	void post(const QUrl &url, const QHash<QString, QString> &values);
	void post(const QString &url, const QString &values);
	void post(const QString &url, const QHash<QString, QString> &values);

	void get(const QUrl &url, const QString &values = "");
	void get(const QUrl &url, const QHash<QString, QString> &values);
	void get(const QString &url, const QString &values = "");
	void get(const QString &url, const QHash<QString, QString> &values);

signals:
	void responseReady(const QString &response);
	void responseError(int result, const QString &response);

protected:
	FBNLogger * log;

	CURLcode curlResult;
	CURL * handle;
	std::string response;
	void doCurl(const std::string &url, const std::string &values = "", bool doHttpPost = false);
	static int writeCallback(char *data, size_t size, size_t nmemb, std::string *buffer);

};

#endif
