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

#ifndef FBNTRAYICON_H
#define FBNTRAYICON_H

#include <QtGui/QtGui>

#include "FBNResourceManager.h"

class FBNTrayIcon : protected QSystemTrayIcon
{

	Q_OBJECT

public:
	FBNTrayIcon(QObject *parent = 0, FBNResourceManager *rm = 0);
	FBNTrayIcon(const QString &, QObject *parent = 0, FBNResourceManager *rm = 0);

	~FBNTrayIcon();

	void setToolTipText(const QString &);
	QString toolTipText();
	
	void setLoginEnabled(bool);
	bool loginEnabled();
	void setViewProfileEnabled(bool);
	bool viewProfileEnabled();

	void animate(int);
	void stopAnimation();

	void show();
	void hide();

signals:
	void loginClicked();
	void viewProfileClicked();
	void enabledClicked(bool checked = false);
	void settingsClicked();
	void aboutClicked();
	void exitClicked();

protected:
	QMenu * _menu;
	QAction * _menuLogin;
	QAction * _menuViewProfile;
	QAction * _menuEnable;
	QAction * _menuSettings;
	QAction * _menuAbout;
	QAction * _menuExit;

	QTimer * _timer;

	FBNResourceManager * resourceManager;

	int _currentFrame;
	int _animateTimes;
	bool _animating;

	void init(FBNResourceManager * rm);
	void setupMenu();

protected slots:
	void triggeredLogin();
	void triggeredViewProfile();
	void triggeredEnable(bool checked = false);
	void triggeredSettings();
	void triggeredAbout();
	void triggeredExit();

	void triggered(QSystemTrayIcon::ActivationReason reason);

	void stepAnimation();

};

#endif
