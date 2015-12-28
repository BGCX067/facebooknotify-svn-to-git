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

#ifndef FBNNOTIFICATIONSETTINGSLIST_H
#define FBNNOTIFICATIONSETTINGSLIST_H

#include <QtGui>
#include "FBNResourceManager.h"
#include "../core/FBNSettings.h"

class FBNNotificationSettingsList : protected QScrollArea
{
public:
	FBNNotificationSettingsList(FBNResourceManager * rm, QWidget * parent);
	~FBNNotificationSettingsList();

	void save(FBNSettings &hash);
	void load(FBNSettings &hash);
	void loadDefault();

	void setGeometry(int, int, int, int);

	void paintEvent(QPaintEvent * e);

protected:
	FBNResourceManager * resourceManager;

	QWidget * scrollWidget;

	QCheckBox * pokes;
	QLabel * pokesIcon;
	QCheckBox * messages;
	QLabel * messagesIcon;
	QCheckBox * wallMessages;
	QLabel * wallMessagesIcon;

	QCheckBox * events;
	QCheckBox * friendUpdates;
	QCheckBox * birthdays;

};


#endif
