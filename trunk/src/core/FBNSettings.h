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

#ifndef FBNSETTINGS_H
#define FBNSETTINGS_H

#include <QHash>
#include <QHashIterator>
#include <QSettings>
#include <QString>
#include <QStringList>

#include "FBNLogger.h"

class FBNSettings : private QHash<QString, QString> 
{

public:
	FBNSettings(FBNLogger *logger);
	~FBNSettings();

	bool getBool(const QString &key, bool defaultValue);
	void setBool(const QString &key, bool value);

	int getInt(const QString &key);
	void setInt(const QString &key, int value);

	double getDouble(const QString &key);
	void setDouble(const QString &key, double value);

	QString getString(const QString &key);
	void setString(const QString &key, const QString &value);

	void load();
	void store();

protected:
	QSettings * settings;

	FBNLogger * logger;

};

#endif
