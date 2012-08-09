#include "physicsworld.h"
#include<BulletDynamics/btBulletDynamicsCommon.h>
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

    void contactTest (btCollisionObject *colObj, ContactDestroyedCallback &resultCallback );

    void contactPairTest (btCollisionObject *colObjA, btCollisionObject *colObjB, ContactDestroyedCallback  &resultCallback);

    delete dynamicsWorld;
    delete solver ;
    delete dispatcher;
    delete collisionConfiguration;
    delete broadphase;
}




