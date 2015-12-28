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

#include "FBNKernelEnums.h"


facebook::UserNetworkType::UserNetworkType facebook::UserNetworkType::fromDomElement(const QDomElement &element)
{
	if (element.nodeName().toLower() != "type")
		return facebook::UserNetworkType::unspecified;

	switch (element.text().toInt())
	{
	case 1:
		return facebook::UserNetworkType::collegeNetwork;
		break;
	case 2:
		return facebook::UserNetworkType::highSchoolNetwork;
		break;
	case 3:
		return facebook::UserNetworkType::workNetwork;
		break;
	case 4:
		return facebook::UserNetworkType::geographicNetwork;
		break;
	default:
		return facebook::UserNetworkType::unspecified;
	}
}
facebook::Gender::Gender facebook::Gender::operator|(facebook::Gender::Gender lhs, facebook::Gender::Gender rhs)
{
	return (facebook::Gender::Gender)((int)lhs | (int)rhs);
}
facebook::Gender::Gender facebook::Gender::operator|=(facebook::Gender::Gender &lhs, facebook::Gender::Gender rhs)
{
	return lhs = lhs | rhs;
}
facebook::Gender::Gender facebook::Gender::fromString(const QString &val)
{
	if (val.toLower() == "male")
		return facebook::Gender::male;
	else if (val.toLower() == "female")
		return facebook::Gender::female;
	return facebook::Gender::unspecified;
}
facebook::Gender::Gender facebook::Gender::fromDomElement(const QDomElement &val)
{
	if (val.nodeName().toLower() == "gender")
		return facebook::Gender::fromString(val.text());

	else if (val.nodeName().toLower() == "meeting_sex")
	{
		Gender retval = facebook::Gender::unspecified;
		QDomElement element = val.firstChildElement();
		while (!element.isNull())
		{
			if (element.nodeName().toLower() == "meeting_sex_elt") 
				retval |= facebook::Gender::fromString(element.text());
			element.nextSiblingElement();
		}
		return retval;
	}

	return facebook::Gender::unspecified;
}
facebook::LookingFor::LookingFor facebook::LookingFor::operator|(facebook::LookingFor::LookingFor lhs, facebook::LookingFor::LookingFor rhs)
{
	return (facebook::LookingFor::LookingFor)((int)lhs | (int)rhs);
}
facebook::LookingFor::LookingFor facebook::LookingFor::operator|=(facebook::LookingFor::LookingFor &lhs, facebook::LookingFor::LookingFor rhs)
{
	return lhs = lhs | rhs;
}
facebook::RelationshipStatus::RelationshipStatus facebook::RelationshipStatus::fromDomElement(const QDomElement &element)
{
	if (element.nodeName().toLower() != "relationship_status")
		return facebook::RelationshipStatus::unspecified;

	if (element.text().toLower() == "")
		return facebook::RelationshipStatus::unspecified;
	else if (element.text().toLower() == "single")
		return facebook::RelationshipStatus::single;
	else if (element.text().toLower() == "in a relationship")
		return facebook::RelationshipStatus::inARelationship;
	else if (element.text().toLower() == "in an open relationship")
		return facebook::RelationshipStatus::inAnOpenRelationship;
	else if (element.text().toLower() == "engaged")
		return facebook::RelationshipStatus::engaged;
	else if (element.text().toLower() == "married")
		return facebook::RelationshipStatus::married;
	else if (element.text().toLower() == "it's complicated")
		return facebook::RelationshipStatus::itsComplicated;
	else
		return facebook::RelationshipStatus::unspecified;

}
facebook::PoliticalView::PoliticalView facebook::PoliticalView::fromDomElement(const QDomElement &element)
{
	if (element.nodeName().toLower() != "political")
		return facebook::PoliticalView::unspecified;

	if (element.text().toLower() == "")
		return facebook::PoliticalView::unspecified;
	else if (element.text().toLower() == "very liberal")
		return facebook::PoliticalView::veryLiberal;
	else if (element.text().toLower() == "liberal")
		return facebook::PoliticalView::liberal;
	else if (element.text().toLower() == "moderate")
		return facebook::PoliticalView::moderate;
	else if (element.text().toLower() == "conservative")
		return facebook::PoliticalView::conservative;
	else if (element.text().toLower() == "very conservative")
		return facebook::PoliticalView::veryConservative;
	else if (element.text().toLower() == "apathetic")
		return facebook::PoliticalView::apathetic;
	else if (element.text().toLower() == "liberation")
		return facebook::PoliticalView::liberation;
	else if (element.text().toLower() == "other")
		return facebook::PoliticalView::other;
	else
		return facebook::PoliticalView::unspecified;

}
facebook::SocialLink::SocialLink facebook::SocialLink::operator|(facebook::SocialLink::SocialLink lhs, facebook::SocialLink::SocialLink rhs)
{
	return (facebook::SocialLink::SocialLink)((int)lhs | (int)rhs);
}
facebook::SocialLink::SocialLink facebook::SocialLink::operator|=(facebook::SocialLink::SocialLink &lhs, facebook::SocialLink::SocialLink rhs)
{
	return lhs = lhs | rhs;
}
QString facebook::ErrorCodes::toString(ErrorCodes error)
{
	switch(error)
	{
		case ErrorCodes::noError: 
			return "No Error/Unlisted API Error";
		case ErrorCodes::unknown: 
			return "An unknown error occurred. Please resubmit the request.";
		case ErrorCodes::service:
			return "The service is not available at this time.";
		case ErrorCodes::tooManyCalls:
			return "The application has reached the maximum number of requests allowed. More requests are allowed once the time window has completed.";
		case ErrorCodes::badIp:
			return "The request came from a remote address not allowed by this application.";
		case ErrorCodes::badParam:
			return "One of the parameters specified was missing or invalid.";
		case ErrorCodes::badApiKey:
			return "The api key submitted is not associated with any known application.";
		case ErrorCodes::badSessionKey:
			return "The session key was improperly submitted or has reached its timeout. Direct the user to log in again to obtain another key.";
		case ErrorCodes::badCallId:
			return "The submitted call_id was not greater than the previous call_id for this session.";
		case ErrorCodes::badSignature:
			return "The signature was not computed correctly.";
		case ErrorCodes::badUserId:
			return "Invalid user id.";
		case ErrorCodes::badUserField:
			return "Invalid user info field.";
		case ErrorCodes::badUserSocialField:
			return "Invalid user field.";
		case ErrorCodes::userPermissionDenied:
			return "User not visible.";
		case ErrorCodes::albumPermissionDenied:
			return "Album not visible.";
		case ErrorCodes::photoPermissionDenied:
			return "Photo not visible.";
	}
	return "No Error/Unlisted API Error";
}
QString facebook::UserDetailFields::toString(UserDetailFields details)
{
	if (details == UserDetailFields::none)
		return "";

	QString retval;
	if (details & UserDetailFields::aboutMe)
		retval += "about_me,";
	if (details & UserDetailFields::affiliations)
		retval += "affiliations,";
	if (details & UserDetailFields::birthday)
		retval += "birthday,";
	if (details & UserDetailFields::favoriteBooks)
		retval += "books,";
	if (details & UserDetailFields::activities)
		retval += "clubs,";
	if (details & UserDetailFields::currentLocation)
		retval += "current_location,";
	if (details & UserDetailFields::firstName)
		retval += "first_name,";
	if (details & UserDetailFields::gender)
		retval += "gender,";
	if (details & UserDetailFields::hometownLocation)
		retval += "hometown_location,";
	if (details & UserDetailFields::highSchools)
		retval += "hs_info,";
	if (details & UserDetailFields::intrests)
		retval += "intrests,";
	if (details & UserDetailFields::lastName)
		retval += "last_name,";
	if (details & UserDetailFields::lookingFor)
		retval += "meeting_for,";
	if (details & UserDetailFields::intrestedIn)
		retval += "meeting_sex,";
	if (details & UserDetailFields::favoriteMovies)
		retval += "movies,";
	if (details & UserDetailFields::favoriteMusic)
		retval += "music,";
	if (details & UserDetailFields::name)
		retval += "name,";
	if (details & UserDetailFields::notesCount)
		retval += "notes_count,";
	if (details & UserDetailFields::politicalViews)
		retval += "political,";
	if (details & UserDetailFields::pictureUrl)
		retval += "pic,";
	if (details & UserDetailFields::profileUpdateTime)
		retval += "profile_update_time,";
	if (details & UserDetailFields::favoriteQuotes)
		retval += "quote,";
	if (details & UserDetailFields::relationshipStatus)
		retval += "relationship_status,";
	if (details & UserDetailFields::religiousViews)
		retval += "religion,";
	if (details & UserDetailFields::schools)
		retval += "school_info,";
	if (details & UserDetailFields::significantOtherId)
		retval += "significant_other_id,";
	if (details & UserDetailFields::status)
		retval += "status,";
	if (details & UserDetailFields::timezone)
		retval += "timezone,";
	if (details & UserDetailFields::favoriteTVShows)
		retval += "tv,";
	if (details & UserDetailFields::wallCount)
		retval += "wall_count,";
	if (details & UserDetailFields::workHistory)
		retval += "work_history,";

	retval.truncate(retval.size() - 1);

	return retval;
}
