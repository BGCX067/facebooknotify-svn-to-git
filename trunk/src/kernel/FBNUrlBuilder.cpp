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

#include "FBNUrlBuilder.h"

FBNUrlBuilder::FBNUrlBuilder()
{
}

FBNUrlBuilder::~FBNUrlBuilder()
{
}


QString FBNUrlBuilder::getPostUrl(bool https)
{
	if (https)
		return URL_RESTSERVER_HTTPS;
	return URL_RESTSERVER;
}
QString FBNUrlBuilder::buildLoginUrl(const QString &apiKey, const QString &authToken)
{
	QString retval = URL_LOGIN;

	retval.replace("%APIKEY%", apiKey);
	retval.replace("%AUTHTOKEN%", authToken);

	return retval;
}
QString FBNUrlBuilder::buildStandardUrl(const urltype urlType, const QString &userId, const QString &apiKey)
{
	QString retval;
	switch (urlType)
	{
		case profile:
			retval = URL_PROFILE;
			break;
		case poke:
			retval = URL_POKE;
			break;
		case addFriend:
			retval = URL_ADDFRIEND;
			break;
		case photos:
			retval = URL_PHOTOS;
			break;
		case photoSearch:
			retval = URL_PHOTO_SEARCH;
			break;
		case wallPost:
			retval = URL_WALLPOST;
			break;
	}

	retval.replace("%UID%", userId);
	retval.replace("%APIKEY%", apiKey);

	return retval;
}
QString FBNUrlBuilder::buildSendMessageUrl(const QString &userId, const QString &apiKey, const QString &subject, const QString &message)
{
	QString retval = URL_MESSAGE;

	retval.replace("%UID%", userId);
	retval.replace("%APIKEY%", apiKey);
	retval.replace("%SUBJECT%", subject);
	retval.replace("%MSG%", message);

	return retval;
}