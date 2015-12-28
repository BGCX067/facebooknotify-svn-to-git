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

#include "FBNTrayIcon.h"

FBNTrayIcon::FBNTrayIcon(QObject *parent, FBNResourceManager *rm) : QSystemTrayIcon(parent)
{
	this->init(rm);
}

FBNTrayIcon::FBNTrayIcon(const QString &toolTip, QObject *parent, FBNResourceManager *rm) : QSystemTrayIcon(parent)
{
	this->init(rm);
}
void FBNTrayIcon::init(FBNResourceManager * rm)
{

	this->resourceManager = rm;

	this->setToolTip(this->resourceManager->getLocalizedString("product_name", "fbNotify"));

	this->setupMenu();

	QObject::connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(triggered(QSystemTrayIcon::ActivationReason)));

	this->_currentFrame = 0;
	this->_animateTimes = 0;
	this->_animating = false;
	this->setIcon(*this->resourceManager->getStaticTrayIcon());
	_timer = new QTimer(this);
	_timer->setInterval(75);
	QObject::connect(_timer, SIGNAL(timeout()), this, SLOT(stepAnimation()));
	this->_timer->start();
}
void FBNTrayIcon::setupMenu()
{
	this->_menu = new QMenu();

	this->_menuLogin = this->_menu->addAction(this->resourceManager->getLocalizedString("trayicon_login_action", "&Login"));
	QObject::connect(this->_menuLogin, SIGNAL(triggered()), this, SLOT(triggeredLogin()));

	this->_menuViewProfile = this->_menu->addAction(this->resourceManager->getLocalizedString("trayicon_viewprofile_action", "&View My Profile"));
	QObject::connect(this->_menuViewProfile, SIGNAL(triggered()), this, SLOT(triggeredViewProfile()));

	this->_menu->addSeparator();

	this->_menuEnable = this->_menu->addAction(this->resourceManager->getLocalizedString("trayicon_enable_action", "&Enable Notifications"));
	QObject::connect(this->_menuEnable, SIGNAL(triggered(bool)), this, SLOT(triggeredEnable(bool)));
	this->_menuEnable->setCheckable(true);

	this->_menu->addSeparator();

	this->_menuSettings = this->_menu->addAction(this->resourceManager->getLocalizedString("trayicon_settings_action", "&Settings"));
	QObject::connect(this->_menuSettings, SIGNAL(triggered()), this, SLOT(triggeredSettings()));
#ifdef Q_OS_WIN32
	QFont defaultAction = this->_menuSettings->font();
	defaultAction.setBold(true);
	this->_menuSettings->setFont(defaultAction);
#endif
	QObject::connect(this, SIGNAL(doubleClicked(const QPoint &)), this, SLOT(triggeredDoubleClick(const QPoint &)));

	this->_menuAbout = this->_menu->addAction(this->resourceManager->getLocalizedString("trayicon_about_action", "&About fbNotify"));
	QObject::connect(this->_menuAbout, SIGNAL(triggered()), this, SLOT(triggeredAbout()));

	this->_menu->addSeparator();

	this->_menuExit = this->_menu->addAction(this->resourceManager->getLocalizedString("trayicon_exit_action", "E&xit"));
	QObject::connect(this->_menuExit, SIGNAL(triggered()), this, SLOT(triggeredExit()));

	this->setContextMenu(_menu);
}

FBNTrayIcon::~FBNTrayIcon()
{
	delete this->_menu;
	if (_timer->isActive()) { _timer->stop(); }
	delete this->_timer;
}

void FBNTrayIcon::setToolTipText(const QString &value) { this->setToolTip(value); }
QString FBNTrayIcon::toolTipText() { return this->toolTip(); }

void FBNTrayIcon::setLoginEnabled(bool value) { this->_menuLogin->setEnabled(value); } 
bool FBNTrayIcon::loginEnabled() { return this->_menuLogin->isEnabled(); }

void FBNTrayIcon::setViewProfileEnabled(bool value) { this->_menuViewProfile->setEnabled(value); } 
bool FBNTrayIcon::viewProfileEnabled() { return this->_menuLogin->isEnabled(); }

void FBNTrayIcon::animate(int times)
{
	_animateTimes += times;
	this->_animating = true;
}
void FBNTrayIcon::stopAnimation()
{
	_animating = false;
	this->_currentFrame = 0;
	this->_animateTimes = 0;
	this->setIcon(*this->resourceManager->getStaticTrayIcon());
}

void FBNTrayIcon::show() { QSystemTrayIcon::show(); }
void FBNTrayIcon::hide() { QSystemTrayIcon::hide(); }

void FBNTrayIcon::stepAnimation()
{
	if (_animating)
	{
		if (_currentFrame == 15)
		{
			_animateTimes--;
			_currentFrame = 0;
		}

		if (_animateTimes == 0)
		{
			stopAnimation();
			return;
		}

		this->setIcon(this->resourceManager->getAnimatedTrayIcon(this->_currentFrame));

		_currentFrame++;
	}
}

void FBNTrayIcon::triggeredLogin()
{
	emit loginClicked();
}

void FBNTrayIcon::triggeredViewProfile()
{
	emit viewProfileClicked();
}

void FBNTrayIcon::triggeredEnable(bool checked)
{
	emit enabledClicked(checked);
}

void FBNTrayIcon::triggeredSettings()
{
	emit settingsClicked();
}
void FBNTrayIcon::triggeredAbout()
{
	emit aboutClicked();
}
void FBNTrayIcon::triggeredExit()
{
	emit exitClicked();
}
void FBNTrayIcon::triggered(QSystemTrayIcon::ActivationReason reason)
{
	if (reason == QSystemTrayIcon::DoubleClick)
		emit settingsClicked();
}

