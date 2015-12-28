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

#ifndef FBNABOUTPANEL_H
#define FBNABOUTPANEL_H

#include <QtGui/QtGui>

#include "FBNConfigurationPanel.h"
#include "FBNSectionHeading.h"
#include "FBNLinkButton.h"

class FBNAboutPanel : public FBNConfigurationPanel
{
public:
	FBNAboutPanel(FBNResourceManager *rm = 0, FBNConfigurationPanelMaster *parent = 0, int index = 4);
	~FBNAboutPanel();


protected:
	FBNSectionHeading * version;
	FBNSectionHeading * onTheWeb;
	FBNSectionHeading * credits;

	QLabel * banner;

	QTextBrowser * creditsBox;

	FBNLinkButton * link1;
};

#endif
