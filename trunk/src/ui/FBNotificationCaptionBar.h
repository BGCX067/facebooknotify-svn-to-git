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

#ifndef FBNOTIFICATIONCAPTIONBAR_H
#define FBNOTIFICATIONCAPTIONBAR_H

#include <qwidget.h>
#include <qpainter.h>
#include <qpoint.h>
#include <qevent.h>

#include "FBNotificationCloseButton.h"
#include "FBNResourceManager.h"





class FBNotificationCaptionBar : public QWidget
{
public:
	FBNotificationCaptionBar(FBNResourceManager * r,QWidget * parent);
	~FBNotificationCaptionBar(void);

public:

	void paintEvent(QPaintEvent * e);
	void mousePressEvent(QMouseEvent * e);
	void mouseMoveEvent(QMouseEvent * e);
	void resizeEvent(QResizeEvent * e);
	void closeEvent(QCloseEvent * e);
	
private:

	QColor bgColor;
	QPoint lastClicked;

	FBNotificationCloseButton * button;

	FBNResourceManager * resourceManager;
};

#endif
