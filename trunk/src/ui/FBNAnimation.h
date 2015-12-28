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

#ifndef FBNANIMATION_H
#define FBNANIMATION_H

//#include "FBNUI_includes.h"

#include <QObject>
#include <QWidget>
#include <QTimer>


class FBNAnimation : public QObject
{

	Q_OBJECT

public:
	enum AnimationType { animateIn, animateOut };

	FBNAnimation(AnimationType type, QTimer *timer, QWidget *widget);
	virtual ~FBNAnimation();

	virtual void stepAnimation();
	virtual bool isDone();
	virtual double currentProgress();
	virtual void reset();

	AnimationType type();

signals:
	void done(FBNAnimation *animation);
	void step(FBNAnimation *animation);

protected:
	QTimer * _timer;
	QWidget * _widget;

private:
	AnimationType _type;

};

#endif
