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

#include "FBNSectionHeading.h"

FBNSectionHeading::FBNSectionHeading(QWidget * parent, FBNResourceManager *rm) : QLabel(parent)
{
	this->resourceManager = rm;
}

FBNSectionHeading::FBNSectionHeading(const QString &text, QWidget * parent, FBNResourceManager *rm) : QLabel(text, parent)
{
	this->resourceManager = rm;
}

FBNSectionHeading::~FBNSectionHeading(void)
{
}

void FBNSectionHeading::paintEvent(QPaintEvent * e)
{
	QPainter p(this);
	p.setFont(*this->resourceManager->getSmallBoldFont());
	p.setPen(*this->resourceManager->getDarkBlueColor());

	p.fillRect(0, 0, this->width(), this->height(), QBrush(Qt::white));
    p.fillRect(0, (this->height() - 18) / 2, this->width(), 18, QBrush(*this->resourceManager->getLightBlueColor()));

	p.drawLine(0, (this->height() - 18) / 2, this->width(), (this->height() - 18) / 2);
	p.drawText(8, ((this->height() - 18) / 2) + 14, this->text());
}
