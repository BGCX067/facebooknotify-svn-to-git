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

#include "FBNotification.h"

FBNotification::FBNotification(FBNResourceManager * r): FBWindow()
{
	this->resourceManager = r;

	QCursor c;
	c.setShape(Qt::PointingHandCursor);
	this->setCursor(c);

	this->resize(this->notificationWidth, this->notificationHeight);

	this->captionBar = new FBNotificationCaptionBar(this->resourceManager, this);

	this->captionBar->setGeometry(2, 2, this->width() - 4, 25);

}

FBNotification::~FBNotification(void)
{
	delete this->captionBar;
}

void FBNotification::slideIn(FBTimer * timer)
{
	
	int top = this->y();
	int height = this->height();
	
	top -= 2;
	height += 2;
	this->setGeometry(this->x(), top, this->width(), height);
	
	if (height > this->notificationHeight) 
	{
		timer->stop();
		emit slideInFinished();
	}

}

void FBNotification::fadeOut(FBTimer * timer)
{

	this->setWindowOpacity(this->windowOpacity() - 0.01);


	if(this->windowOpacity() <= 0.02)
	{
		timer->stop();
		this->closeMe();
		
	}

}

void FBNotification::closeMe()
{



	this->close();
	emit dead(this);
	

	
}

void FBNotification::prematureClose()
{

	this->close();
	emit prematureClose(this);
	
	
}


void FBNotification::hold(FBTimer * timer)
{

	QObject::connect( timer, SIGNAL(timeout(FBTimer *)), this, SIGNAL(holdFinished()));
}

void FBNotification::show()
{
	
	FBWindow::show();
}
