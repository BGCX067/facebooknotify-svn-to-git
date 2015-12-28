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

#include "FBNNotificationSettingsList.h"

FBNNotificationSettingsList::FBNNotificationSettingsList(FBNResourceManager * rm, QWidget * parent) : QScrollArea(parent)
{
	this->resourceManager = rm;
	this->setFrameShape(QFrame::NoFrame);

	this->scrollWidget = new QWidget(this);
	this->scrollWidget->setGeometry(0, 0, 0, 400);
	this->setWidget(scrollWidget);

	QPalette pal;
	pal.setColor(QPalette::Window, Qt::white);
	this->setPalette(pal);
	pal.setColor(QPalette::WindowText, *this->resourceManager->getDarkGrayColor());


	this->pokesIcon = new QLabel(this->scrollWidget);
	this->pokesIcon->setPixmap(this->resourceManager->getSmallIcon("poke"));
	this->pokes = new QCheckBox("Pokes", this->scrollWidget);
			this->pokes->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

	this->pokes->setGeometry(28, 0, this->pokes->width(), this->pokes->height());
	this->pokes->resize(this->pokes->minimumSizeHint());
	this->pokesIcon->setGeometry(6, 0, 22, this->pokes->height());

	this->messagesIcon = new QLabel(this->scrollWidget);
	this->messagesIcon->setPixmap(this->resourceManager->getSmallIcon("mail_request"));
	this->messages = new QCheckBox("Messages", this->scrollWidget);
	this->messages->setGeometry(this->pokes->x(), this->pokes->y() + this->pokes->height(), this->pokes->width(), this->messages->height());
	this->messagesIcon->setGeometry(this->pokesIcon->x(), this->messages->y(), 22, this->messages->height());

	this->wallMessagesIcon = new QLabel(this->scrollWidget);
	this->wallMessagesIcon->setPixmap(this->resourceManager->getSmallIcon("wall_post"));
	this->wallMessages = new QCheckBox("Wall Posts", this->scrollWidget);
	this->wallMessages->setGeometry(this->pokes->x(), this->messages->y() + this->messages->height(),  this->wallMessages->width(), this->wallMessages->height());
	this->wallMessagesIcon->setGeometry(this->pokesIcon->x(), this->wallMessages->y(), 22, this->wallMessages->height());


//	


//	
//	

	this->events = new QCheckBox("Events", this->scrollWidget);
	this->events->setGeometry(this->pokes->x(), 205 + 22, 130, 22);
}

FBNNotificationSettingsList::~FBNNotificationSettingsList()
{
	delete this->pokesIcon;
	delete this->pokes;

	delete this->messages;
	delete this->messagesIcon;
	delete this->wallMessages;
	delete this->wallMessagesIcon;

	delete this->events;

	delete this->scrollWidget;
}
void FBNNotificationSettingsList::save(FBNSettings &hash)
{

}
void FBNNotificationSettingsList::load(FBNSettings &hash)
{
	this->pokes->setChecked(hash.getBool("notifications_standard_show_pokes", true));
	this->messages->setChecked(hash.getBool("notifications_standard_show_messages", true));
	this->wallMessages->setChecked(hash.getBool("notifications_standard_show_wallMessages", true));

	this->events->setChecked(hash.getBool("notifications_advanced_show_events", true));

}

void FBNNotificationSettingsList::loadDefault() 
{
	this->pokes->setChecked(true);
	this->messages->setChecked(true);
	this->wallMessages->setChecked(true);
}

void FBNNotificationSettingsList::setGeometry(int x, int y, int width, int height)
{
	QScrollArea::setGeometry(x, y, width, height);
	this->scrollWidget->setGeometry(this->scrollWidget->x(), this->scrollWidget->y(), width - 25, this->scrollWidget->height());
}

void FBNNotificationSettingsList::paintEvent(QPaintEvent * e)
{
	QPainter p(this);
	p.fillRect(0, 0, this->width(), this->height(), QBrush(Qt::white));
}