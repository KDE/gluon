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

///TODO: Make this something entirely different... QVariant wrapped Eigen types, wooh! ;)

#ifndef GLUON_VARIANTTYPES
#define GLUON_VARIANTTYPES

#ifndef EIGEN_CORE_H
#warning This needs to be included AFTER Eigen and friends
#endif

#include <QVariant>
#include <Eigen/Geometry>

Q_DECLARE_METATYPE(Eigen::Vector3d)
//qRegisterMetatype<Eigen::Vector3d>("Eigen::Vector3d");

#endif