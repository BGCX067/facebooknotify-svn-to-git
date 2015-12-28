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

#include "FBNFadeInAnimation.h"

FBNFadeInAnimation::FBNFadeInAnimation(QTimer *timer, QWidget *widget)
: FBNAnimation(FBNAnimation::AnimationType(animateIn), timer, widget)
{
	this->reset();
}

FBNFadeInAnimation::~FBNFadeInAnimation() { }
void FBNFadeInAnimation::stepAnimation()
{
	this->_widget->setWindowOpacity(this->_widget->windowOpacity() + 0.01);
	emit step((FBNAnimation *)this);

	if (this->_widget->windowOpacity() == 1.0)
	{
		this->_timer->stop();
		emit done((FBNAnimation *)this);
	}
}
bool FBNFadeInAnimation::isDone()
{
	if (this->_widget->windowOpacity() == 1.0)
		return true;
	else
		return false;
}
double FBNFadeInAnimation::currentProgress()
{
	return this->_widget->windowOpacity();
}
void FBNFadeInAnimation::reset()
{
	this->_widget->setWindowOpacity(0);
}
