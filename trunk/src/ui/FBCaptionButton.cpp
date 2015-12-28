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

#include "FBCaptionButton.h"

FBCaptionButton::FBCaptionButton(QWidget * parent): QWidget(parent)
{
	entered = false;
	left = false;
	pressed = false;
	released = false;
}

FBCaptionButton::~FBCaptionButton(void)
{

}

void FBCaptionButton::enterEvent(QEvent * e)
{
	this->mouseEntered();
	repaint();
}

void FBCaptionButton::leaveEvent(QEvent * e)
{
	this->mouseLeft();
	repaint();
}

void FBCaptionButton::mousePressEvent(QMouseEvent * e)
{
	this->mousePressed();
	repaint();
	
}

void FBCaptionButton::mouseReleaseEvent(QMouseEvent * e)
{
	this->mouseReleased();
	repaint();
	emit clicked();
}

void FBCaptionButton::paintEnter(QPainter * p)
{
	p->setPen(QColor("white"));
	p->drawLine(0, 0, this->width(), 0);
	p->drawLine(0, 0, 0, this->height());
	p->setPen(QColor("black"));
	p->drawLine(0, this->height()-1, this->width()-1, this->height()-1);
	p->drawLine(this->width()-1, this->height()-1, this->width()-1, 0);

}

void FBCaptionButton::paintLeave(QPainter * p)
{
	p->setPen(QColor( 59, 89, 152 ));
	p->drawLine(0, 0, this->width(), 0);
	p->drawLine(0, 0, 0, this->height());
	p->setPen(QColor( 59, 89, 152 ));
	p->drawLine(0, this->height()-1, this->width()-1, this->height()-1);
	p->drawLine(this->width()-1, this->height()-1, this->width()-1, 0);	
}

void FBCaptionButton::paintPress(QPainter * p)
{
	p->setPen(QColor("black"));
	p->drawLine(0, 0, this->width(), 0);
	p->drawLine(0, 0, 0, this->height());
	p->setPen(QColor("white"));
	p->drawLine(0, this->height()-1, this->width()-1, this->height()-1);
	p->drawLine(this->width()-1, this->height()-1, this->width()-1, 0);	
}

void FBCaptionButton::mouseEntered()
{
	this->entered = true;
	this->left = false;
	this->pressed = false;
	this->released = false;
}

void FBCaptionButton::mouseLeft()
{
	this->entered = false;
	this->left = true;
	this->pressed = false;
	this->released = false;
}

void FBCaptionButton::mousePressed()
{
	this->entered = false;
	this->left = false;
	this->pressed = true;
	this->released = false;
}

void FBCaptionButton::mouseReleased()
{
	this->entered = false;
	this->left = false;
	this->pressed = false;
	this->released = true;
}

void FBCaptionButton::paintEvent(QPaintEvent * e)
{

	QWidget::paintEvent(e);

	QPainter p(this);

	p.fillRect(QRect(0, 0, this->width(), this->height()), QBrush(QColor(59,89,152)));

	if(this->entered)
	{
		this->paintEnter(&p);
	}

	if(this->left)
	{
		this->paintLeave(&p);
	}

	if(this->pressed)
	{
		this->paintPress(&p);
	}

	if(this->released)
	{
		this->paintEnter(&p);
	}


}
