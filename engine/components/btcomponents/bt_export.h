/*
<one line to give the program's name and a brief idea of what it does.>
Copyright (C) <year>  <name of author>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef BTCOMPONENT_EXPORT_H
#define BTCOMPONENT_EXPORT_H

#include <QtCore/qglobal.h>

#ifndef BTCOMPONENT_EXPORT
#if defined(MAKE_BTCOMPONENT_LIB)
#  define BTCOMPONENT_EXPORT Q_DECL_EXPORT
#else
#  define BTCOMPONENT_EXPORT Q_DECL_IMPORT
#endif
#endif

# ifndef BTCOMPONENT_EXPORT_DEPRECATED
#  define BTCOMPONENT_EXPORT_DEPRECATED Q_DECL_DEPRECATED BTCOMPONENT_EXPORT
# endif


#endif
