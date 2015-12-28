//	fbNotify: A Facebook notification system.
//	Copyright (C) 2006 fbNotify Team.
//
//	This program is free software, you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 2 of the License, or
//	(at your option) any later version.
//
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY, without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License along
//	with this program, if not, write to the Free Software Foundation, Inc.,
//	51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

#ifndef FBNKERNELENUMS_H
#define FBNKERNELENUMS_H

#include <QString>
#include <QtCore>
#include <QtXml>

namespace facebook
{
	namespace UserNetworkType
	{
		enum UserNetworkType  // user.getInfo.affiliations.affiliations_elt.type
		{
			unspecified = 0,
			collegeNetwork = 1,
			highSchoolNetwork = 2,
			workNetwork = 3,
			geographicNetwork = 4
		};

		UserNetworkType fromDomElement(const QDomElement &val);
	};

	namespace Gender
	{
		enum Gender  // m or f
		{
			unspecified		= 0,
			male			= 1 << 0,
			female			= 1 << 1
		};
		Gender operator|(Gender lhs, Gender rhs);
		Gender operator|=(Gender &lhs, Gender rhs);
		Gender fromString(const QString &val);
		Gender fromDomElement(const QDomElement &val);	
	};

	namespace LookingFor
	{
		enum LookingFor
		{
			unspecified		= 0,
			friendship		= 1 << 0,
			dating			= 1 << 1,
			relationship	= 1 << 2,
			randomPlay		= 1 << 3,
			whateverICanGet = 1 << 4
		};

		LookingFor operator|(LookingFor lhs, LookingFor rhs);
		LookingFor operator|=(LookingFor &lhs, LookingFor rhs);
		LookingFor fromDomElement(const QDomElement &val);
	};

	namespace RelationshipStatus
	{
		enum RelationshipStatus
		{
			unspecified = 0,
			single = 1,
			inARelationship = 2,
			inAnOpenRelationship = 3,
			engaged = 4,
			married = 5,
			itsComplicated = 6
		};

		RelationshipStatus fromDomElement(const QDomElement &val);
	};

	namespace PoliticalView
	{
		enum PoliticalView
		{
			unspecified = 0,
			veryLiberal = 1,
			liberal = 2,
			moderate = 3,
			conservative = 4,
			veryConservative = 5,
			apathetic = 6,
			liberation = 7,
			other = 8
		};

		PoliticalView fromDomElement(const QDomElement &val);
	};

	namespace SocialLink
	{
		enum SocialLink
		{
			unspecified		= 0,
			lived			= 1 << 0,
			worked			= 1 << 1,
			clubOrGroup 	= 1 << 2,
			course			= 1 << 3,
			highSchool		= 1 << 4,
			traveled 		= 1 << 5,
			family 			= 1 << 6,
			thruFriend 		= 1 << 7,
			thruFacebook 	= 1 << 8,
			metRandom		= 1 << 9,
			hookup			= 1 << 10,
			dated			= 1 << 11,
			dontknow		= 1 << 12
		};

		SocialLink operator|(SocialLink lhs, SocialLink rhs);
		SocialLink operator|=(SocialLink &lhs, SocialLink rhs);
		SocialLink fromString(const QString &val);
		SocialLink fromXml(const QDomElement &val);
	};

	namespace ErrorCodes
	{
		enum ErrorCodes  // Error codes
		{
			noError = 0,
			unknown = 1,
			service = 2,
			tooManyCalls = 4,
			badIp = 5,
			badParam = 100,
			badApiKey = 101,
			badSessionKey = 102,
			badCallId = 103,
			badSignature = 104,
			badUserId = 110,
			badUserField = 111,
			badUserSocialField = 112,
			userPermissionDenied = 210,
			albumPermissionDenied = 220,
			photoPermissionDenied = 221
		};

		QString toString(ErrorCodes error);
	};

	namespace UserDetailFields
	{
		typedef quint64 UserDetailFields;
		
		const UserDetailFields none					= 0;
		const UserDetailFields aboutMe				= 1 << 0;
		const UserDetailFields affiliations			= 1 << 1;
		const UserDetailFields birthday				= 1 << 2;
		const UserDetailFields favoriteBooks		= 1 << 3;
		const UserDetailFields activities			= 1 << 4;
		const UserDetailFields currentLocation		= 1 << 5;
		const UserDetailFields firstName			= 1 << 6;
		const UserDetailFields gender				= 1 << 7;
		const UserDetailFields hometownLocation		= 1 << 8;
		const UserDetailFields highSchools			= 1 << 9;
		const UserDetailFields intrests				= 1 << 10;
		const UserDetailFields lastName				= 1 << 11;
		const UserDetailFields lookingFor			= 1 << 12;
		const UserDetailFields intrestedIn			= 1 << 13;
		const UserDetailFields favoriteMovies		= 1 << 14;
		const UserDetailFields favoriteMusic		= 1 << 15;
		const UserDetailFields name					= 1 << 16;
		const UserDetailFields notesCount			= 1 << 17;
		const UserDetailFields politicalViews		= 1 << 18;
		const UserDetailFields pictureUrl			= 1 << 19;
		const UserDetailFields profileUpdateTime	= 1 << 20;
		const UserDetailFields favoriteQuotes		= 1 << 21;
		const UserDetailFields relationshipStatus	= 1 << 22;
		const UserDetailFields religiousViews		= 1 << 23;
		const UserDetailFields schools				= 1 << 24;
		const UserDetailFields significantOtherId	= 1 << 25;
		const UserDetailFields status				= 1 << 26;
		const UserDetailFields timezone				= 1 << 27;
		const UserDetailFields favoriteTVShows		= 1 << 28;
		const UserDetailFields wallCount			= 1 << 29;
		const UserDetailFields workHistory			= 1 << 30;
		const UserDetailFields all					= Q_UINT64_C(0xFFFFFFFFFFFFFFFF);
		
		QString toString(UserDetailFields details);

	};
}

#endif
