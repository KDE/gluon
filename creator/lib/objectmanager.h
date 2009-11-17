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

#ifndef GLUON_CREATOR_OBJECTMANAGER_H
#define GLUON_CREATOR_OBJECTMANAGER_H

#include "gluoncreatorlib_macros.h"

#include <common/ksingleton.h>

namespace Gluon {
class GameObject;

namespace Creator {

class GLUONCREATORLIB_EXPORT ObjectManager : public KSingleton<ObjectManager>
{
    Q_OBJECT
    public slots:
        Gluon::GameObject* createNewScene();
        Gluon::GameObject* createNewObject();

    signals:
        void newScene(Gluon::GameObject*);
        void newObject(Gluon::GameObject*);

    private:
        friend class KSingleton<ObjectManager>;

        ObjectManager() { m_objectId = 0; m_sceneId = 0; }
        ~ObjectManager() { }
        Q_DISABLE_COPY(ObjectManager)

        int m_objectId;
        int m_sceneId;
};

}

}

#endif // GLUON_CREATOR_OBJECTMANAGER_H
