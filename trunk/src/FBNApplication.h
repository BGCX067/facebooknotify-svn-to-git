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

#ifndef FBNAPPLICATION_H
#define FBNAPPLICATION_H

#include <QtCore>
#include <QApplication>

#ifdef WIN32
#include <windows.h>
#include <Lmcons.h>
#endif

#ifdef Q_OS_MACX
#include <Carbon.h>
#endif

class FBNApplication : public QApplication
{

	Q_OBJECT

public:

	FBNApplication(const QString &token, int argc, char *argv[], bool singleInstance = true);
	~FBNApplication();

	bool sendMessage(const QString &message, int timeout = 5000);  

	bool previousInstanceExists();

#ifdef WIN32
	bool winEventFilter(MSG * msg, long * result);
#endif

signals:
	void messageReceived(const QString &message);

protected:

	void initSingleInstance(QString token, bool perUser = true);
	void destroySingleInstance();

	void initApplication();

	QString _token;

#ifdef WIN32
	long dwLastErrorPreviousInstance;
	HWND hMutex;
#endif

};



#endif
