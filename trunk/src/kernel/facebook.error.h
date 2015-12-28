//	fbNotify: A Facebook notification system.
//	Copyright (C) 2006 fbNotify Team.
//
//	This program is free software, you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 2 of the License, or
//	(at your option) any later version.
//
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY, without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License along
//	with this program, if not, write to the Free Software Foundation, Inc.,
//	51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

#ifndef FACEBOOK_ERROR_H
#define FACEBOOK_ERROR_H

#include <QString>
#include <QDomDocument>

#include "FBNKernelStructs.h"
#include "../core/FBNLogger.h"

namespace facebook
{
	class Error
	{
	public:
		Error(FBNLogger * logger = 0);
		~Error();

		const facebook::ErrorData & error();
		const facebook::ErrorData & getError(const QString &xml);
		void setError(const facebook::ErrorData &error);

	protected:
		facebook::ErrorData _error;

		FBNLogger * _logger;

	};

}
#endif
