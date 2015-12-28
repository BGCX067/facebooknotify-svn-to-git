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

#include "facebook.friends.h"

facebook::Friends::Friends()
{
}

facebook::Friends::~Friends()
{
}

facebook::FriendsVector facebook::Friends::getFriendsVector(const QString &xml, const QString &method)
{
	facebook::FriendsVector retval;
	
	QDomDocument doc;
	QDomError domError;
	if (!doc.setContent(xml, &(domError.message), &(domError.line), &(domError.column)))
		throw domError;

	QDomElement resultElement = doc.firstChildElement();
	if (resultElement.isNull() || 
	   (resultElement.nodeName() != "result") ||
	   (resultElement.attribute("method").toLower() != method.toLower()))
		throw xml;

	QDomElement element = resultElement.firstChildElement();
	while (!element.isNull())
	{
		if (element.nodeName().toLower() == "fb_error")
			throw xml;
		else if (element.nodeName().toLower() == "result_elt")
			retval.push_back(element.text());
		element = element.nextSiblingElement();
	}

	return retval;
}

const facebook::FriendsVector & facebook::Friends::appUsers()
{
	return _appUsers;
}
const facebook::FriendsVector & facebook::Friends::getAppUsers(const QString &xml)
{
	_appUsers = getFriendsVector(xml, "facebook.friends.getappusers");
	return _appUsers;
}
void facebook::Friends::setAppUsers(const facebook::FriendsVector &appUsers)
{
	_appUsers = appUsers;
}

const facebook::FriendsVector & facebook::Friends::friends()
{
	return _friends;
}
const facebook::FriendsVector & facebook::Friends::getFriends(const QString &xml)
{
	_friends = getFriendsVector(xml, "facebook.friends.get");
	return _friends;
}
void facebook::Friends::setFriends(const facebook::FriendsVector &friends)
{
	_friends = friends;
}

const facebook::FriendsVector & facebook::Friends::requests()
{
	return _requests;
}
const facebook::FriendsVector & facebook::Friends::getRequests(const QString &xml)
{
	_requests = getFriendsVector(xml, "facebook.friends.getrequests");
	return _requests;
}
void facebook::Friends::setRequests(const facebook::FriendsVector &requests)
{
	_requests = requests;
}

const facebook::FriendsVector & facebook::Friends::typedFriends()
{
	return _typedFriends;
}
const facebook::FriendsVector & facebook::Friends::getTypedFriends(const QString &xml)
{
	_typedFriends = getFriendsVector(xml, "facebook.friends.gettyped");
	return _typedFriends;
}
void facebook::Friends::setTypedFriends(const facebook::FriendsVector &typedFriends)
{
	_typedFriends = typedFriends;
}