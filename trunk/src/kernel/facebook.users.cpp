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

#include "facebook.users.h"

facebook::Users::Users()
{
}

facebook::Users::~Users()
{
}

const facebook::UserInfo & facebook::Users::userInfo()
{
	return _userInfo;
}

const facebook::UserInfo & facebook::Users::getUserInfo(const QString &xml)
{
	facebook::UserInfo profile;

	QDomDocument doc;
	if (!doc.setContent(xml))
		throw false;

	QDomElement resultElement = doc.firstChildElement();
	if (resultElement.isNull() || 
	   (resultElement.nodeName().toLower() != "result") ||
	   (resultElement.attribute("method").toLower() != "facebook.users.getinfo"))
		throw xml;

	QDomElement element = resultElement.firstChildElement();
	while (!element.isNull())
	{
		if (element.nodeName().toLower() == "fb_error")
			throw xml;
		else if (element.nodeName().toLower() == "about_me")
			profile.aboutMe = element.text();
		else if (element.nodeName().toLower() == "affiliations")
			profile.affiliations;  // = facebook::UserAffiliationTyp;
		else if (element.nodeName().toLower() == "birthday")
			profile.birthday; //= element.text() to a QDate
		else if (element.nodeName().toLower() == "books")
			profile.favoriteBooks = element.text();
		else if (element.nodeName().toLower() == "clubs")
			profile.activities = element.text();
		else if (element.nodeName().toLower() == "current_location")
			profile.currentLocation; //= {some function call}
		else if (element.nodeName().toLower() == "first_name")
			profile.firstName = element.text();
		else if (element.nodeName().toLower() == "gender")
			profile.gender = facebook::Gender::fromDomElement(element);
		else if (element.nodeName().toLower() == "hometown_location")
			profile.hometownLocation; // some function call
		else if (element.nodeName().toLower() == "hs_info")
			profile.loadHighSchoolsFromDomElement(element);
		else if (element.nodeName().toLower() == "intrests")
			profile.intrests = element.text();
		else if (element.nodeName().toLower() == "last_name")
			profile.lastName = element.text();
		else if (element.nodeName().toLower() == "meeting_for")
			profile.lookingFor; // some function call
		else if (element.nodeName().toLower() == "meeting_sex")
			profile.intrestedIn = facebook::Gender::fromDomElement(element);
		else if (element.nodeName().toLower() == "movies")
			profile.favoriteMovies = element.text();
		else if (element.nodeName().toLower() == "music")
			profile.favoriteMusic = element.text();
		else if (element.nodeName().toLower() == "name")
			profile.name = element.text();
		else if (element.nodeName().toLower() == "notes_count")
			profile.notesCount = element.text().toInt();
		else if (element.nodeName().toLower() == "intrests")
			profile.politicalViews; // some function call
		else if (element.nodeName().toLower() == "pic")
			profile.pictureUrl = element.text();
		else if (element.nodeName().toLower() == "profile_update_time")
			profile.profileUpdateTime.setTime_t(element.text().toInt()); // some function call= element.text().toInt();
		else if (element.nodeName().toLower() == "quote")
			profile.favoriteQuotes = element.text();
		else if (element.nodeName().toLower() == "relationship_status")
			profile.relationshipStatus = facebook::RelationshipStatus::fromDomElement(element);
		else if (element.nodeName().toLower() == "school_info")
			profile.loadSchoolsFromDomElement(element);
		else if (element.nodeName().toLower() == "significant_other_id")
			profile.significantOtherId = element.text();
		else if (element.nodeName().toLower() == "status")
			profile.status = facebook::UserStatus(element);
		else if (element.nodeName().toLower() == "timezone")
			profile.timezone = element.text().toInt();
		else if (element.nodeName().toLower() == "tv")
			profile.favoriteTVShows = element.text();
		else if (element.nodeName().toLower() == "wall_count")
			profile.wallCount = element.text().toInt();
		else if (element.nodeName().toLower() == "work_history")
			profile.workHistory; // some function call = element.text();
		element = element.nextSiblingElement();
	}

	_userInfo = profile;
	return _userInfo;
}

void facebook::Users::setUserInfo(const facebook::UserInfo &userInfo)
{
	_userInfo = userInfo;
}