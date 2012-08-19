#ifndef GLUON_ENGINE_PHYSICSWORLD_H
#define GLUON_ENGINE_PHYSICSWORLD_H

#include <core/singleton.h>
#include <engine/component.h>
#include <btBulletDynamicsCommon.h>

namespace GluonEngine
{
class PhysicsWorld : public GluonCore::Singleton<PhysicsWorld> //Inherit template
 {
    Q_OBJECT
    GLUON_SINGLETON(PhysicsWorld) //Declare constructor and disable copying

  /*public:
        physicsworld ();
       ~physicsworld();
*/
       public:

          btDiscreteDynamicsWorld* dynamicsWorld;
};

}

#endif //GLUON_ENGINE_PHYSICSWORLD_H
