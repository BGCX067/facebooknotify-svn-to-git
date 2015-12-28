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


//  Abstracting this XML:
//
//  <?xml version="1.0" encoding="UTF-8"?>
//  <result method="facebook.messages.getCount">
//    <unread>0</unread>
//    <total>182</total>
//  </result>

#include "facebook.messages.h"

facebook::Messages::Messages()
{
	_count.unread = 0;
	_count.total = 0;
	_count.mostRecent.setTime_t(0);
}

facebook::Messages::~Messages()
{
}

const facebook::MessageCount & facebook::Messages::count()
{
	return _count;
}

const facebook::MessageCount & facebook::Messages::getCount(const QString &xml)
{
	facebook::MessageCount count;

	QDomDocument doc;
	QDomError domError;
	if (!doc.setContent(xml, &(domError.message), &(domError.line), &(domError.column)))
		throw domError;

	QDomElement resultElement = doc.firstChildElement();
	if (resultElement.isNull() || 
	   (resultElement.nodeName().toLower() != "result") ||
	   (resultElement.attribute("method").toLower() != "facebook.messages.getcount"))
		throw xml;

	QDomElement element = resultElement.firstChildElement();
	while (!element.isNull())
	{
		if (element.nodeName().toLower() == "fb_error")
			throw xml;
		else if (element.nodeName().toLower() == "unread")
			count.unread = element.text().toInt();
		else if (element.nodeName().toLower() == "total")
			count.total = element.text().toInt();
		else if (element.nodeName().toLower() == "most_recent")
			count.mostRecent.setTime_t(element.text().toInt());
		element = element.nextSiblingElement();
	}

	_count = count;
	return _count;
}
void facebook::Messages::setCount(const facebook::MessageCount &count)
{
	_count = count;
}

bool facebook::operator< (const facebook::MessageCount &lhs, const facebook::MessageCount &rhs)
{
	if (lhs.unread < rhs.unread)
		return true;
	if (lhs.total < rhs.total)
		return true;
	return false;
}
bool facebook::operator> (const facebook::MessageCount &lhs, const facebook::MessageCount &rhs)
{
	if ((lhs.unread > rhs.unread) && (lhs.total != rhs.total))
		return true;
	return (lhs.total > rhs.total);
}
bool facebook::operator==(const facebook::MessageCount &lhs, const facebook::MessageCount &rhs)
{
	return ((lhs.unread == rhs.unread) && (lhs.total == rhs.total));
}
bool facebook::operator<=(const facebook::MessageCount &lhs, const facebook::MessageCount &rhs)
{
	return ((lhs < rhs) || (lhs == rhs));
}
bool facebook::operator>=(const facebook::MessageCount &lhs, const facebook::MessageCount &rhs)
{
	return ((lhs > rhs) || (lhs == rhs));
}
bool facebook::operator!=(const facebook::MessageCount &lhs, const facebook::MessageCount &rhs)
{
	return (!(lhs == rhs));
}