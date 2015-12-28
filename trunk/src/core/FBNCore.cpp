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

#include "FBNCore.h"

FBNCore::FBNCore(FBNApplication *app) : QThread(app)
{
	// Move application pointer
	this->fbNotify = app;

	// Logger
	this->logger = new FBNLogger("fbNotify.txt");
#ifndef QT_NO_DEBUG
	this->logger->enter("fbNotify Startup");
#endif

	// Setup Core objects
	this->settings = new FBNSettings(logger);
	this->settings->load();
#ifndef QT_NO_DEBUG
	this->logger->writeLine("Core.Settings created and loaded");
#endif

	this->services = new FBNServices();
#ifndef QT_NO_DEBUG
	this->logger->writeLine("Core.ServicesManager created");
#endif


	this->manager = new FBNLocalization("en", this->logger);
#ifndef QT_NO_DEBUG
	this->logger->writeLine("Core.LocalizationManager created");
#endif


	// Setup Kernel objects
	this->urlBuilder = new FBNUrlBuilder();
	this->kernel = new FBNKernel(logger, services, urlBuilder);
#ifndef QT_NO_DEBUG
	this->logger->writeLine("Kernel created");
#endif

	// Setup UI objects
	this->resourceManager = new FBNResourceManager(manager, services);
#ifndef QT_NO_DEBUG
	this->logger->writeLine("UI.ResourceManager created");
#endif

	this->configurationWindow = new FBNConfigurationWindow(this->resourceManager, this->logger);
	QObject::connect(this->configurationWindow, SIGNAL(loginClicked()), this, SLOT(loginRequested()));
#ifndef QT_NO_DEBUG
	this->logger->writeLine("UI.ConfigurationWindow created");
#endif

	this->trayIcon = new FBNTrayIcon(this, this->resourceManager);
	QObject::connect(this->trayIcon, SIGNAL(loginClicked()), this, SLOT(loginMenuItemClicked()));
	QObject::connect(this->trayIcon, SIGNAL(enabledClicked(bool)), this, SLOT(enabledMenuItemClicked(bool)));
	QObject::connect(this->trayIcon, SIGNAL(settingsClicked()), this, SLOT(settingsMenuItemClicked()));
	QObject::connect(this->trayIcon, SIGNAL(aboutClicked()), this, SLOT(aboutMenuItemClicked()));
	QObject::connect(this->trayIcon, SIGNAL(exitClicked()), this, SLOT(exitMenuItemClicked()));
	this->trayIcon->show();
#ifndef QT_NO_DEBUG
	this->logger->writeLine("UI.TrayIcon created");
#endif

	this->notificationManager = new FBNNotificationManager(this->resourceManager, this->trayIcon, this->logger, this->settings);
#ifndef QT_NO_DEBUG
	this->logger->writeLine("UI.NotificationManager created");
#endif

	QObject::connect(fbNotify, SIGNAL(messageReceived(QString)), this, SLOT(messageReceived(QString)));


	QObject::connect(this->kernel, SIGNAL(errorThrown(facebook::ErrorData)),
					 this, SLOT(kernelErrorThrown(facebook::ErrorData)));
	QObject::connect(this->kernel, SIGNAL(errorThrown(QString)),
					 this, SLOT(kernelErrorThrown(QString)));

	QObject::connect(this->kernel, SIGNAL(messagesCountReady(facebook::MessageCount)),
					 this, SLOT(messagesCountReady(facebook::MessageCount)));
	QObject::connect(this->kernel, SIGNAL(wallCountReady(facebook::UserInfo)),
					 this, SLOT(wallCountReady(facebook::UserInfo)));
	QObject::connect(this->kernel, SIGNAL(pokeCountReady(facebook::PokeCount)),
					 this, SLOT(pokeCountReady(facebook::PokeCount)));
	QObject::connect(this->kernel, SIGNAL(userProfileReady(facebook::UserInfo)),
					 this, SLOT(userProfileReady(facebook::UserInfo)));


	this->runThread = true;
	this->runThreadProcesses = true;
}

FBNCore::~FBNCore()  // MUST BE DONE IN REVERSE ORDER
{
	// Destroy UI objects
	delete this->notificationManager;
	delete this->trayIcon;
	delete this->configurationWindow;
	delete this->resourceManager;

	// Destroy Core objects
	delete this->manager;
	delete this->services;
	delete this->settings;

	// Destroy Kernel objects
	delete this->kernel;
	delete this->urlBuilder;

	// Destroy the logger
	delete this->logger;

	this->terminate();
}

void FBNCore::run()
{
	while (runThread)
	{
		if (runThreadProcesses)
		{

		}

		this->sleep(3);
	}
}

void FBNCore::pollPause()
{
	while(!runThread)
	{
		this->sleep(1);
	}
}

void FBNCore::loginMenuItemClicked()
{
	loginRequested();
}
void FBNCore::enabledMenuItemClicked(bool checked)
{
	this->configurationWindow->setLoginPanelEnabled(false);
}
void FBNCore::settingsMenuItemClicked()
{
	this->configurationWindow->show();
}
void FBNCore::aboutMenuItemClicked()
{
	this->configurationWindow->showThenAbout();
}
void FBNCore::exitMenuItemClicked()
{
	this->settings->store();
	this->runThread = false;
	this->fbNotify->quit();
#ifndef QT_NO_DEBUG
	this->logger->leave("fbNotify Shutdown");
#endif
}

void FBNCore::loginRequested()
{
	this->kernel->startLogin();
}

void FBNCore::messageReceived(const QString &msg)
{
	if (msg == "fbNotify.ShowSettings")
	{
		this->settingsMenuItemClicked();
		this->trayIcon->animate(1);
	}
	else if(msg == "fbNotify.Exit")
		this->exitMenuItemClicked();
}

void FBNCore::kernelErrorThrown(const facebook::ErrorData &errorData) {}
void FBNCore::kernelErrorThrown(const QString &error){}

void FBNCore::messagesCountReady(const facebook::MessageCount &messages){}
void FBNCore::wallCountReady(const facebook::UserInfo &info){}
void FBNCore::pokeCountReady(const facebook::PokeCount &pokes){}
void FBNCore::userProfileReady(const facebook::UserInfo &info){}