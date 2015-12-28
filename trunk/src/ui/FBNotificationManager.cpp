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

#include "FBNotificationManager.h"

FBNotificationManager::FBNotificationManager(FBNResourceManager  * r): QObject()
{
	this->resourceManager = r;
}

FBNotificationManager::~FBNotificationManager(void)
{
	for(int i = 0; i < this->notifications.size(); i++)
	{
		delete notifications[i];
	}

	notifications.clear();
}

void FBNotificationManager::addNotification(FBNotification * notification, int hold)
{
	FBTimer * slideInTimer = new FBTimer();
	slideInTimer->setInterval(1);

	FBTimer * holdTimer = new FBTimer();
	holdTimer->setSingleShot(true);
	holdTimer->setInterval(hold);


	FBTimer * fadeOutTimer = new FBTimer();
	fadeOutTimer->setInterval(10);

	notification->holdTimer = holdTimer;
	notification->fadeOutTimer = fadeOutTimer;


	QObject::connect( slideInTimer,  SIGNAL(timeout(FBTimer * )), 
		              notification,  SLOT(slideIn(FBTimer * ))
				    );

	QObject::connect( notification, SIGNAL(slideInFinished()),
		              holdTimer   , SLOT(start())
					);


	if(this->notifications.size() == 0)
	{
		QObject::connect( holdTimer,    SIGNAL(timeout(FBTimer *)),
						fadeOutTimer, SLOT(start())
						);


		QObject::connect( fadeOutTimer,    SIGNAL(timeout(FBTimer *)),
						notification,    SLOT(fadeOut(FBTimer *))
						);

		QObject::connect( notification,    SIGNAL(dead(FBNotification *)),
						this,            SLOT(removeNotification(FBNotification *))
						);
	}

	QObject::connect(notification, SIGNAL(prematureClose(FBNotification *)),
		             this, SLOT(removeNotification(FBNotification*))
					 );


	startNotification(notification, this->notifications.size(), slideInTimer, holdTimer, fadeOutTimer);

	this->notifications.push_back(notification);
	
}




void FBNotificationManager::startNotification(FBNotification * notification, int position, FBTimer * slidein, FBTimer * hold, FBTimer *fade)
{
	
	
	notification->setGeometry(notification->availableGeometry().width() - notification->width() - padding, notification->availableGeometry().height() - (position+1)* padding - (position) * notification->notificationHeight, notification->notificationWidth, 0);
	notification->show();
	slidein->start();
	

}

void FBNotificationManager::removeNotification(FBNotification * notification)
{
	
	int index = -1;

	for(int i = 0; i < this->notifications.size() && index == -1; i++)
	{
		if(this->notifications[i] == notification)
		{
			index = i;
			delete notification;
		}
	}

	if(index != -1)
	{
		std::vector<FBNotification *>::iterator it = this->notifications.begin();
		for(int c = 0; c < index; c++)
		{
			it++;
		}

		this->notifications.erase(it);
	}


	this->compact();
}


void FBNotificationManager::compact()
{


	for(int i = 0; i < this->notifications.size(); i++)
	{
		int position = i+1;
		FBNotification * notification = this->notifications[i];
		notification->setGeometry(notification->availableGeometry().width() - notification->width() - padding, notification->availableGeometry().height() - (position)* padding - (position) * notification->notificationHeight, notification->notificationWidth, notification->notificationHeight);
	}

	if(this->notifications.size() > 0)
	{
		FBNotification * n = this->notifications[0];

		FBTimer * holdTimer = n->holdTimer;
		FBTimer * fadeOutTimer = n->fadeOutTimer;

		

		QObject::connect( holdTimer,    SIGNAL(timeout(FBTimer *)),
						fadeOutTimer, SLOT(start())
						);


		QObject::connect( fadeOutTimer,    SIGNAL(timeout(FBTimer *)),
						n,    SLOT(fadeOut(FBTimer *))
						);

		QObject::connect( n,    SIGNAL(dead(FBNotification *)),
						this,            SLOT(removeNotification(FBNotification *))
						);

		holdTimer->setInterval(1000);
		holdTimer->start();
	}
		
}


void FBNotificationManager::newMessageNotification(int num)
{
	FBNotification * m = new FBMessageNotification(this->resourceManager, num);
	this->addNotification(m);
	
}

void FBNotificationManager::newPokeNotification(int num)
{
	FBNotification * m = new FBPokeNotification(this->resourceManager, num);
	this->addNotification(m);
	
}

void FBNotificationManager::newWallNotification(int num)
{
	FBNotification * m = new FBWallNotification(this->resourceManager, num);
	this->addNotification(m);
	
}

void FBNotificationManager::newLoginNotification(int hold)
{
	FBNotification * m = new FBLoginNotification(this->resourceManager);
	this->addNotification(m, hold);
	
}
