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

#ifndef FBNOTIFICATION_H
#define FBNOTIFICATION_H

#include "FBWindow.h"
#include "FBNotificationCaptionBar.h"
#include "FBTimer.h"
#include "FBNResourceManager.h"
#include <qcursor.h>



class FBNotification : public FBWindow
{
	Q_OBJECT
public:
	FBNotification(FBNResourceManager *);
	~FBNotification(void);



public slots:

	void slideIn(FBTimer * );

	//void slideOut(FBTimer *);

	void hold(FBTimer * timer);

	//void fadeIn(FBTimer *);

	void fadeOut(FBTimer * timer);

	void show();

	void closeMe();

	void prematureClose();

signals:

	void slideInFinished();
	void holdFinished();
	void fadeOutFinished();
	void dead(FBNotification *);
	void prematureClose(FBNotification *);

public:

	//FBNotificationManager * manager;

	const static int notificationHeight = 150;
	const static int notificationWidth = 220;

	FBNotificationCaptionBar * captionBar;

	FBTimer * holdTimer;
	FBTimer * fadeOutTimer;

	FBNResourceManager * resourceManager;
};

#endif
