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

#ifndef FBNLOCALIZATION_H
#define FBNLOCALIZATION_H

#include <QtCore>
#include <QtXml>
#include "FBNLogger.h"

class FBNLocalization : private QHash<QString, QString>
{
public:
	FBNLocalization(const QString &lang = "en", FBNLogger * log = 0);
	~FBNLocalization();

	void loadLanguageFile(const QString &lang = "en");
	QString language();

	QString getLocalizedString(const QString &key, const QString &def = "");

protected:
	bool _loaded;
	QString _language;

	FBNLogger * logger;

	void parseLanguageFile(const QString &xml);

};

#endif
