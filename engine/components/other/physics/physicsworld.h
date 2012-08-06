#ifndef GLUON_ENGINE_PHYSICSWORLD_H
#define GLUON_ENGINE_PHYSICSWORLD_H

#include <core/singleton.h>
#include <engine/component.h>
#include <btBulletDynamicsCommon.h>

namespace GluonEngine
{
class physicsworld : public GluonCore::Singleton<physicsworld> //Inherit template
 {
    Q_OBJECT
    GLUON_SINGLETON(physicsworld) //Declare constructor and disable copying

  public:
        physicsworld ();
       ~physicsworld();

  private:
          btDiscreteDynamicsWorld* dynamicsWorld;

}; 

}

#endif //GLUON_ENGINE_PHYSICSWORLD_H
