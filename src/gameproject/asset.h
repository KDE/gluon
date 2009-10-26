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

#ifndef GLUON_ASSET_H
#define GLUON_ASSET_H

#include "gluonobject.h"
#include <QUrl>
#include <QSharedData>

namespace Gluon
{
    class AssetPrivate;

    class Asset : public GluonObject
    {
        Q_OBJECT
        Q_PROPERTY(QString file READ file WRITE setFile)

        public:
            Asset(QObject * parent = 0);
            Asset(const Asset &other, QObject * parent = 0);
            ~Asset();

            GluonObject* instantiate();

            void setFile(const QString &newFile);
            QString file() const;

        Q_SIGNALS:
            void dataChanged();

        private:
            QSharedDataPointer<AssetPrivate> d;
    };
}

#endif				// GLUON_ASSET_H
