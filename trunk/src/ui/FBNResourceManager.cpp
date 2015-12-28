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

#include "FBNResourceManager.h"

FBNResourceManager::FBNResourceManager(FBNLocalization * localization, FBNServices * services)
{
	this->localizationManager = localization;

	this->servicesManager = services;

	this->base = "../res/notifications/";

	this->staticTrayIcon = new QPixmap(":/trayIcons/01");

	this->closeButton = new QImage(QString(":/buttons/close"));
	this->closeButtonHover = new QImage(QString(":/buttons/closeHover"));

	this->messageIcon =  new QImage(this->base+QString("message.png"));
	this->pokeIcon = new QImage(this->base+QString("poke.png"));

	this->loginButton = new QImage(":/buttons/login");

	this->darkBlueColor = new QColor(59, 89, 152);
	this->blueColor = new QColor(109, 132, 180);
	this->lightBlueColor = new QColor(216, 223, 234);

	this->yellowColor = new QColor(255, 226, 34);
	this->lightYellowColor = new QColor(255, 251, 226);

	this->greenColor = new QColor(0, 128, 0);

	this->lightGrayColor = new QColor(247, 247, 247);
	this->darkGrayColor = new QColor(102, 102, 102);

#ifdef Q_OS_WIN32
	this->smallBoldFont = new QFont("tahoma", 8, QFont::Bold);
	this->smallNormalFont = new QFont("tahoma", 8, QFont::Normal);
	this->mediumBoldFont = new QFont("tahoma", 11, QFont::Bold);
	this->largeBoldFont = new QFont("tahoma", 16, QFont::Bold);
#endif
#ifdef Q_OS_MACX
	this->smallBoldFont = new QFont("lucida grande", 11, QFont::Bold);
	this->smallNormalFont = new QFont("lucida grande", 11, QFont::Normal);
	this->mediumBoldFont = new QFont("lucida grande", 14, QFont::Bold);
	this->largeBoldFont = new QFont("lucida grande", 19, QFont::Bold);
#endif
#ifdef Q_OS_LINUX
	this->smallBoldFont = new QFont("helvetica", 11, QFont::Bold);
	this->smallNormalFont = new QFont("helvetica", 11, QFont::Normal);
	this->mediumBoldFont = new QFont("lucida grande", 14, QFont::Bold);
	this->largeBoldFont = new QFont("lucida grande", 19, QFont::Bold);
#endif

	this->aboutPanelBanner = new QImage(QString(":/res/fbnlogo_about.png"));

	this->pokeSound = new QSound("../res/poke.wav");
	this->messageSound = new QSound("../res/message.wav");
	this->wallSound = new QSound("../res/wall.wav");
}

FBNResourceManager::~FBNResourceManager(void)
{
	delete this->staticTrayIcon;

	delete this->closeButton;
	delete this->closeButtonHover;

	delete this->messageIcon;
	delete this->pokeIcon;

	delete this->loginButton;

	delete this->darkBlueColor;
	delete this->blueColor;
	delete this->lightBlueColor;

	delete this->yellowColor;
	delete this->lightYellowColor;

	delete this->greenColor;

	delete this->lightGrayColor;
	delete this->darkGrayColor;

	delete this->smallBoldFont;
	delete this->smallNormalFont;
	delete this->mediumBoldFont;
	delete this->largeBoldFont; 

	delete this->aboutPanelBanner;

	delete this->pokeSound;
	delete this->messageSound;
	delete this->wallSound;
}

FBNLocalization * FBNResourceManager::getLocalizationManager()
{
	return this->localizationManager;
}
QString FBNResourceManager::getLocalizedString(const QString &key, const QString &def)
{
	return this->localizationManager->getLocalizedString(key, def);
}

FBNServices * FBNResourceManager::getServicesManager()
{
	return this->servicesManager;
}
void FBNResourceManager::openEmailClient(QString address)
{
	this->servicesManager->openEmailClient(address);
}
void FBNResourceManager::openWebBrowser(QString address)
{
	this->servicesManager->openWebBrowser(address);
}

QPixmap * FBNResourceManager::getAppIcon() { return appIcon; }

QPixmap * FBNResourceManager::getStaticTrayIcon() { return staticTrayIcon; }
QPixmap   FBNResourceManager::getAnimatedTrayIcon(int index)
{
	QString path = ":/trayIcons/";
	index = (index % 14) + 1;
	if (index <= 9)
		path += "0";
	QString new_index;
	new_index = new_index.setNum(index);
	path += new_index;
	return QPixmap(path);
}

QImage * FBNResourceManager::getCloseButton() { return closeButton; }
QImage * FBNResourceManager::getCloseButtonHover() { return closeButtonHover; }

QImage * FBNResourceManager::getMessageIcon() { return messageIcon; }
QImage * FBNResourceManager::getPokeIcon() { return pokeIcon; }

QImage * FBNResourceManager::getLoginButton() { return loginButton; }

QColor * FBNResourceManager::getDarkBlueColor() { return darkBlueColor; }
QColor * FBNResourceManager::getBlueColor() { return blueColor; }
QColor * FBNResourceManager::getLightBlueColor() { return lightBlueColor; }

QColor * FBNResourceManager::getYellowColor() { return yellowColor; }
QColor * FBNResourceManager::getLightYellowColor() { return lightYellowColor; }

QColor * FBNResourceManager::getGreenColor() { return greenColor; }

QColor * FBNResourceManager::getLightGrayColor() { return lightGrayColor; }
QColor * FBNResourceManager::getDarkGrayColor() { return darkGrayColor; }

QFont * FBNResourceManager::getSmallBoldFont() { return smallBoldFont; }
QFont * FBNResourceManager::getSmallNormalFont() { return smallNormalFont; }
QFont * FBNResourceManager::getMediumBoldFont() { return mediumBoldFont; }
QFont * FBNResourceManager::getLargeBoldFont() { return largeBoldFont; }

QImage * FBNResourceManager::getAboutPanelBanner() { return aboutPanelBanner; }

void FBNResourceManager::playPokeSound() { this->pokeSound->play(); }
void FBNResourceManager::playMessageSound() { this->messageSound->play(); }
void FBNResourceManager::playWallSound() { this->wallSound->play(); }

void FBNResourceManager::generateAboutPanelCreditsBox(QTextBrowser *browser)
{

}
QPixmap FBNResourceManager::getSmallIcon(const QString &name)
{
	QPixmap retval(":/smallIcons/" + name);
	return retval;
}
