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

#include "FBNServices.h"

void FBNServices::openEmailClient(QString address)
{
	QUrl url("mailto:" + address);
	this->openUrl(url);
}
void FBNServices::openWebBrowser(QString address)
{
	QUrl url(address);
	this->openUrl(url);
}

QString FBNServices::generateMD5Hash(const QString &str)
{
	string newstr = generateMD5Hash(str.toStdString());
	QString newval(newstr.c_str());
	return newval;
}
string FBNServices::generateMD5Hash(const string &str)
{
	md5_state_t state;
	md5_byte_t digest[16];
	char hex_output[16 * 2 + 1];
	int di;
	md5_init(&state);
	md5_append(&state, (const md5_byte_t *) str.c_str(), (int) strlen(str.c_str()));
	md5_finish(&state, digest );
	for (di = 0; di < 16; ++di)
		sprintf(hex_output + di * 2, "%02x", digest[di]);
	return string(hex_output);
}