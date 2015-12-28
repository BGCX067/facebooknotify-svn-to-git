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

#include "FBNLoginPanel.h"

FBNLoginPanel::FBNLoginPanel(FBNResourceManager * rm, FBNConfigurationPanelMaster * parent, int index) : FBNConfigurationPanel(rm, parent, index)
{
	this->setText("Login");

	this->loginHeading = new FBNSectionHeading("fbNotify needs you to login to Facebook", this, this->resourceManager);
	this->loginHeading->setGeometry(12, 12, this->width() - 24, 18);

	this->loginMessage = new QLabel(this);
	this->loginMessage->setGeometry(12, 34, this->width() - 24, 28);
	this->loginMessage->setWordWrap(true);
	this->loginMessage->setText("Click the blue Facebook button below to open your Web browser.  ");  
	this->loginMessage->setText(this->loginMessage->text() + "Once the page loads, enter your Facebook account information.");
	this->loginMessage->setText(this->loginMessage->text() + "As soon as you login there, fbNotify will work.");

	this->loginButton = new FBNLoginButton(this->resourceManager, this);
	this->loginButton->setGeometry((this->width() - 109) / 2, 64, 109, 28);
	QObject::connect(this->loginButton, SIGNAL(clicked()), this, SLOT(loginButtonClicked()));


	this->dummyHeading = new FBNSectionHeading("Why do I have to login using my Web browser?", this, this->resourceManager);
	this->dummyHeading->setGeometry(12, 100, this->width() - 24, 18);

	this->dummyMessage = new QLabel(this);
	this->dummyMessage->setGeometry(12, this->dummyHeading->y() + this->dummyHeading->height() + 4, this->width() - 24, 56);
	this->dummyMessage->setWordWrap(true);
	this->dummyMessage->setText("Facebook requires that ALL applications that use the Facebook Development Platform login ");
	this->dummyMessage->setText(this->dummyMessage->text() + "through the Facebook Web site.  Currently, it violates the ");
	this->dummyMessage->setText(this->dummyMessage->text() + "developers' Terms of Service agreement to have users login ");
	this->dummyMessage->setText(this->dummyMessage->text() + "in any other way.  If this is too much of a hassle, don't blame ");
	this->dummyMessage->setText(this->dummyMessage->text() + "the fbNotify Development Team.  Click the link below to tell Facebook.");

	this->complainLink = new FBNLinkButton(this->resourceManager, this);
	this->complainLink->setText("Let Facebook know");
	this->complainLink->setUrl("http://www.facebook.com/help.php?tab=suggest");
	this->complainLink->setGeometry(this->width() - this->complainLink->width() - 16, this->dummyMessage->y() + this->dummyMessage->height(), 109, 24);

}

FBNLoginPanel::~FBNLoginPanel()
{
	delete this->dummyHeading;
	delete this->complainLink;
	delete this->dummyMessage;
	delete this->loginHeading;
	delete this->loginButton;
	delete this->loginMessage;
}

void FBNLoginPanel::loginButtonClicked()
{
	emit loginClicked();
}
