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

#include "FBNKernelStructs.h"

facebook::UserStatus::UserStatus(const QDomElement &element)
{
	if (element.nodeName().toLower() != "status")
		throw false;

	QDomElement resultElement = element.firstChildElement();
	while (!resultElement.isNull())
	{
		if (resultElement.nodeName().toLower() == "message")
			this->message = resultElement.text();
		else if (resultElement.nodeName().toLower() == "time")
			this->time.setTime_t(resultElement.text().toInt());

		resultElement = resultElement.nextSiblingElement();
	}

}

facebook::UserStatus::UserStatus()
{	
	this->time.setTime_t(0);
}

void facebook::UserInfo::loadHighSchoolsFromDomElement(const QDomElement &element)
{
	if (element.nodeName().toLower() != "hs_info")
		return;

	this->highSchools.clear();

	facebook::SchoolInformation hs1;
	facebook::SchoolInformation hs2;

	QDomElement resultElement = element.firstChildElement();
	while (!resultElement.isNull())
	{
		if (resultElement.nodeName().toLower() == "hs1_name")
			hs1.name = resultElement.text();
		else if (resultElement.nodeName().toLower() == "hs2_name")
			hs2.name = resultElement.text();
		else if (resultElement.nodeName().toLower() == "hs1_key")
			hs1.name = resultElement.text();
		else if (resultElement.nodeName().toLower() == "hs2_key")
			hs2.key = resultElement.text();
		else if (resultElement.nodeName().toLower() == "year")
			hs1.year = resultElement.text().toInt();
			hs2.year = resultElement.text().toInt();

		resultElement = resultElement.nextSiblingElement();
	}

	this->highSchools.push_back(hs1);
	this->highSchools.push_back(hs2);
}
void facebook::UserInfo::loadSchoolsFromDomElement(const QDomElement &element)
{
	if (element.nodeName().toLower() != "hs_info")
		return;

	this->schools.clear();

	QDomElement resultElement = element.firstChildElement();
	while (!resultElement.isNull())
	{
		if (resultElement.nodeName().toLower() == "school_info_elt")
		{
			QDomElement childElement = element.firstChildElement();
			facebook::SchoolInformation school;
			while (!childElement.isNull())
			{
				if (childElement.nodeName().toLower() == "name")
					school.name = childElement.text();
				else if (childElement.nodeName().toLower() == "year")
					school.year = childElement.text().toInt();
				else if (childElement.nodeName().toLower() == "key")
					school.key = childElement.text();

				childElement = childElement.nextSiblingElement();
			}
			this->schools.push_back(school);
		}
		resultElement = resultElement.nextSiblingElement();
	}
}
