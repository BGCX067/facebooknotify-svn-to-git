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

#include "FBNAnimation.h"

FBNAnimation::FBNAnimation(AnimationType type, QTimer *timer, QWidget *widget)
{
	_type = type;
	_timer = timer;
	_widget = widget;
	
	this->reset();
}
FBNAnimation::~FBNAnimation() {}

void FBNAnimation::stepAnimation() {}
bool FBNAnimation::isDone() { return false; }
double FBNAnimation::currentProgress() { return 0.0; }
void FBNAnimation::reset() {}

FBNAnimation::AnimationType FBNAnimation::type()
{
	return this->_type;
}
