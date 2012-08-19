#include "physicsworld.h"
#include<BulletDynamics/btBulletDynamicsCommon.h>
#include<bullet/BulletCollision/CollisionDispatch/btCollisionWorld.h>

using namespace GluonEngine;


GLUON_DEFINE_SINGLETON(PhysicsWorld) //Define the static variables

PhysicsWorld::PhysicsWorld( QObject* parent ): GluonCore::Singleton< PhysicsWorld >( parent ) //Constructor definition
{

    // Build the broadphase
    btBroadphaseInterface* broadphase = new btDbvtBroadphase();

    // Set up the collision configuration and dispatcher
    btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();

    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

    // The actual physics solver
    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

     dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);

     //dynamicsWorld->addRigidBody(btRigidBody);------------------------------------------------------------------------------------------------


     void contactTest (btCollisionObject *colObj, btCollisionWorld::ContactResultCallback &resultCallback );

     void contactPairTest (btCollisionObject *colObjA, btCollisionObject *colObjB,btCollisionWorld::ContactResultCallback &resultCallback);



    delete dynamicsWorld;
    delete solver ;
    delete dispatcher;
    delete collisionConfiguration;
    delete broadphase;
}




