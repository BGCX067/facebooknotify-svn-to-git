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

#ifndef FACEBOOK_POKES_H
#define FACEBOOK_POKES_H

#include <QString>
#include <QDomDocument>

#include "FBNKernelStructs.h"

namespace facebook
{
	class Pokes
	{

	public:
		Pokes();
		~Pokes();

		const facebook::PokeCount & count();
		const facebook::PokeCount & getCount(const QString &xml);
		void setCount(const facebook::PokeCount &count);

	protected:
		facebook::PokeCount _count;

	};
};
#endif
