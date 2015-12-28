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

#include "FBNAboutPanel.h"

FBNAboutPanel::FBNAboutPanel(FBNResourceManager * rm, FBNConfigurationPanelMaster * parent, int index) : FBNConfigurationPanel(rm, parent, index)
{
	this->setText("About fbNotify");



	this->version = new FBNSectionHeading("About fbNotify - Alpha GUI Build", this, this->resourceManager);
	this->version->setGeometry(12, 12, this->width() - 24, 18);
	
	this->onTheWeb = new FBNSectionHeading("fbNotify on the Web", this, this->resourceManager);
	this->onTheWeb->setGeometry(12, 220, this->width() - 24, 18);
	this->credits = new FBNSectionHeading("Credits", this, this->resourceManager);
	this->credits->setGeometry(12, 190, this->width() - 24, 18);


	this->banner = new QLabel(this);
	this->banner->setPixmap(QPixmap::fromImage(*this->resourceManager->getAboutPanelBanner()));
	this->banner->setGeometry(50, 30, 355, 156);

	this->link1 = new FBNLinkButton(this->resourceManager, this);
	this->link1->setGeometry(50, 0, 355, 20);
	this->link1->setText("You have been poked 2 times.");

//	this->creditsBox = new QTextBrowser(this);

}

FBNAboutPanel::~FBNAboutPanel()
{
	delete this->banner;

	delete this->version;
		delete this->credits;
	delete this->onTheWeb;

	delete this->link1;
//	delete this->creditsBox;

}
