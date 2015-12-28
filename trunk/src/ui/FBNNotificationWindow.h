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

#ifndef FBNNOTIFICATIONWINDOW_H
#define	FBNNOTIFICATIONWINDOW_H

#include <QtGui>
#include <QString>
#include <QPixmap>

#include "../core/FBNLogger.h"
#include "../kernel/FBNKernel_includes.h"

#include "FBNEffects.h"
#include "FBNResourceManager.h"
#include "FBNLinkButton.h"
#include "FBNCloseButton.h"

class FBNNotificationWindow : public QDesktopWidget
{

	Q_OBJECT


public:
	FBNNotificationWindow(FBNResourceManager *rm, FBNLogger *log);
	~FBNNotificationWindow();

	void paintEvent(QPaintEvent * e);
	void enterEvent(QEvent * event);
	void leaveEvent(QEvent * event);

	QString linkUrl();
	void setLinkUrl(const QString &url);

	QString text();
	void setText(const QString &url);

	QImage displayIcon();
	void setDisplayIcon(QImage &newbitmap);

signals:
	void notificationClicked();
	void linkClicked(const QString &url);
	void closeButtonClicked();

protected slots:
	void closeButtonClickedSlot();

protected:
	FBNResourceManager * resourceManager;
	FBNLogger * logger;

	FBNCloseButton * closeButton;
	FBNLinkButton * linkButton;
	QLabel * imageLabel;

	QImage * _displayIcon;

	void layout();
};




#endif
