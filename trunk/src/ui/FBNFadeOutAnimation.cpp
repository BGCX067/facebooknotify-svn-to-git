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

#include "FBNFadeOutAnimation.h"

FBNFadeOutAnimation::FBNFadeOutAnimation(QTimer *timer, QWidget *widget)
: FBNAnimation(FBNAnimation::AnimationType(animateOut), timer, widget)
{
	this->reset();
}

FBNFadeOutAnimation::~FBNFadeOutAnimation() { }
void FBNFadeOutAnimation::stepAnimation()
{
	this->_widget->setWindowOpacity(this->_widget->windowOpacity() - 0.01);
	emit step((FBNAnimation *)this);

	if (this->_widget->windowOpacity() == 0.0)
	{
		this->_timer->stop();
		emit done((FBNAnimation *)this);
	}
}
bool FBNFadeOutAnimation::isDone()
{
	if (this->_widget->windowOpacity() == 0.0)
		return true;
	else
		return false;
}
double FBNFadeOutAnimation::currentProgress()
{
	return (1.0 - this->_widget->windowOpacity());
}
void FBNFadeOutAnimation::reset()
{
	this->_widget->setWindowOpacity(1.0);
}
