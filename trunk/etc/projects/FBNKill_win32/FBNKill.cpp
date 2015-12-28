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

//  FBNKill is a program to see if fbNotify is runnning, if it is
//  it signals to fbNotify to quit.  Useful for installations.

#include <windows.h>

int main()
{
	HWND hWnd = FindWindow(NULL, "fbNotify");
	char msg[14] = "fbNotify.Exit";
	if (hWnd)
	{
		COPYDATASTRUCT cpd;
		cpd.dwData = 0;
		cpd.cbData = 14;
		cpd.lpData = (void *) msg;
		return SendMessage(hWnd, WM_COPYDATA, 0, (LPARAM) &cpd);
	}
	else
		return false;
}