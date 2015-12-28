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

#ifndef FACEBOOK_FRIENDS_H
#define FACEBOOK_FRIENDS_H

#include <QString>
#include <QDomDocument>

#include "FBNKernelStructs.h"

namespace facebook
{
	class Friends
	{
	public:
		Friends();
		~Friends();

		const facebook::FriendsVector & appUsers();
		const facebook::FriendsVector & getAppUsers(const QString &xml);
		void setAppUsers(const facebook::FriendsVector &appUsers);

		const facebook::FriendsVector & friends();
		const facebook::FriendsVector & getFriends(const QString &xml);
		void setFriends(const facebook::FriendsVector &friends);

		const facebook::FriendsVector & requests();
		const facebook::FriendsVector & getRequests(const QString &xml);
		void setRequests(const facebook::FriendsVector &requests);

		const facebook::FriendsVector & typedFriends();
		const facebook::FriendsVector & getTypedFriends(const QString &xml);
		void setTypedFriends(const facebook::FriendsVector &typedFriends);

	protected:
		facebook::FriendsVector _appUsers;
		facebook::FriendsVector _friends;
		facebook::FriendsVector _requests;
		facebook::FriendsVector _typedFriends;

		facebook::FriendsVector getFriendsVector(const QString &xml, const QString &method);

	};
};
#endif
