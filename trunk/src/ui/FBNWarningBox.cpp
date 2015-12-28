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

#include "FBNWarningBox.h"

FBNWarningBox::FBNWarningBox(QWidget * parent, FBNResourceManager *rm) : QLabel(parent)
{
	this->resourceManager = rm;
}

FBNWarningBox::FBNWarningBox(const QString &text, QWidget * parent, FBNResourceManager *rm) : QLabel(text, parent)
{
	this->resourceManager = rm;
}

FBNWarningBox::~FBNWarningBox(void)
{
}

void FBNWarningBox::paintEvent(QPaintEvent * e)
{
	//QPainter p(this);

	//p.setPen(*this->resourceManager->getYellowColor());
	//p.fillRect(0, 0, this->width(), this->height(), QBrush(*this->resourceManager->getLightYellowColor()));
	//p.drawRect(0, 0, this->width() - 1, this->height() - 1);

	//if (this->text().size() > 0)
	//{
	//	if (this->caption().size() = 0)
	//	{
	//		p.setFont(*this->resourceManager->getSmallBoldFont());
	//		p.setPen(Qt::black);
	//		p.drawText(8, ((this->height() - 18) / 2) + 14, this->text());

	//	}
	//	p.setPen(*this->resourceManager->getGreenColor());
	//
	//p.setFont(*this->resourceManager->getSmallNormalFont());
	//}
}
