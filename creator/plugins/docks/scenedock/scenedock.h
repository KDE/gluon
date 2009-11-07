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

#ifndef GLUON_CREATOR_SCENEDOCK_H
#define GLUON_CREATOR_SCENEDOCK_H

#include <widgets/dock.h>

namespace Gluon {

namespace Creator {

    class SceneDock : public Gluon::Creator::Dock
    {
        public:
            SceneDock(const QString& title, QWidget* parent = 0, Qt::WindowFlags flags = 0);
            ~SceneDock();

            virtual QAbstractItemView* view();
            virtual QAbstractItemModel* model();

        public slots:
            virtual void setSelection(Gluon::GluonObject* obj = 0);

        private:
            class SceneDockPrivate;
            SceneDockPrivate* d;
    };

}

}

#endif // GLUON_CREATOR_SCENEDOCK_H
