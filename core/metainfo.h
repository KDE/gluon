/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef GLUONCORE_METAINFO_H
#define GLUONCORE_METAINFO_H

#include <QtCore/QString>

namespace GluonCore
{
    class GluonObject;
    class MetaInfo
    {
        public:
            MetaInfo(GluonObject* parent);
            MetaInfo(const MetaInfo& other);
            ~MetaInfo();

            void setPropertyRange(const QString& property, qreal min, qreal max);
            bool hasPropertyRange(const QString& property) const;
            qreal propertyRangeMin(const QString& property) const;
            qreal propertyRangeMax(const QString& property) const;
            void removePropertyRange(const QString& property);

            void setPropertyStep(const QString& property, qreal step);
            bool hasPropertyStep(const QString& property) const;
            qreal propertyStep(const QString& property) const;
            void removePropertyStep(const QString& property);

        private:
            class MetaInfoPrivate;
            MetaInfoPrivate* d;
    };
}

#endif // GLUONCORE_METAINFO_H
