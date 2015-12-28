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

#include "FBNSettings.h"

FBNSettings::FBNSettings(FBNLogger *log) : QHash<QString, QString>()
{
	logger = log;
	settings = new QSettings("fbNotify Team", "fbNotify");
#ifndef QT_NO_DEBUG
	this->logger->writeLine("Core.Settings created");
#endif
}
FBNSettings::~FBNSettings()
{
	this->settings->sync();
	delete this->settings;

#ifndef QT_NO_DEBUG
	this->logger->writeLine("Core.Settings destroyed");
#endif

}

bool FBNSettings::getBool(const QString &key, bool defaultValue)
{
	if (this->value(key) == "true")
		return true;
	if (this->value(key) == "false")
		return false;
	return defaultValue;
}

void FBNSettings::setBool(const QString &key, bool value)
{
	if (value)
		(*this)[key] = "true";
	else
		(*this)[key] = "false";
}
int FBNSettings::getInt(const QString &key)
{
	return this->value(key).toInt();
}

void FBNSettings::setInt(const QString &key, int value)
{
	QString newval;
	newval = newval.setNum(value);
	(*this)[key] = newval;
}

double FBNSettings::getDouble(const QString &key)
{
	return this->value(key).toDouble();
}

void FBNSettings::setDouble(const QString &key, double value)
{
	QString newval;
	newval = newval.setNum(value);
	(*this)[key] = newval;
}

QString FBNSettings::getString(const QString &key)
{
	return this->value(key);
}

void FBNSettings::setString(const QString &key, const QString &value)
{
	(*this)[key] = value;
}

void FBNSettings::load()
{
	QStringList keys = this->settings->allKeys();
	for (int i = 0; i < keys.size(); i++)
		(*this)[keys[i]] = this->settings->value(keys[i]).toString();
#ifndef QT_NO_DEBUG
	this->logger->writeLine("Core.Settings loaded");
#endif
}
void FBNSettings::store()
{
	if (this->count())
	{
		QHashIterator<QString, QString> i((QHash<QString, QString>)*this);
		while (i.hasNext())
		{
			i.next();
			this->settings->setValue(i.key(), i.value());
		}
	}
#ifndef QT_NO_DEBUG
	this->logger->writeLine("Core.Settings stored");
#endif
}
