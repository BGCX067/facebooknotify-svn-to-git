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
//	<result method="">
//	  <fb_error>
//		<code>101</code>
//		<msg>Invalid API key</msg>
//		<your_request/>
//	  </fb_error>
//	</result>

#include "facebook.error.h"

facebook::Error::Error(FBNLogger *logger)
{
	_logger = logger;
	_error.errorCode = facebook::ErrorCodes::noError;
}

facebook::Error::~Error()
{
}

const facebook::ErrorData & facebook::Error::error()
{
	return _error;
}

const facebook::ErrorData & facebook::Error::getError(const QString &xml)
{
	facebook::ErrorData newError;
	try
	{
		QDomDocument doc;
		QDomError domError;
		if (!doc.setContent(xml, &(domError.message), &(domError.line), &(domError.column)))
			throw domError;				// XML is totally invalid and useless

		QDomElement resultElement = doc.firstChildElement();
		if (resultElement.isNull() || 
		   (resultElement.nodeName().toLower() != "result"))
			throw xml;					// XML is not of the correct schema
		newError.methodCalled = resultElement.attribute("method");

		QDomElement errorElement = resultElement.firstChildElement();
		if (errorElement.isNull() || (errorElement.nodeName().toLower() != "fb_error"))
			throw xml;					// XML is not of the correct schema

		QDomElement element = errorElement.firstChildElement();
		while (!element.isNull())
		{
			if (element.nodeName().toLower() == "unread")
				newError.errorCode = (facebook::ErrorCodes::ErrorCodes) element.text().toInt();
			else if (element.nodeName().toLower() == "msg")
				newError.message = element.text();
			element = element.nextSiblingElement();
		}

	}
	catch (const QString &val)
	{
		if (_logger)
		{
			_logger->writeError("Error.getError: Invalid XML Structure", "XML is not of an error type.\n" + val, true);
		}
	}
	catch (const QDomError &val)
	{
		if (_logger)
		{
			_logger->writeError("Error.getError: Invalid XML", "XML is not well-formed.\n" + xml, true);
		}
	}

	_error = newError;

	return _error;
}

void facebook::Error::setError(const facebook::ErrorData &error)
{
	_error = error;
}
