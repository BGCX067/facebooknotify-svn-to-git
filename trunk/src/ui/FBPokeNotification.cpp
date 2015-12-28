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

#include "FBPokeNotification.h"

FBPokeNotification::FBPokeNotification(FBNResourceManager * m, int num): FBNotification(m)
{
	this->number = num;
	m->playPokeSound();
}


FBPokeNotification::~FBPokeNotification(void)
{



}



void FBPokeNotification::paintEvent(QPaintEvent * e )
{
	FBNotification::paintEvent(e);
	
	QPainter p(this);

	p.drawImage(35, 60, *resourceManager->getPokeIcon());
	p.setPen(*this->resourceManager->getBlueColor());
	p.setFont(QFont("Tahoma", 10, QFont::Bold));
	p.drawText(100, 90, QString("%1").arg(this->number));

	QFontMetrics fm(QFont("Tahoma", 10, QFont::Bold));
	int width = fm.width(QString("%1").arg(this->number));

	p.setFont(QFont("Tahoma", 8, QFont::Normal));

	if(this->number == 1)
	{
		p.drawText(100 + width + 7, 90, "new poke");
	}
	else
	{
		p.drawText(100 + width + 7, 90, "new pokes");
	}
	
}
	
void FBPokeNotification::mousePressEvent(QMouseEvent * e)
{


}
