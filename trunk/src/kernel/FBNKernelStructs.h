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

#ifndef FBNKERNELSTRUCTS_H
#define FBNKERNELSTRUCTS_H

#include <QtCore>
#include <QtXml>

#include "FBNKernelEnums.h"

namespace facebook
{
	typedef QVector<QString> FriendsVector;
	typedef QString AuthToken;			// auth.createToken
	typedef unsigned int WallCount;		//wall.getCount

	struct Session  // auth.getSession
	{
		QString sessionKey;
		QString userId;
		QString secret;
	};

	struct Event  // events.getInWindow
	{
		QString name;
		QString ownerId;
		QDateTime startTime;
		QDateTime endTime;
		QString attending;
	};

	struct MessageCount  //messages.getCount
	{
		int unread;
		int total;
		QDateTime mostRecent;

		friend bool operator< (const MessageCount &lhs, const MessageCount &rhs);
		friend bool operator> (const MessageCount &lhs, const MessageCount &rhs);
		friend bool operator== (const MessageCount &lhs, const MessageCount &rhs);
		friend bool operator<= (const MessageCount &lhs, const MessageCount &rhs);
		friend bool operator>= (const MessageCount &lhs, const MessageCount &rhs);
		friend bool operator!= (const MessageCount &lhs, const MessageCount &rhs);

	};

	struct PokeCount  //pokes.getCount
	{
		int unseen;
		int total;

		friend bool operator< (const PokeCount &lhs, const PokeCount &rhs);
		friend bool operator> (const PokeCount &lhs, const PokeCount &rhs);
		friend bool operator== (const PokeCount &lhs, const PokeCount &rhs);
		friend bool operator<= (const PokeCount &lhs, const PokeCount &rhs);
		friend bool operator>= (const PokeCount &lhs, const PokeCount &rhs);
		friend bool operator!= (const PokeCount &lhs, const PokeCount &rhs);

	};



	struct Photo  // photos.getAlbums - cover photo; photos.getFromAlbum
	{
		QString link;
		QString src;
		QString caption;
		QDateTime created;
		QString albumId;
	};

	struct PhotoAlbum  // photos.getAlbums
	{
		QString albumId;
		facebook::Photo coverPhoto;
		QString name;
		QDateTime created;
		QDateTime modified;
		QString description;
		QString location;
	};

	struct PhotoCommentCount  // photos.getCommentCount
	{
		int total;
	};

	struct UserAffiliation  // users.getInfo - affiliations
	{
		int year;
		QString status;
		facebook::UserNetworkType::UserNetworkType type;
		QString name;
		QString key;
	};

	struct SchoolInformation  // users.getInfo - hs_info, school_info
	{
		QString name;
		int year;
		QString key;
	};
	typedef QVector<facebook::SchoolInformation> SchoolVector;


	struct Location // users.getInfo - hometown_location, current_location
	{
		QString city;
		QString stateOrRegion;
		QString country;
	};

	struct WorkInformation
	{
		QString country;
		QString region;
		QString city;
		QString companyName;
		QString position;
		QString description;
		QDate startDate;
		QDate endDate;
	};

	struct UserStatus
	{
		QString message;
		QDateTime time;

		UserStatus(const QDomElement &element);
		UserStatus();
	};

	struct UserInfo
	{
		QString aboutMe;
		QVector<facebook::UserAffiliation> affiliations;
		QDate birthday;
		QString favoriteBooks;
		QString activities;
		facebook::Location currentLocation;
		QString firstName;
		facebook::Gender::Gender gender;
		facebook::Location hometownLocation;
		facebook::SchoolVector highSchools;
		QString intrests;
		QString lastName;
		facebook::LookingFor::LookingFor lookingFor;
		facebook::Gender::Gender intrestedIn;
		QString favoriteMovies;
		QString favoriteMusic;
		QString name;
		int notesCount;
		facebook::PoliticalView::PoliticalView politicalViews;
		QString pictureUrl;
		QDateTime profileUpdateTime;
		QString favoriteQuotes;
		facebook::RelationshipStatus::RelationshipStatus relationshipStatus;
		QString religiousViews;
		facebook::SchoolVector schools;
		QString significantOtherId;
		facebook::UserStatus status;
		int timezone;
		QString favoriteTVShows;
		facebook::WallCount wallCount;
		QVector<facebook::WorkInformation> workHistory;

		void loadHighSchoolsFromDomElement(const QDomElement &element);
		void loadSchoolsFromDomElement(const QDomElement &element);
	};

	struct ErrorData
	{
		QString methodCalled;
		facebook::ErrorCodes::ErrorCodes errorCode;
		QString message;
	};


}

struct QDomError
{
	QString message;
	int line;
	int column;
};

#endif
