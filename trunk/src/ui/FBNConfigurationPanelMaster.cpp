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

#include "FBNConfigurationPanelMaster.h"

FBNConfigurationPanelMaster::FBNConfigurationPanelMaster(QWidget * parent, FBNResourceManager *rm) : QWidget(parent)
{
	this->resourceManager = rm;
}

FBNConfigurationPanelMaster::~FBNConfigurationPanelMaster(void)
{
}

void FBNConfigurationPanelMaster::paintEvent(QPaintEvent * e)
{
	QPainter p(this);
	p.fillRect(0, 0, this->width(), this->height(), QBrush(Qt::white));
	
	p.setPen(*this->resourceManager->getLightBlueColor());
	p.drawLine(144, 0, 144, this->height());

    p.fillRect(0, 0, this->width(), 33, QBrush(*this->resourceManager->getDarkBlueColor()));

	p.setPen(QColor(59, 89, 152));
	p.drawLine(0, 56, this->width(), 56);
	p.drawLine(0, this->height() - 1, this->width(), this->height() - 1);
	p.fillRect(0, 33, this->width(), 23, QBrush(*this->resourceManager->getBlueColor()));

	p.setPen(Qt::white);
	p.setFont(*this->resourceManager->getLargeBoldFont());
	p.drawText(8, 24, "fbNotify");
	p.setFont(*this->resourceManager->getMediumBoldFont());
	p.drawText(8, 50, "Settings");

}
