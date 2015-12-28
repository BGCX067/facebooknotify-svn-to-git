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

#ifndef FBNCONFIGURATIONWINDOW_H
#define FBNCONFIGURATIONWINDOW_H

#include "../core/FBNLogger.h"
#include "../core/FBNSettings.h"
#include "FBNUI_includes.h"

class FBNConfigurationWindow : public QDesktopWidget
{

	Q_OBJECT

public:
	FBNConfigurationWindow(FBNResourceManager *rm = 0, FBNLogger *log = 0);
	~FBNConfigurationWindow(void);

public:
	void show();
	void showThenLogin();
	void showThenAbout();

	bool confirmHide();
	
	void loadSettings(void);
	void loadDefaultSettings();
	void save(void);

	void setLoginPanelEnabled(bool val);

signals:
	void loginClicked();

public slots:

	void restoreDefaultsButtonClicked();
	void cancelButtonClicked();

	void aboutPanelSelectedChanged(bool);
	void loginPanelSelectedChanged(bool);
	void notificationsPanelSelectedChanged(bool);
	void panelSelectedChanged(bool);

	void loginButtonClicked();

protected:

	FBNLogger * logger;
	FBNResourceManager * resourceManager;

	QDialogButtonBox * buttons;
	QPushButton * okButton;
	QPushButton * cancelButton;
	QPushButton * restoreDefaultsButton;

	FBNConfigurationPanelMaster * panelMaster;

	FBNNotificationsPanel * notificationsPanel;
	FBNLoginPanel * loginPanel;
	FBNAboutPanel * aboutPanel;



QCheckBox * testcb;
	FBNSectionHeading * test;
	FBNConfigurationPanel * panel;

	QTextBrowser * testtext;

	FBNWarningBox * testwarning;

	void keyPressEvent(QKeyEvent * e);
	

};

#endif
