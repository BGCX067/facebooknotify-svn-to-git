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

#include "FBNCloseButton.h"

FBNCloseButton::FBNCloseButton(FBNResourceManager * rm, QWidget * w): QPushButton(w)
{
	this->resourceManager = rm;

	this->mouseOver = false;

	this->setToolTip(this->resourceManager->getLocalizedString("CloseButtonToolTip", "Close"));
	w->setAttribute(Qt::WA_AlwaysShowToolTips);
}

FBNCloseButton::~FBNCloseButton(void)
{

}


void FBNCloseButton::paintEvent(QPaintEvent * e)
{
	QPainter p(this);

	QImage toDraw = *this->resourceManager->getCloseButtonHover();
	if (mouseOver)
		toDraw = *this->resourceManager->getCloseButton();

	p.drawImage(
		(this->width() - toDraw.width()) / 2,
		(this->height() - toDraw.height()) / 2,
		toDraw);
}

void FBNCloseButton::enterEvent(QEvent * e)
{
	this->mouseOver = true;
	repaint();
}

void FBNCloseButton::leaveEvent(QEvent * e)
{
	this->mouseOver = false;
	repaint();
}
