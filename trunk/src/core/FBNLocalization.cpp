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

#include "FBNLocalization.h"

FBNLocalization::FBNLocalization(const QString &lang, FBNLogger * log)
{
	this->logger = log;
	_loaded = false;
	loadLanguageFile(lang);
}

FBNLocalization::~FBNLocalization()
{
}

QString FBNLocalization::getLocalizedString(const QString &key, const QString &def)
{
	if (!_loaded)
		return def;
	QString retVal;
	retVal = this->value(key, def);
	if (retVal.length() == 0)
		return def;
	return retVal;
}

void FBNLocalization::loadLanguageFile(const QString &lang)
{
#ifndef QT_NO_DEBUG
	this->logger->enter("FBNLocalization::loadLanguageFile");
#endif
	QFile langFile("../res/" + lang + ".fbnl");
	try
	{

		if (!langFile.open(QIODevice::ReadOnly | QIODevice::Text))
			throw false;

#ifndef QT_NO_DEBUG
			this->logger->writeLine("File opened succesfully!");
#endif

		QString xml;
		QTextStream textStream(&langFile);
        while (!textStream.atEnd()) {
            xml += textStream.readLine();
        }
		langFile.close();

#ifndef QT_NO_DEBUG
		this->logger->writeData("File read succesfully! Resultant data (xml)", xml, true);
#endif

		parseLanguageFile(xml);

		_loaded = true;
		_language = lang;
	}
	catch (bool val)
	{
		_loaded = false;
		_language = "";
		langFile.close();
		return ;
	}
#ifndef QT_NO_DEBUG
	this->logger->leave("FBNLocalization::loadLanguageFile");
#endif
}

void FBNLocalization::parseLanguageFile(const QString &xml)
{
	QDomDocument doc;
	if (!doc.setContent(xml))
		throw false;

	QDomElement langRootElement = doc.firstChildElement();
	if (langRootElement.isNull() ||
		langRootElement.nodeName() != "fbnotify_localization_data")
		throw false;

	QDomElement searchNode = langRootElement.firstChildElement();
	QDomElement dataElement;
    while (!searchNode.isNull()) {
		if (searchNode.nodeName() == "data")
		{
			dataElement = searchNode;
			break;
		}
        searchNode = searchNode.nextSiblingElement();
    }
	if (dataElement.isNull())
		throw false;

	this->clear();
	QDomElement stringNode = dataElement.firstChildElement();
	while (!stringNode.isNull())
	{
		(*this)[stringNode.attribute("key")] = stringNode.text();
		stringNode = stringNode.nextSiblingElement();
	}
	if (!this->size())
		throw false;
}
