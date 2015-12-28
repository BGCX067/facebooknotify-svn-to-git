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

#include "FBWindow.h"

FBWindow::FBWindow(void): QDesktopWidget()
{
	// makes the window frameless
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::ToolTip);

	this->borderLightColor = QColor(214, 223, 238);
	this->borderDarkColor = QColor(161, 181, 206);
	
}

FBWindow::~FBWindow(void)
{
}

void FBWindow::paintEvent(QPaintEvent * e)
{
	// make sure we call the superclass' paint event handler
	QDesktopWidget::paintEvent(e);

	// then draw the notification box's facebook-blue 3D outline
	QPainter p(this);

	p.fillRect(0, 0, this->width(), this->height(), QBrush(QColor("white")));


	// draw the facebook-blue 3D borders
	p.setPen(this->borderLightColor);
	p.drawLine(0, 0, this->width() - 1, 0);
	p.drawLine(1, 1, this->width() - 2, 1);
	p.drawLine(0, 0, 0, this->height() - 1);
	p.drawLine(1, 1, 1, this->height() - 2);

	p.setPen(this->borderDarkColor);
	p.drawLine(0, this->height() - 1, this->width() - 1, this->height() - 1);
	p.drawLine(1, this->height() - 2, this->width() - 2, this->height() - 2);
	p.drawLine(this->width() - 1, this->height() - 1, this->width() - 1, 0);
	p.drawLine(this->width() - 2, this->height() - 2, this->width() - 2, 1);
	

}
