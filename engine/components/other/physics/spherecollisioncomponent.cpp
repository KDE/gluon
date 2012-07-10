#include<btBulletDynamicsCommon.h>
#include<btBulletCollisionCommon.h>
#include<BulletCollision/CollisionShapes/btSphereShape.h>
#include<bullet/BulletCollision/CollisionDispatch/btEmptyCollisionAlgorithm.h>
#include "spherecollisioncomponent.h"


REGISTER_OBJECTTYPE( GluonEngine, SphereCollisionComponent )

using namespace GluonEngine;


int main () {

     btScalar radius;

     //  broadphase construction

    btBroadphaseInterface* broadphase = new btDbvtBroadphase();

    /** collision configuration

    and dispatcher
*/

    btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();

    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

  //solver

    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

  /** The world
          creation
    */

    btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);

    dynamicsWorld->setGravity(btVector3(0,-10,0));

     btCollisionShape*  sphereShape = new btSphereShape(radius);

     btDefaultMotionState* sphereMotionState =  new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));// adding falling sphere

      btScalar mass = 1;

      btVector3 sphereInertia(0,0,0);

       sphereShape->calculateLocalInertia(mass,sphereInertia);

       btRigidBody::btRigidBodyConstructionInfo sphereRigidBodyCI(mass,sphereMotionState,sphereShape,sphereInertia);

       btRigidBody* sphereRigidBody = new btRigidBody(sphereRigidBodyCI);

       dynamicsWorld->addRigidBody(sphereRigidBody);

        void start();

        void update( );

        void stop();

         dynamicsWorld->removeRigidBody(sphereRigidBody);

       delete sphereRigidBody->getMotionState();

       delete sphereRigidBody;

      delete sphereShape;

       delete dynamicsWorld;

       delete solver;

        delete dispatcher;

         delete collisionConfiguration;

          delete broadphase;

    return 0;
}

  void start()
 {
     void  processCollision (btCollisionObject *body0, btCollisionObject *body1, const btDispatcherInfo &dispatchInfo, btManifoldResult *resultOut);

     btScalar calculateTimeOfImpact (btCollisionObject *body0, btCollisionObject *body1, const btDispatcherInfo &dispatchInfo, btManifoldResult *resultOut);

 }

  void update()
  {

      void   btCollisionPairCallback (btDispatcherInfo &dispatchInfo, btCollisionDispatcher *dispatcher);

  }

  void stop()
  {

  }


