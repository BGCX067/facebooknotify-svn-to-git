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

#include "FBNNotificationsPanel.h"

FBNNotificationsPanel::FBNNotificationsPanel(FBNResourceManager * rm, FBNConfigurationPanelMaster * parent, int index) : FBNConfigurationPanel(rm, parent, index)
{
	this->setText("Notifications");

	this->displayTypes = new FBNSectionHeading("Notification Types to Display", this, this->resourceManager);
	this->displayTypes->setGeometry(12, 12, this->width() - 24, 18);

	this->displayStyles = new FBNSectionHeading("Display Effects", this, this->resourceManager);
	this->displayStyles->setGeometry(12, 300, this->width() - 24, 18);

	this->notificationsScrollArea = new FBNNotificationSettingsList(this->resourceManager, this);
	this->notificationsScrollArea->setGeometry(12, displayTypes->y() + 18, this->width() - 24, 250);

	// display effects
	this->animateTrayIcon = new QCheckBox("Animate Tray Icon", this);
//	this->animateTrayIcon->setGeometry(this->messages->x(), 300 + 24, 130, 22);


	this->animateTrayIcon->setVisible(false);
}

FBNNotificationsPanel::~FBNNotificationsPanel()
{
	delete this->displayStyles;
	delete this->displayTypes;

	delete this->notificationsScrollArea;

	delete this->animateTrayIcon;

}
void FBNNotificationsPanel::save(FBNSettings &hash)
{
	this->notificationsScrollArea->save(hash);
}
void FBNNotificationsPanel::load(FBNSettings &hash)
{
	this->notificationsScrollArea->load(hash);


	this->animateTrayIcon->setChecked(hash.getBool("notifications_effects_animateTrayIcon", true));
}

void FBNNotificationsPanel::loadDefault() 
{
	this->notificationsScrollArea->loadDefault();

}
