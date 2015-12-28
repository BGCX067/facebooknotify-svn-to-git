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

#include "FBNApplication.h"

#ifndef WIN32
#ifndef Q_OS_MACX

void FBNApplication::initSingleInstance(QString token, bool perUser)
{
}
void FBNApplication::destroySingleInstance()
{
}

bool FBNApplication::previousInstanceExists()
{
	return false;
}

bool FBNApplication::sendMessage(const QString &message, int timeout)
{
	return false;
}

#endif
#endif

FBNApplication::FBNApplication(const QString &token, int argc, char *argv[], bool singleInstance) : QApplication(argc, argv)
{
	if (singleInstance)
		initSingleInstance(token);
	initApplication();
}

FBNApplication::~FBNApplication()
{
	destroySingleInstance();
}