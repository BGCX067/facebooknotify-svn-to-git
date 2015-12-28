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
//  <result method="facebook.wall.getCount">18</result>

#include "facebook.wall.h"

facebook::Wall::Wall()
{
	_count = 0;
}

facebook::Wall::~Wall()
{
}

const facebook::WallCount & facebook::Wall::count()
{
	return _count;
}

const facebook::WallCount & facebook::Wall::getCount(const QString &xml)
{
	int new_total = 0;
	try
	{
		QDomDocument doc;
		QDomError domError;
		if (!doc.setContent(xml, &(domError.message), &(domError.line), &(domError.column)))
			throw domError;

		QDomElement resultElement = doc.firstChildElement();
		if (resultElement.isNull() || 
		   (resultElement.nodeName() != "result") ||
		   (resultElement.attribute("method") != "facebook.wall.getCount"))
			throw xml;

		new_total = resultElement.text().toInt();

	}
	catch (const QString &val)
	{ 
		throw val;
	}
	catch (bool val)
	{ 
		throw val;
	}
	_count = new_total;
	return _count;
}
void facebook::Wall::setCount(const facebook::WallCount &count)
{
	_count = count;
}

