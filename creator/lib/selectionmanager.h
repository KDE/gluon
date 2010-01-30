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

#ifndef GLUON_CREATOR_SELECTIONMANAGER_H
#define GLUON_CREATOR_SELECTIONMANAGER_H

#include <core/singleton.h>

#include "gluoncreator_macros.h"

namespace GluonCore {
    class GluonObject;
}

namespace GluonCreator {

class GLUONCREATOR_EXPORT SelectionManager : public GluonCore::Singleton<SelectionManager>
{
    Q_OBJECT
    public:
        typedef QList<GluonCore::GluonObject*> SelectionList;
        SelectionList selection() const;

    public slots:
        void setSelection(const SelectionList& selection);

    signals:
        void selectionChanged(SelectionManager::SelectionList);

    private:
        friend class GluonCore::Singleton<SelectionManager>;
        SelectionManager();
        ~SelectionManager();
        Q_DISABLE_COPY(SelectionManager)

        class SelectionManagerPrivate;
        SelectionManagerPrivate *d;
};

}

#endif // GLUON_CREATOR_SELECTIONMANAGER_H
