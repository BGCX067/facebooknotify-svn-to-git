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

#include "FBNPanelTab.h"

FBNPanelTab::FBNPanelTab(FBNResourceManager * rm, QWidget * w): QPushButton(w)
{

	QCursor c;
	c.setShape(Qt::PointingHandCursor);
	this->setCursor(c);


	this->resourceManager = rm;
	this->_selected = false;


	this->mouseOver = false;

}

FBNPanelTab::~FBNPanelTab(void)
{

}

bool FBNPanelTab::selected()
{
	return _selected;
}

void FBNPanelTab::setSelected(bool value)
{
	_selected = value;
	repaint();
	emit selectedChanged(value);
}

void FBNPanelTab::paintEvent(QPaintEvent * e)
{
	QPainter p(this);
	p.setFont(*this->resourceManager->getSmallNormalFont());
	QCursor arrow(Qt::ArrowCursor);
	QCursor hand(Qt::PointingHandCursor);
	if (this->isEnabled())
	{
		if (!mouseOver && !_selected)
		{
			p.fillRect(0, 0, this->width(), this->height(), QBrush(Qt::white));
			p.setPen(*this->resourceManager->getDarkBlueColor());
			this->setCursor(hand);
		}
		else if (mouseOver && !_selected)
		{
			p.fillRect(0, 0, this->width(), this->height(), QBrush(*this->resourceManager->getDarkBlueColor()));
			p.setPen(Qt::white);
		}
		else if (_selected)
		{
			p.fillRect(0, 0, this->width(), this->height(), QBrush(Qt::white));
			p.setFont(*this->resourceManager->getSmallBoldFont());
			p.setPen(*this->resourceManager->getDarkBlueColor());
			this->setCursor(arrow);
		}
	}
	else
	{
		p.fillRect(0, 0, this->width(), this->height(), QBrush(Qt::white));
		p.setPen(*this->resourceManager->getDarkGrayColor());
		this->setCursor(arrow);
	}
	p.drawText(4, 13, this->text());
	p.setPen(*this->resourceManager->getLightBlueColor());
	p.drawLine(0, this->height()-1, this->width(), this->height() - 1);
	if (_selected)
	{
		p.setPen(*this->resourceManager->getDarkBlueColor());
		p.drawLine(0, this->height()-2, this->width(), this->height() - 2);
		p.drawLine(0, this->height()-1, this->width(), this->height() - 1);
	}
}

void FBNPanelTab::enterEvent(QEvent * e)
{
	if (this->isEnabled())
		this->mouseOver = true;
	repaint();
}

void FBNPanelTab::leaveEvent(QEvent * e)
{
	this->mouseOver = false || this->hasFocus();
	repaint();
}

void FBNPanelTab::mousePressEvent(QMouseEvent * e)
{
	if (e->button() == Qt::LeftButton)
	{
		this->_selected = true;
		repaint();

		emit selectedChanged(true);
		emit clicked(this);
	}
}
void FBNPanelTab::keyPressEvent(QKeyEvent * e)
{
	if (e->key() == Qt::Key_Space)
	{
		this->_selected = true;
		repaint();

		emit selectedChanged(true);
		emit clicked(this);
	}
}
void FBNPanelTab::focusInEvent(QFocusEvent * e)
{
	this->mouseOver = true;
	repaint();
}
void FBNPanelTab::focusOutEvent(QFocusEvent * e)
{
	this->mouseOver = false;
	repaint();
}
