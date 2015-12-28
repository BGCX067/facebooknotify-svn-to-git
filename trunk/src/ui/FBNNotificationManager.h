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

#ifndef FBNNOTIFICATIONMANAGER_H
#define FBNNOTIFICATIONMANAGER_H

#include <QtCore>

#include "../core/FBNLogger.h"
#include "../core/FBNSettings.h"
#include "../kernel/FBNKernel_includes.h"
#include "FBNAnimation.h"
#include "FBNNotificationWindow.h"
#include "FBNResourceManager.h"
#include "FBNTrayIcon.h"
#include "FBNLoginNotification.h"

class FBNNotificationManager : public QObject
{
	
	Q_OBJECT

public:
	FBNNotificationManager(FBNResourceManager *rm, FBNTrayIcon *icon, FBNLogger *log, FBNSettings *set);
	~FBNNotificationManager();

	void newPokeNotification(const facebook::PokeCount &count);
	void newLoginNotification(bool stage1);

	void setShowAnimation(FBNAnimation *ani);
	FBNAnimation showAnimation();

	void setHideAnimation(FBNAnimation *ani);
	FBNAnimation hideAnimation();

protected slots:
	void animationStep(FBNAnimation *animation);
	void animationDone(FBNAnimation *animation);

protected:
	FBNResourceManager * resourceManager;
	FBNLogger * logger;
	FBNSettings * settings;
	FBNTrayIcon * trayIcon;

	QVector<FBNNotificationWindow *> notifications;

	void addNotification(FBNNotificationWindow *w);
	void removeNotification(FBNNotificationWindow *w);
	void compactNotifications();

	FBNAnimation * _showAnimation;
	FBNAnimation * _hideAnimation;
#ifdef win32
	const static int padding = 4;
#else
	const static int padding = 2;
#endif
};

#endif
