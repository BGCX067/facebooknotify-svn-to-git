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

#include "FBNLinkButton.h"

FBNLinkButton::FBNLinkButton(FBNResourceManager * rm, QWidget * w): QPushButton(w)
{

	QCursor hand(Qt::PointingHandCursor);
	this->setCursor(hand);

	this->resourceManager = rm;

	this->mouseOver = false;
	this->_hoverUnderline = true;

	this->_autoLaunch = true;
	this->_wordWrap = false;

	QObject::connect(this, SIGNAL(clicked()), this, SLOT(clickedUrl()));
}

FBNLinkButton::~FBNLinkButton(void)
{

}


void FBNLinkButton::paintEvent(QPaintEvent * e)
{
	QPainter p(this);
	p.fillRect(0, 0, this->width(), this->height(), QBrush(Qt::white));
	p.setPen(*this->resourceManager->getDarkBlueColor());

	QFont fontToUse = *this->resourceManager->getSmallNormalFont();
	fontToUse.setUnderline(true);

	if (!mouseOver && _hoverUnderline)
		fontToUse.setUnderline(false);

	p.setFont(fontToUse);

	int flags = Qt::AlignCenter;
	if (_wordWrap)
		flags |= Qt::TextWordWrap;

	p.drawText(0, 0, this->width(), this->height(), flags, this->text());
}

void FBNLinkButton::enterEvent(QEvent * e)
{
	this->mouseOver = true;
	repaint();
}

void FBNLinkButton::leaveEvent(QEvent * e)
{
	this->mouseOver = false;
	repaint();
}

bool FBNLinkButton::hoverUnderline()
{
	return _hoverUnderline;
}

void FBNLinkButton::setHoverUnderline(bool value)
{
	_hoverUnderline = value;
	repaint();
}

QString FBNLinkButton::url()
{
	return _url;
}
void FBNLinkButton::setUrl(const QString &url)
{
	_url = url;
}

bool FBNLinkButton::autoLaunch()
{
	return _autoLaunch;
}
void FBNLinkButton::setAutoLaunch(bool val)
{
	_autoLaunch = val;
}

void FBNLinkButton::clickedUrl()
{
	if (_url.length() && _autoLaunch)
		this->resourceManager->openWebBrowser(_url);
}

bool FBNLinkButton::wordWrap()
{
	return _wordWrap;
}
void FBNLinkButton::setWordWrap(bool val)
{
	_wordWrap = val;
	repaint();
}