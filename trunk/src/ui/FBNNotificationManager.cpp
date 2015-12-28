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

#include "FBNNotificationManager.h"

FBNNotificationManager::FBNNotificationManager(FBNResourceManager *rm, FBNTrayIcon *icon, FBNLogger *log, FBNSettings *set)
{
	this->resourceManager = rm;
	this->logger = log;
	this->settings = set;
	this->trayIcon = icon;

	icon->animate(2);

	newLoginNotification(true);

}

FBNNotificationManager::~FBNNotificationManager()
{
	for (int i = 0; i < this->notifications.size(); i++)
		delete notifications[i];

	notifications.clear();
}

void FBNNotificationManager::addNotification(FBNNotificationWindow *w)
{
	this->notifications.push_back(w);
}
void FBNNotificationManager::removeNotification(FBNNotificationWindow *w)
{
}
void FBNNotificationManager::compactNotifications()
{

}

void FBNNotificationManager::animationStep(FBNAnimation *animation) { }
void FBNNotificationManager::animationDone(FBNAnimation *animation) { }

void FBNNotificationManager::newPokeNotification(const facebook::PokeCount &count)
{
}
void FBNNotificationManager::newLoginNotification(bool stage1)
{
	FBNNotificationWindow * login;
	login = new FBNLoginNotification(stage1, this->resourceManager, this->logger);
	this->addNotification(login);
	login->show();
}
