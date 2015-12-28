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

#include "FBNEffects.h"


#ifdef WIN32

#include <QtCore/qt_windows.h>

FBNEffects::FBNEffects()
{
}
FBNEffects::~FBNEffects()
{
}
void FBNEffects::setDrawDropShadowFlag(QWidget * w, bool flag)
{
	int CS_DROPSHADOW = 0x20000;
	HWND widgetHwnd = w->winId();
	int currentStyle = GetClassLong(widgetHwnd, GCL_STYLE);
	int newStyle;
	if (flag)
	{
		newStyle = currentStyle | CS_DROPSHADOW;
	}
	else
	{
		newStyle = currentStyle & !CS_DROPSHADOW;
	}
	SetClassLong(widgetHwnd, GCL_STYLE, newStyle);
}

#endif


#ifndef WIN32
FBNEffects::FBNEffects()
{
}
FBNEffects::~FBNEffects()
{
}

void FBNEffects::setDrawDropShadowFlag(QWidget * w, bool flag)
{
}

#endif