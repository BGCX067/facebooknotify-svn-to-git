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

#include "FBNKernel.h"

FBNKernel::FBNKernel(FBNLogger * logger, FBNServices * services, FBNUrlBuilder * url)
{
	this->log = logger;
	this->services = services;
	this->urlBuilder = url;

	this->http = new FBNHttp(this->log);
	this->connect(http, SIGNAL(responseReady(QString)), this, SLOT(httpReady(QString)));
	this->connect(http, SIGNAL(responseError(CURLcode, QString)), this, SLOT(httpError(CURLcode, QString)));

	this->loginState = notLoggedIn;
	this->callId = 1;
	
	error = facebook::Error(log);

	auth.setSessionSecret(SECRET);
}
	
FBNKernel::~FBNKernel(void)
{
	delete this->http;
}

void FBNKernel::startLogin()
{
	if (loginState == notLoggedIn)
	{
		currentAction = authCreateToken;
		loginState = waiting;
		QHash<QString, QString> h;
		callFacebookFunction("facebook.auth.createToken", h);
	}
	else if (loginState == waiting)
		launchLogin();
}
void FBNKernel::launchLogin()
{
	if (loginState == waiting)
	{
		QString url = this->urlBuilder->buildLoginUrl(APIKEY, auth.authToken());
		this->services->openWebBrowser(url);
		getSession();
	}
}
void FBNKernel::httpReady(const QString &response)
{
	requestComplete(response);
}
void FBNKernel::httpError(const CURLcode &result, const QString &response)
{
	this->log->writeData("response error", response);
}

void FBNKernel::callFacebookFunction(const QString &method, QHash<QString, QString> params, bool https, bool useCallId)
{

	params.insert("method", method);
	params.insert("api_key", APIKEY);

	if (auth.session().sessionKey.length() > 0)
		params.insert("session_key", auth.session().sessionKey);

	if (auth.authToken().length() > 0)
		params.insert("auth_token", auth.authToken());

	QString callIdStr;
	callIdStr.setNum(callId);
	params.insert("call_id", callIdStr);
	callId++;

	QString sig = makeSignature(params);
	params.insert("sig", sig);

	this->http->post(this->urlBuilder->getPostUrl(https), params);

}


void FBNKernel::requestComplete(const QString &xml)
{
	if (loginState == waiting)
	{
		try
		{
			switch (currentAction)
			{
				case authCreateToken:
					auth.getAuthToken(xml);
					launchLogin();
					break;
				case authGetSession:
					auth.getSession(xml);
					loginState = loggedIn;
					break;
				default:
					currentAction = none;
			}
		}
		catch (bool val)
		{
			emit errorThrown("XML cannot be parsed");
		}
		catch (const QString &val)
		{
			error.getError(val);
			emit errorThrown(error.error());
		}
	}
	else if (loginState == loggedIn)
	{
		try
		{
			switch (currentAction)
			{
				case messagesGetCount:
					emit messagesCountReady(messages.getCount(xml));
					break;
				case pokesGetCount:
					emit pokeCountReady(pokes.getCount(xml));
					break;
				case userGetInfo:
					emit userProfileReady(users.getUserInfo(xml));
					break;
				case wallGetCount:
					emit wallCountReady(users.getUserInfo(xml));
					break;
				default:
					currentAction = none;
			}
		}
		catch (bool val)
		{
			emit errorThrown("XML cannot be parsed");
		}
		catch (const QString &val)
		{
			error.getError(val);
			emit errorThrown(error.error());
		}
		currentAction = none;
	}
}

QString FBNKernel::makeSignature(const QHash<QString, QString> &values)
{
	QString retval = "";
	QList<QString> keys = values.uniqueKeys();
	qSort(keys.begin(), keys.end());
	for (int i = 0; i < keys.size(); i++)
	{
		retval += keys[i] + "=";
		retval += values.value(keys[i]);
	}
	retval += auth.session().secret;
	return this->services->generateMD5Hash(retval);
}

void FBNKernel::getMessagesCount()
{
	currentAction = messagesGetCount;
	QHash<QString, QString> values;
	callFacebookFunction("facebook.messages.getCount", values, true);
}
void FBNKernel::getPokesCount()
{
	currentAction = pokesGetCount;
	QHash<QString, QString> values;
	callFacebookFunction("facebook.pokes.getCount", values, true);
}
void FBNKernel::getUserProfile(const QString &userId, facebook::UserDetailFields::UserDetailFields requested)
{
	currentAction = userGetInfo;
	QHash<QString, QString> values;
	
	if (userId.size())
		values.insert("users", userId);
	else
		values.insert("users", auth.session().userId);

	values.insert("fields", facebook::UserDetailFields::toString(requested));

	callFacebookFunction("facebook.users.getInfo", values, true);
}
void FBNKernel::getWallCount(const QString &userId)
{
	currentAction = wallGetCount;
	QHash<QString, QString> values;
	
	if (userId.size())
		values.insert("users", userId);
	else
		values.insert("users", auth.session().userId);

	values.insert("fields", facebook::UserDetailFields::toString(facebook::UserDetailFields::wallCount));

	callFacebookFunction("facebook.users.getInfo", values, true);
}


void FBNKernel::getSession()
{
	if (loginState == waiting)
	{
		currentAction = authGetSession;
		QHash<QString, QString> values;
		callFacebookFunction("facebook.auth.getSession", values, true, false);
	}

}