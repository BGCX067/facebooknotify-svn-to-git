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

#ifndef FBNKERNEL_H
#define FBNKERNEL_H

#include <QtCore>

#include "facebook.h"
#include "FBNUrlBuilder.h"
#include "FBNHttp.h"
#include "../core/FBNLogger.h"
#include "../core/FBNServices.h"

class FBNKernel : public QObject
{

	Q_OBJECT

public:

	enum LoginState
	{
		notLoggedIn,
		waiting,
		loggedIn
	};

	enum CurrentAction
	{
		none,
		authCreateToken,
		authGetSession,
		eventsGetInWindow,
		friendsGet,
		friendsGetAppUsers,
		friendsGetTyped,
		friendsAreFriends,
		messagesGetCount,
		photosGetAlbums,
		photosGetCommentCount,
		photosGetFromAlbum,
		photosGetOfUser,
		pokesGetCount,
		sessionPing,
		userGetInfo,
		wallGetCount
	};

	FBNKernel(FBNLogger *log, FBNServices *services, FBNUrlBuilder *url);
	~FBNKernel(void);

	void startLogin();
	void getSession();

	void getMessagesCount();
	void getPokesCount();
	void getWallCount(const QString &userId = "");
	void getUserProfile(const QString &userId = "", facebook::UserDetailFields::UserDetailFields requested = facebook::UserDetailFields::all);

signals:
	void errorThrown(const facebook::ErrorData &errorData);
	void errorThrown(const QString &error);

	void messagesCountReady(const facebook::MessageCount &messages);
	void wallCountReady(const facebook::UserInfo &info);
	void pokeCountReady(const facebook::PokeCount &pokes);
	void userProfileReady(const facebook::UserInfo &info);


protected slots:
	void httpReady(const QString &response);
	void httpError(const CURLcode &result, const QString &response);

protected:

	FBNLogger * log;
	FBNServices * services;
	FBNUrlBuilder * urlBuilder;
	FBNHttp * http;

	facebook::Auth auth;
	facebook::Error error;
	//facebook::Events events;
	//facebook::Friends friends;
	facebook::Messages messages;
	//facebook::Photos photos;
	facebook::Pokes pokes;
	facebook::Users users;

	LoginState loginState;
	quint64 callId;
	CurrentAction currentAction;

	void callFacebookFunction(const QString &method, QHash<QString, QString> params, bool https = false, bool useCallId = true);
	void requestComplete(const QString &xml);
	QString makeSignature(const QHash<QString, QString> &values);

	void launchLogin();

#define RESTHTTPADDRESS "http://api.facebook.com/restserver.php"
#define RESTHTTPSADDRESS "https://api.facebook.com/restserver.php"
#define LOGINHTTPADDRESS "http://api.facebook.com/login.php"

// NON-PRODUCTION API KEY AND SECRET - REMOVE FOR RELEASE BUILDS
#define APIKEY "f2b47684f2a1742d8a408c46a87e392b"
#define SECRET "09da2fbf9ed041c20eb82b8203b1c774"

};

#endif
