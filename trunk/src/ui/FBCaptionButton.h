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

#ifndef FBCAPTIONBUTTON_H
#define FBCAPTIONBUTTON_H

#include <qwidget.h>
#include <qpainter.h>

class FBCaptionButton : public QWidget
{
	Q_OBJECT
public:
	FBCaptionButton(QWidget * parent);
	~FBCaptionButton(void);

signals:

	void clicked();

public:

	void enterEvent(QEvent *);
	void leaveEvent(QEvent *);
	void mousePressEvent(QMouseEvent *);
	void mouseReleaseEvent(QMouseEvent *);
	void paintEvent(QPaintEvent *);

	void paintEnter(QPainter * p);
	void paintLeave(QPainter * p);
	void paintPress(QPainter * p);

public:

	void mouseEntered();
	void mouseLeft();
	void mousePressed();
	void mouseReleased();

protected:

	bool entered;
	bool left;
	bool pressed;
	bool released;

};

#endif
