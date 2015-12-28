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

#ifndef FBNLOGINPANEL_H
#define FBNLOGINPANEL_H

#include <QtGui/QtGui>


#include "FBNConfigurationPanel.h"
#include "FBNSectionHeading.h"
#include "FBNLinkButton.h"
#include "FBNLoginButton.h"

class FBNLoginPanel : public FBNConfigurationPanel
{

	Q_OBJECT

public:
	FBNLoginPanel(FBNResourceManager *rm = 0, FBNConfigurationPanelMaster *parent = 0, int index = 4);
	~FBNLoginPanel();

signals:
	void loginClicked();

protected slots:
	void loginButtonClicked();
	
protected:

// Standard message
	FBNSectionHeading * loginHeading;
	QLabel * loginMessage;
	FBNLoginButton * loginButton;

// Why?  Tell Facebook...
	FBNSectionHeading * dummyHeading;
	QLabel * dummyMessage;
	FBNLinkButton * complainLink;

};

#endif
