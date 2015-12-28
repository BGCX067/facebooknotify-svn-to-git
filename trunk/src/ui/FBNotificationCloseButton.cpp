//	fbNotify: A Facebook notification system.
//	Copyright (C) 2006 fbNotify Team.
//
//	This program is free software; you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation; either version 2 of the License, or
//	(at your option) any later version.

//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU General Public License for more details.

//	You should have received a copy of the GNU General Public License along
//	with this program; if not, write to the Free Software Foundation, Inc.,
//	51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

#include "FBNotificationCloseButton.h"

FBNotificationCloseButton::FBNotificationCloseButton(QWidget * caption): FBCaptionButton(caption)
{
	
}

FBNotificationCloseButton::~FBNotificationCloseButton(void)
{
}

void FBNotificationCloseButton::paintEvent(QPaintEvent * e)
{
	FBCaptionButton::paintEvent(e);

	QPainter p(this);
	p.setPen(QColor("white"));
	p.drawLine(pad, pad, this-> width() - pad -1, this->height()- pad-1);
	p.drawLine(pad, this->height() - pad - 1, this->width() - pad - 1, pad);
}
