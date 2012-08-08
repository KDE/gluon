#include "physicsworld.h"
#include<bullet/BulletCollision/CollisionDispatch/btCollisionWorld.h>

using namespace GluonEngine;


GLUON_DEFINE_SINGLETON(physicsworld) //Define the static variables

physicsworld::physicsworld( QObject* parent ): GluonCore::Singleton< physicsworld >( parent ) //Constructor definition
{

    // Build the broadphase
    btBroadphaseInterface* broadphase = new btDbvtBroadphase();

    // Set up the collision configuration and dispatcher
    btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();

    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

    // The actual physics solver
    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

   dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);

    dynamicsWorld->addRigidBody(btRigidBody);

    //void contactTest (btCollisionObject *colObj, ContactResultCallback &resultCallback  );

    //void contactPairTest (btCollisionObject *colObjA, btCollisionObject *colObjB, ContactResultCallback  &resultCallback);

    delete dynamicsWorld;
    delete solver ;
    delete dispatcher;
    delete collisionConfiguration;
    delete broadphase;
}




