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

#ifndef FBNCORE_H
#define FBNCORE_H

#include "../fbNotify.h"
#include "../kernel/FBNUrlBuilder.h"
#include "../kernel/FBNKernel.h"

class FBNCore : public QThread
{

	Q_OBJECT

public:
	FBNCore(FBNApplication *app);
	~FBNCore();

public slots:
	void messageReceived(const QString& msg);

	void loginMenuItemClicked();
	void enabledMenuItemClicked(bool checked = false);
	void settingsMenuItemClicked();
	void aboutMenuItemClicked();
	void exitMenuItemClicked();

	void loginRequested();

// Slots for the kernel
	void kernelErrorThrown(const facebook::ErrorData &errorData);
	void kernelErrorThrown(const QString &error);

	void messagesCountReady(const facebook::MessageCount &messages);
	void wallCountReady(const facebook::UserInfo &info);
	void pokeCountReady(const facebook::PokeCount &pokes);
	void userProfileReady(const facebook::UserInfo &info);

protected:
// Thread
	void run();
	void pollPause();
	bool runThread;
	bool runThreadProcesses;

// Application
	FBNApplication * fbNotify;
	FBNLogger * logger;

// Kernel	
	FBNUrlBuilder * urlBuilder;
	FBNKernel * kernel;

// Core
	FBNSettings * settings;
	FBNServices * services;
	FBNLocalization * manager;

// UI
	FBNResourceManager * resourceManager;
	FBNConfigurationWindow * configurationWindow;
	FBNTrayIcon * trayIcon;
	FBNNotificationManager * notificationManager;

};

#endif
