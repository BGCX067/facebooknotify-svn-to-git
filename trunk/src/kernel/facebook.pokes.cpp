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
//	<?xml version="1.0" encoding="UTF-8"?>
//	<result method="facebook.pokes.getCount">
//    <unseen>1</unseen>
//	  <total>63</total>
//	</result>

#include "facebook.pokes.h"

facebook::Pokes::Pokes()
{
	_count.unseen = 0;
	_count.total = 0;
}

facebook::Pokes::~Pokes()
{
}

const facebook::PokeCount & facebook::Pokes::count()
{
	return _count;
}

const facebook::PokeCount & facebook::Pokes::getCount(const QString &xml)
{
	facebook::PokeCount count;

	QDomDocument doc;
	QDomError domError;
	if (!doc.setContent(xml, &(domError.message), &(domError.line), &(domError.column)))
		throw domError;

	QDomElement resultElement = doc.firstChildElement();
	if (resultElement.isNull() || 
	   (resultElement.nodeName() != "result") ||
	   (resultElement.attribute("method").toLower() != "facebook.pokes.getcount"))
		throw xml;

	QDomElement element = resultElement.firstChildElement();
	while (!element.isNull())
	{
		if (element.nodeName().toLower() == "fb_error")
			throw xml;
		else if (element.nodeName().toLower() == "unseen")
			count.unseen = element.text().toInt();
		else if (element.nodeName().toLower() == "total")
			count.total = element.text().toInt();
		element = element.nextSiblingElement();
	}

	_count = count;
	return _count;
}
void facebook::Pokes::setCount(const facebook::PokeCount &count)
{
	_count = count;
}

