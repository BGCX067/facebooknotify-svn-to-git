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

#ifndef FBNOTIFICATIONMANAGER_H
#define FBNOTIFICATIONMANAGER_H

#include <vector>
#include "FBTimer.h"
#include "FBNResourceManager.h"
#include "FBNotification.h"
#include "FBLoginNotification.h"
#include "FBMessageNotification.h"
#include "FBPokeNotification.h"
#include "FBWallNotification.h"
//#include "FBPhotoCommentNotification.h"


class FBNotificationManager: public QObject
{
	Q_OBJECT

public:

	FBNotificationManager(FBNResourceManager *);
	~FBNotificationManager(void);

public slots:



	void newLoginNotification(int hold = 3000000);
	void newMessageNotification(int num = 1);
	void newPokeNotification(int num = 1);
	void newWallNotification(int num = 1);
	//void newPhotoCommentNotification(int num);



protected slots:

	void addNotification(FBNotification * notification, int hold = 4000);
	void removeNotification(FBNotification * );
	void compact();


protected:

	void startNotification(FBNotification * n, int top, FBTimer * , FBTimer *, FBTimer *);

protected:

	FBNResourceManager * resourceManager;
	int animationStyle;
	const static int padding = 5;
	std::vector<FBNotification *> notifications;
};

#endif
