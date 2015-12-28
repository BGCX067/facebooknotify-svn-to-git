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

#ifdef WIN32
void FBNApplication::initSingleInstance(QString token, bool perUser)
{
	hMutex = (HWND) CreateMutex(NULL, false, (WCHAR*) token.toStdString().c_str());
	dwLastErrorPreviousInstance = GetLastError();
}
void FBNApplication::destroySingleInstance()
{
	if (hMutex)
	{
		ReleaseMutex(hMutex);
		CloseHandle(hMutex);
		hMutex = NULL;
	}
}
bool FBNApplication::previousInstanceExists()
{
	return (ERROR_ALREADY_EXISTS == dwLastErrorPreviousInstance);
}

bool FBNApplication::sendMessage(const QString &message, int timeout)
{
	HWND hWnd = FindWindow(NULL, L"fbNotify");
	if (hWnd)
	{
		COPYDATASTRUCT cpd;
		cpd.dwData = 0;
		cpd.cbData = message.length() + 1;
		cpd.lpData = (void *) message.toStdString().c_str();
		return SendMessage(hWnd, WM_COPYDATA, 0, (LPARAM) &cpd);
	}
	else
		return false;
}

bool FBNApplication::winEventFilter(MSG * msg, long * result)
{
	switch (msg->message)
	{
		case WM_COPYDATA:
			COPYDATASTRUCT * cpd = (COPYDATASTRUCT *) msg->lParam;
			char * retmsg = (char *) cpd->lpData;
			emit messageReceived(retmsg);
			return true;
			break;
	}
	return QApplication::winEventFilter(msg, result);
}

void FBNApplication::initApplication()
{
}

#endif