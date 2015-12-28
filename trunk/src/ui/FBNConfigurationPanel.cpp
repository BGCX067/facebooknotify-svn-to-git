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

#include "FBNConfigurationPanel.h"

FBNConfigurationPanel::FBNConfigurationPanel(FBNResourceManager * rm, FBNConfigurationPanelMaster * parent, int index) : QWidget(parent)
{
	this->resourceManager = rm;
	this->tab = new FBNPanelTab(rm, parent);
	this->tab->setGeometry(12, 69 + (index * 18), 120, 18);
	QObject::connect(this->tab, SIGNAL(selectedChanged(bool)), this, SLOT(tabSelectedChanged(bool)));

	this->hide();
	this->setGeometry(145, 57, parent->width() - 145, parent->height() - 57);
}

FBNConfigurationPanel::~FBNConfigurationPanel()
{
	delete this->tab;
}


QString FBNConfigurationPanel::text()
{
	return this->tab->text();
}

void FBNConfigurationPanel::setText(const QString &newText)
{
	this->tab->setText(newText);
}
void FBNConfigurationPanel::tabSelectedChanged(bool selected)
{
	this->setVisible(selected);
	emit selectedChanged(selected);
}

FBNPanelTab * FBNConfigurationPanel::getTab()
{
	return this->tab;
}

void FBNConfigurationPanel::setSelected(bool value)
{
	this->tab->setSelected(value);
}

bool FBNConfigurationPanel::selected()
{
	return this->tab->selected();
}

bool FBNConfigurationPanel::isEnabled()
{
	return QWidget::isEnabled();
}
void FBNConfigurationPanel::setEnabled(bool value)
{
	this->tab->setEnabled(value);
	QWidget::setEnabled(value);
}