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

#ifndef FBNNOTIFICATIONPANEL_H
#define FBNNOTIFICATIONPANEL_H

#include <QtGui/QtGui>

#include "FBNConfigurationPanel.h"
#include "FBNSectionHeading.h"
#include "FBNNotificationSettingsList.h"

#include "../core/FBNSettings.h"

class FBNNotificationsPanel : public FBNConfigurationPanel
{
public:
	FBNNotificationsPanel(FBNResourceManager *rm = 0, FBNConfigurationPanelMaster *parent = 0, int index = 1);
	~FBNNotificationsPanel();

	void save(FBNSettings &hash);
	void load(FBNSettings &hash);
	void loadDefault();

protected:

	FBNSectionHeading * displayTypes;
	FBNSectionHeading * displayStyles;

	FBNNotificationSettingsList * notificationsScrollArea;

	// display effects
	QCheckBox * animateTrayIcon;

};

#endif
