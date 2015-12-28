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

#ifndef FBNRESOURCEMANAGER_H
#define FBNRESOURCEMANAGER_H

#include <QtGui/QtGui>

#include "../core/FBNLocalization.h"
#include "../core/FBNServices.h"

class FBNResourceManager
{
public:
	FBNResourceManager(FBNLocalization * localization, FBNServices * services);
	~FBNResourceManager(void);

public:

	FBNLocalization * getLocalizationManager();
	QString getLocalizedString(const QString &key, const QString &def = "");
	
	FBNServices * getServicesManager();
	void openEmailClient(QString address = "");
	void openWebBrowser(QString address);

	QPixmap * getAppIcon();

	QPixmap * getStaticTrayIcon();
	QPixmap   getAnimatedTrayIcon(int);

	QImage * getCloseButton();
	QImage * getCloseButtonHover();

	QImage * getBirthdayIcon();
	QImage * getEventIcon();
	QImage * getFriendUpdateIcon();
	QImage * getMessageIcon();
	QImage * getMobileMessageIcon();
	QImage * getPhotoIcon();
	QImage * getPokeIcon();
	QImage * getWallIcon();

	QImage * getLoginButton();

	QColor * getDarkBlueColor();
	QColor * getBlueColor();
	QColor * getLightBlueColor();

	QColor * getYellowColor();
	QColor * getLightYellowColor();

	QColor * getGreenColor();

	QColor * getLightGrayColor();
	QColor * getDarkGrayColor();

	QFont * getSmallBoldFont();
	QFont * getSmallNormalFont();
	QFont * getMediumBoldFont();
	QFont * getLargeBoldFont();

	QImage * getAboutPanelBanner();

	QPixmap   getSmallIcon(const QString &name);

	void playPokeSound();
	void playMessageSound();
	void playWallSound();

	void generateAboutPanelCreditsBox(QTextBrowser *browser);
private:

	FBNLocalization * localizationManager;
	FBNServices * servicesManager;

	QString base;

	QPixmap * appIcon;
	QPixmap * staticTrayIcon;

	QImage * notificationTitle;

	QImage * closeButton;
	QImage * closeButtonHover;

	QImage * birthdayIcon;
	QImage * eventIcon;
	QImage * friendUpdateIcon;
	QImage * messageIcon;
	QImage * mobileMessageIcon;
	QImage * photoIcon;
	QImage * pokeIcon;
	QImage * wallIcon;

	QImage * loginButton;

	QColor * darkBlueColor;
	QColor * blueColor;
	QColor * lightBlueColor;

	QColor * yellowColor;
	QColor * lightYellowColor;

	QColor * greenColor;

	QColor * lightGrayColor;
	QColor * darkGrayColor;

	QFont * smallBoldFont;
	QFont * smallNormalFont;
	QFont * mediumBoldFont;
	QFont * largeBoldFont;

	QImage * aboutPanelBanner;

	QSound * pokeSound;
	QSound * messageSound;
	QSound * wallSound;
};

#endif
