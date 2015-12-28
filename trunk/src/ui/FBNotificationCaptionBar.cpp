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

#include "FBNotificationCaptionBar.h"
#include "FBNotification.h"

FBNotificationCaptionBar::FBNotificationCaptionBar(FBNResourceManager * r, QWidget * parent): QWidget(parent)
{
	this->resourceManager = r;

	QCursor c;
	c.setShape(Qt::ArrowCursor);
	this->setCursor(c);

	this->bgColor = QColor(59, 89, 152);

	this->button = new FBNotificationCloseButton(this);

	QObject::connect(this->button, SIGNAL(clicked()), parent, SLOT(prematureClose()));

}

FBNotificationCaptionBar::~FBNotificationCaptionBar(void)
{
	delete button;
}

void FBNotificationCaptionBar::paintEvent(QPaintEvent * e)
{
	QPainter p(this);
	p.fillRect(0, 0, this->width(), this->height(), QBrush(QColor(this->bgColor)));
	//p.drawImage(5, 3, *resourceManager->getNotificationTitle());
	

}

void FBNotificationCaptionBar::mousePressEvent(QMouseEvent * e)
{
	this->lastClicked = e->pos();	
}


void FBNotificationCaptionBar::mouseMoveEvent(QMouseEvent * e)
{
	FBNotification * p = (FBNotification *) this->parentWidget();

	// make the parent window of the caption bar drag with the mouse-move event
	// that the caption bar recieves

	p->setGeometry(p->x() + e->x() - this->lastClicked.x(), p->y() + e->y() - this->lastClicked.y(), p->width(), p->height());


}

void FBNotificationCaptionBar::closeEvent(QCloseEvent * e)
{
	this->parentWidget()->close();
}

void FBNotificationCaptionBar::resizeEvent(QResizeEvent * e)
{
		button->setGeometry(this->width() - 20, 4, 16, 16);
}
