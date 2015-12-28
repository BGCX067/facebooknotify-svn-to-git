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

#ifndef FBNCONFIGURATIONPANEL_H
#define FBNCONFIGURATIONPANEL_H
#include <QtGui/QtGui>

#include "FBNResourceManager.h"
#include "FBNPanelTab.h"
#include "FBNConfigurationPanelMaster.h"

#include "../core/FBNSettings.h"

class FBNConfigurationPanel : public QWidget
{

	Q_OBJECT

private:
	QString _text;

public:

	FBNConfigurationPanel(FBNResourceManager *rm = 0, FBNConfigurationPanelMaster *parent = 0, int index = 0);
	~FBNConfigurationPanel();

	void save(FBNSettings &hash);
	void load(FBNSettings &hash);
	void loadDefault();

	QString text();
	void setText(const QString &newText);
	void setSelected(bool);
	bool selected();

	bool isEnabled();
	void setEnabled(bool value);

	FBNPanelTab * getTab();

public slots:
	void tabSelectedChanged(bool);

signals:
	void selectedChanged(bool);

protected:
	FBNResourceManager * resourceManager;
	FBNPanelTab * tab;

};

#endif
