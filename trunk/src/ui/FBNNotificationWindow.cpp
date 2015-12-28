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

#include "FBNNotificationWindow.h"


FBNNotificationWindow::FBNNotificationWindow(FBNResourceManager *rm, FBNLogger *log) : QDesktopWidget()
{
	this->resourceManager = rm;
	this->logger = log;

	this->setWindowFlags(Qt::FramelessWindowHint | Qt::ToolTip | Qt::WindowStaysOnTopHint);

	QCursor hand(Qt::PointingHandCursor);
	this->setCursor(hand);


	this->linkButton = new FBNLinkButton(rm, this);
	this->linkButton->setWordWrap(true);
	this->closeButton = new FBNCloseButton(rm, this);
	QObject::connect(this->closeButton, SIGNAL(clicked()), this, SLOT(closeButtonClickedSlot()));
	this->_displayIcon = this->resourceManager->getPokeIcon();

	FBNEffects effects;
	effects.setDrawDropShadowFlag(this, true);

	layout();
}
FBNNotificationWindow::~FBNNotificationWindow()
{
	delete this->linkButton;
	delete this->closeButton;
}

void FBNNotificationWindow::paintEvent(QPaintEvent * e)
{
	QDesktopWidget::paintEvent(e);

	QPainter p(this);

	p.fillRect(0, 0, this->width(), this->height(), Qt::white);

	QPen pen(*this->resourceManager->getDarkBlueColor());
	pen.setWidth(2);

	p.setPen(pen);
	p.drawRect(1, 1, this->width() - 2, this->height() - 2);


	QRect headingBox;
	QRect imageBox;

	headingBox = QRect(0, 0, this->width(), 24);
	if (_displayIcon)
		imageBox = QRect((this->width() - _displayIcon->width()) / 2, 28, _displayIcon->width(), _displayIcon->height());

	
	p.fillRect(headingBox, *this->resourceManager->getDarkBlueColor());

	p.setPen(Qt::white);
	p.setFont(*this->resourceManager->getMediumBoldFont());
	p.drawText(8, 18, "fbNotify");

	if (_displayIcon)
		p.drawImage(imageBox, *_displayIcon);
}
QString FBNNotificationWindow::linkUrl()
{
}
void setLinkUrl(const QString &url)
{
}

QString FBNNotificationWindow::text()
{
}
void FBNNotificationWindow::setText(const QString &url)
{
}


QImage FBNNotificationWindow::displayIcon()
{
	return *(_displayIcon);
}
void FBNNotificationWindow::setDisplayIcon(QImage &newbitmap)
{
	_displayIcon = &(newbitmap);
	layout();
}

void FBNNotificationWindow::layout()
{
	this->resize(176, 120);

	this->closeButton->setGeometry(this->width() - 17, 5, 14, 14);
	if (!_displayIcon)
		this->linkButton->setGeometry(1, 24, this->width() - 2, this->height() - 26);
	else
	{
		this->linkButton->setGeometry(2, 24 + _displayIcon->height() + 4, this->width() - 4, this->height() - _displayIcon->height() - 30);
	}
}
void FBNNotificationWindow::enterEvent(QEvent * e)
{
	this->linkButton->setHoverUnderline(false);
}
void FBNNotificationWindow::leaveEvent(QEvent * e)
{
	this->linkButton->setHoverUnderline(true);
}

void FBNNotificationWindow::closeButtonClickedSlot()
{
	this->close();
	emit closeButtonClicked();
}