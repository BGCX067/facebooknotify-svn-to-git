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

#include "FBNLogger.h"

FBNLogger::FBNLogger(const QString &filename) : file(filename)
{
	if (!file.open(QIODevice::Append | QIODevice::WriteOnly | QIODevice::Text))
		throw false;
	fs = new QTextStream(&file);

	indentCount = 0;
};

FBNLogger::~FBNLogger()
{
	fs->flush();
	delete this->fs;
	file.close();
}

void FBNLogger::enter(const QString &methodName, bool timeStamp)
{
	*fs << indent() << "ENTER >> " << methodName;
	indentCount++;

	if (timeStamp)
		*fs << ' ' << makeTimeStamp();

	*fs << '\n';
	fs->flush();
}

void FBNLogger::leave(const QString &methodName, bool timeStamp)
{
	indentCount--;
	*fs << indent() << "LEAVE << " << methodName;

	if (timeStamp)
		*fs << ' ' << makeTimeStamp();

	*fs << '\n';
	fs->flush();
}

void FBNLogger::writeData(const QString &dataName, const QVariant &data, bool block, bool timeStamp)
{
	*fs << indent() << dataName << " = ";
	if (!block)
	{
		*fs << data.toString() << "; ";
		if (timeStamp)
			*fs << makeTimeStamp() << '\n';
	}
	else
	{
		indentCount++;
		QString blocked = indent() + data.toString();
		blocked.replace('\n', "\n" + indent());
		*fs << '\n' << blocked << '\n';
		if (timeStamp)
			*fs << indent() << makeTimeStamp() << '\n';
		indentCount--;
	}

	fs->flush();
}
void FBNLogger::writeError(const QString &errorName, const QVariant &data, bool block, bool timeStamp)
{
	*fs << indent() << "ERROR >> " << errorName;
	if (!block)
	{
		*fs << " >> " << data.toString() << '\n';
		if (timeStamp)
			*fs << makeTimeStamp() << '\n';
	}
	else
	{
		indentCount++;
		QString blocked = indent() + data.toString();
		blocked.replace('\n', '\n' + indent());
		*fs << '\n' << blocked << '\n';
		if (timeStamp)
			*fs << indent() << makeTimeStamp() << '\n';
		indentCount--;
	}

	fs->flush();
}

void FBNLogger::writeLine(const QString &line, bool timeStamp)
{
	*fs << indent() << line << ' ';
	if (timeStamp)
		*fs << makeTimeStamp() << '\n';
	fs->flush();
}

void FBNLogger::writeFacebookError(const facebook::ErrorData &data, bool timeStamp)
{
	*fs << indent() << "ERROR >> Facebook API Error " << (int) data.errorCode << " <<";
	if (timeStamp)	
		*fs << ' ' << makeTimeStamp();
	*fs	<< '\n';
	indentCount++;
	*fs << indent() << facebook::ErrorCodes::toString(data.errorCode) << '\n';
	indentCount--;
	fs->flush();
}



QString FBNLogger::indent()
{
	if (indentCount < 0)
		indentCount = 0;

	QString value(6 * indentCount, ' ');
	return value;
}

QString FBNLogger::makeTimeStamp()
{
	QDateTime date;
	QString stamp;
	stamp += "[";
	stamp += date.currentDateTime().toString();
	stamp += "]";
	return stamp;
}
