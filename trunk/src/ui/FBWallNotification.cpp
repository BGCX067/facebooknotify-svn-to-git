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

#include "FBWallNotification.h"

FBWallNotification::FBWallNotification(FBNResourceManager * m, int n): FBNotification(m)
{
	this->number = n;
	m->playWallSound();
}

FBWallNotification::~FBWallNotification(void)
{

}

void FBWallNotification::paintEvent(QPaintEvent * e)
{
	FBNotification::paintEvent(e);


	QPainter p(this);
	p.setPen(*this->resourceManager->getBlueColor());

	p.setFont(QFont("Tahoma", 8, QFont::Normal));

	//p.drawText(30, 90, "You have ");

	p.setFont(QFont("Tahoma", 8, QFont::Bold));
	p.drawText(60, 90, QString("%1").arg(this->number));


	QFontMetrics m(QFont("Tahoma", 8, QFont::Bold));
	int width = m.width(QString("%1").arg(this->number));

	p.setFont(QFont("Tahoma", 8, QFont::Normal));
	p.drawText(60 + width + 7 , 90, "new");

	p.setFont(QFont("Tahoma", 8, QFont::Bold));
	p.drawText(60 + width + 7 + 25, 90, "wall posts");


}


void FBWallNotification::mousePressEvent(QMouseEvent * e)
{


}
