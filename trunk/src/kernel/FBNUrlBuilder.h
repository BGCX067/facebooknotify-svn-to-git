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

#ifndef FBNURLBUILDER_H
#define FBNURLBUILDER_H

#include <QtCore>
#include "FBNKernelStructs.h"


#define URL_RESTSERVER "http://api.facebook.com/restserver.php"
#define URL_RESTSERVER_HTTPS "https://api.facebook.com/restserver.php"

#define URL_LOGIN "http://api.facebook.com/login.php?api_key=%APIKEY%&auth_token=%AUTHTOKEN%"

#define URL_MESSAGE "http://www.facebook.com/message.php?uid=%UID%&api_key=%APIKEY%&subject=%SUBJECT%&msg=%MSG%"

#define URL_PROFILE "http://www.facebook.com/profile.php?uid=%UID%&api_key=%APIKEY%"
#define URL_POKE "http://www.facebook.com/poke.php?uid=%UID%&api_key=%APIKEY%"
#define URL_ADDFRIEND "http://www.facebook.com/addfriend.php?uid=%UID%&api_key=%APIKEY%"
#define URL_PHOTOS "http://www.facebook.com/photos.php?uid=%UID%&api_key=%APIKEY%"
#define URL_PHOTO_SEARCH "http://www.facebook.com/photo_search.php?uid=%UID%&api_key=%APIKEY%"
#define URL_WALLPOST "http://www.facebook.com/wallpost.php?uid=%UID%&api_key=%APIKEY%"

class FBNUrlBuilder : public QObject
{

	Q_OBJECT

public:

	enum urltype
	{
		profile,
		poke,
		addFriend,
		photos,
		photoSearch,
		wallPost
	};

	FBNUrlBuilder();
	~FBNUrlBuilder();

	QString getPostUrl(bool https = false);
	QString buildLoginUrl(const QString &apiKey, const QString &authToken);
	QString buildStandardUrl(const urltype urlType, const QString &userId, const QString &apiKey);
	QString buildSendMessageUrl(const QString &userId, const QString &apiKey, const QString &subject, const QString &message);


};

#endif
