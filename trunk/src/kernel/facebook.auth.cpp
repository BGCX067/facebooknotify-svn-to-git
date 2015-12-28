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

//  Abstracting this xml
//  <?xml version="1.0" encoding="UTF-8"?>
//	<result method="facebook.auth.createToken" type="struct">
//    <token>8bd7eb80aef3778f2478921787d7e911</token>
//  </result>
//  and also
//  <?xml version="1.0" encoding="UTF-8"?>
//  <result method="facebook.auth.getSession" type="struct">
//    <session_key>f480f33c7927939f49b761f1-iDnIuRVGi6TwnYvgP-9yvqA..</session_key>
//    <uid>i1eBQSkwz3UQ.</uid>
//    <secret>secret</secret>
//  </result>
//  along with
//  <?xml version="1.0" encoding="UTF-8"?>
//  <result method="facebook.sesion.ping">true</result>

#include "facebook.auth.h"

facebook::Auth::Auth()
{
}

facebook::Auth::~Auth()
{
}

facebook::AuthToken & facebook::Auth::authToken()
{
	return _authToken;
}
const facebook::AuthToken & facebook::Auth::getAuthToken(const QString &xml)
{
	facebook::AuthToken authToken;

	QDomDocument doc;
	QDomError domError;
	if (!doc.setContent(xml, &(domError.message), &(domError.line), &(domError.column)))
		throw domError;

	QDomElement resultElement = doc.firstChildElement();
	if (resultElement.isNull() || 
	   (resultElement.nodeName().toLower() != "result") ||
	   (resultElement.attribute("method").toLower() != "facebook.auth.createtoken"))
		throw xml;

	QDomElement element = resultElement.firstChildElement();
	while (!element.isNull())
	{
		if (element.nodeName().toLower() == "fb_error")
			throw xml;
		else if (element.nodeName().toLower() == "token")
			authToken = element.text();
		element = element.nextSiblingElement();
	}

	_authToken = authToken;
	return _authToken;
}
void facebook::Auth::setAuthToken(const facebook::AuthToken &authToken)
{
	_authToken = authToken;
}

facebook::Session & facebook::Auth::session()
{
	return _session;
}
const facebook::Session & facebook::Auth::getSession(const QString &xml)
{
	facebook::Session session;

	QDomDocument doc;
	QDomError domError;
	if (!doc.setContent(xml, &(domError.message), &(domError.line), &(domError.column)))
		throw domError;
	
	QDomElement resultElement = doc.firstChildElement();
	if (resultElement.isNull() || 
	   (resultElement.nodeName().toLower() != "result") ||
	   (resultElement.attribute("method").toLower() != "facebook.auth.getsession"))
		throw xml;

	QDomElement element = resultElement.firstChildElement();
	while (!element.isNull())
	{
		if (element.nodeName().toLower() == "fb_error")
			throw xml;
		else if (element.nodeName().toLower() == "session_key")
			session.sessionKey = element.text();
		else if (element.nodeName().toLower() == "uid")
			session.userId = element.text();
		else if ((element.nodeName().toLower() == "secret") && element.text().length() > 0)
			session.secret = element.text();
		element = element.nextSiblingElement();
	}
	_session = session;
	return _session;
}
void facebook::Auth::setSession(const facebook::Session &session)
{
	_session = session;
}
void facebook::Auth::setSessionSecret(const QString &secret)
{
	_session.secret = secret;
}

bool facebook::Auth::pingSession(const QString &xml)
{
	QDomDocument doc;
	QDomError domError;
	if (!doc.setContent(xml, &(domError.message), &(domError.line), &(domError.column)))
		throw domError;

	QDomElement resultElement = doc.firstChildElement();
	if ((resultElement.nodeName().toLower() == "result") &&
	   (resultElement.attribute("method").toLower() != "facebook.session.ping"))
		return (resultElement.text().toLower() == "true");

	return false;
}
