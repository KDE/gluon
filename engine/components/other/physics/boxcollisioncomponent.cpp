#include<BulletCollision/CollisionShapes/btBoxShape.h>
#include<BulletCollision/CollisionShapes/btSphereShape.h>
#include<BulletCollision/BroadphaseCollision/btCollisionAlgorithm.h>
#include<BulletCollision/CollisionDispatch/btSphereSphereCollisionAlgorithm.h>
#include<BulletCollision/CollisionDispatch/btSphereBoxCollisionAlgorithm.h>
#include "gameobject.h"
#include "scene.h"
#include "boxcollisioncomponent.h"
#include "physicsworld.h"



REGISTER_OBJECTTYPE( GluonEngine, BoxCollisionComponent )

using namespace GluonEngine;

class BoxCollisionComponent::BoxCollisionComponentPrivate
{
    public:
            BoxCollisionComponentPrivate() :
            collisionGroup( 0 ),
            targetGroup( 0 ),
            boxHalfExtents(0),
            collides( 0 ),
            box(0),
            box1(0),
            sphere(0),
            numContacts(0)
        {
        }

        int collisionGroup;
        int targetGroup;
        btVector3 boxHalfExtents;
        int  numContacts;
        GameObject* collides;
        btCollisionShape* box;
        btCollisionShape*box1;
        btCollisionShape* sphere;

        int componentType;
        const char* typeName;

         QVector<Component*>  collisionComponents;
};


struct btDrawingResult : public btCollisionWorld::ContactResultCallback
{
    btScalar	addSingleResult(btManifoldPoint& cp,	const btCollisionObject* colObj0,int partId0,int index0,const btCollisionObject* colObj1,int partId1,int index1)
    {

        btVector3 ptA = cp.getPositionWorldOnA();
        btVector3 ptB = cp.getPositionWorldOnB();

          return 0;
      }
};

BoxCollisionComponent::BoxCollisionComponent( QObject* parent )
  : Component( parent )
  , d( new BoxCollisionComponentPrivate )
{
     d->componentType = qMetaTypeId<GluonEngine::BoxCollisionComponent*>();
}

BoxCollisionComponent::~BoxCollisionComponent()
{
    delete d;
}

QString BoxCollisionComponent::category() const
{
    return QString( "Physics" );
}

void  BoxCollisionComponent::initialize()
{
   //creating a boxshape
    d->box= new btBoxShape(&d->boxHalfExtents) ;//-----------------------------------------------------------------------------
    //setting default motionstate making unused Quaterion 1is set for non used coordinate
    btDefaultMotionState* boxMotionState =new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));//---------------------------------
    //setting default mass 1 not zero  because need minimum inertia
    btScalar mass = 1;
    //construction info of sphere Rigidbody
    btRigidBody::btRigidBodyConstructionInfo  boxRigidBodyCI(mass,boxMotionState,d->box,btVector3(0,0,0));//-------------------------------------------
    //construction of the rigid body
    btRigidBody* boxRigidBody = new btRigidBody(boxRigidBodyCI);//------------------------------------------
    //setting up default
     boxRigidBody->setDamping(1,1);//-------------------------------------------------------------------
    //adding rigidbody to the world
     PhysicsWorld::instance()->dynamicsWorld->addRigidBody(boxRigidBody);//----------------------------------------------
     //creating a new sphereshape
     d->box1=new btBoxShape(&d->boxHalfExtents);//-----------------------------------------------------------------------
     //setting default motionstate making unused Quaterion
      btDefaultMotionState* boxMotionState1 =new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));//-----------------------------------
     //setting default mass 1 not zero  because need minimum inertia
      btScalar mass1 = 1;//------------------------------------------------------------------------------------
      //construction info of sphere Rigidbody
      btRigidBody::btRigidBodyConstructionInfo  boxRigidBodyCI1(mass1,boxMotionState1,d->box1,btVector3(0,0,0));//--------------------------
     //construction of the rigid body
      btRigidBody* boxRigidBody1 = new btRigidBody(boxRigidBodyCI1);//---------------
      //setting up default
       boxRigidBody1->setDamping (1, 1);//----------------------------------
      //adding rigidbody to the world
       PhysicsWorld::instance()->dynamicsWorld->addRigidBody(boxRigidBody1);//-----------------------------------
      // creation of the box shape
       btScalar radius ;
       d->sphere=new btSphereShape( radius);//--------------------------------------
      // adding box shape to world
       btDefaultMotionState* sphereMotionState =new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));//--------------------
      //construction info
       btRigidBody::btRigidBodyConstructionInfo  sphereRigidBodyCI(mass,sphereMotionState,d->sphere,btVector3(0,0,0));//--------------------------------
       //box rigidbody
        btRigidBody* sphereRigidBody = new btRigidBody(sphereRigidBodyCI);//------------------------------------------------------
       //set damping to default
        boxRigidBody->setDamping(1,1);//--------------------------------------------------------
       //adding box to world
        PhysicsWorld::instance()->dynamicsWorld->addRigidBody(boxRigidBody);//--------------------------------------------------
}

void BoxCollisionComponent::start()
{

    d->collisionComponents = gameObject()->scene()->sceneContents()->findComponentsInChildrenByType( d->componentType ).toVector();

    int counter = 0;

    foreach( Component *component, d->collisionComponents )
    {
        //check whether the component is enabled and instance of the component is enabled
         if( component->enabled() && component->gameObject()->enabled() )
         {
            //non blockable signal emitted before object is desroyed and  remove that index of  component using Slot
              connect( component, SIGNAL(destroyed(QObject*)), SLOT(componentDestroyed(QObject*)) );
            //append the component,so  counter  gives the count  of enabled components
               static_cast<BoxCollisionComponent*>( component )->addComponent( this );
           }
           else
           {
                //if no components are enabled make it zero
                 d->collisionComponents.replace( counter, 0 );
             }
              counter++;
      }
}

void BoxCollisionComponent::update( int  elapsedMilliseconds )
{
    int timestep=elapsedMilliseconds;

    d->collides = 0;

    PhysicsWorld::instance()->dynamicsWorld->stepSimulation((timestep/1000),1,(1/60));

    //our position
    QVector3D position = gameObject()->position();
    //Eliminate the Z-axis
     position.setZ( 0 );
   //check wheteher the object is colliding with any other in the physics world
     int componentCount = d->collisionComponents.count();

     btCollisionObject*box1;//------------------------

     btCollisionObject*sphere;//---------------------------------------------------------
       //data about colllision of game objects
     Component** data = d->collisionComponents.data();
    //declaration of spherecollision object for  contact Test
     btCollisionObject* box;//------------------------------------------------
    // Variable drawn from structure provides collision information after test to world
     btDrawingResult renderCallback;

     for( int i = 0; i < componentCount; ++i )
     {
         BoxCollisionComponent* Box = qobject_cast< BoxCollisionComponent* >( data[i] );//--------------------------------------
          // checking if the collision group and target group are same
         if( d->collisionGroup == d->targetGroup )
         {
             // contactTest checks collision between sphere and all objects of the world
             PhysicsWorld::instance()->dynamicsWorld->contactTest(box,renderCallback);//-------------------------------------------------------
             // nummanifolds get the number of contactpoints between sphere and and objects in world
             int  numManifolds =PhysicsWorld::instance()->dynamicsWorld->getDispatcher()->getNumManifolds();//---------------------------------------

             PhysicsWorld::instance()-> dynamicsWorld->performDiscreteCollisionDetection();

             Component* component;
              // numManifolds >0 shows collision has occured since contactpoints are present
             if(numManifolds>0 )
             {
                  //non blockable signal emitted before object is desroyed and  remove that index of  component using Slot
                 connect(  component, SIGNAL(destroyed(QObject*)), SLOT(setCollisionGroup(int numManifolds)) );
                 //append the component,so  counter  gives the count  of enabled components
                  static_cast<BoxCollisionComponent*>( component )->addComponent( this );//--------------------------------------------
               }

                //contactPairTest checks whether the object is colliding with other sphere object in the world
               PhysicsWorld::instance()->dynamicsWorld->contactPairTest(box,box1,renderCallback);//--------------------------------------------
              {
                   btPersistentManifold* contactManifold =PhysicsWorld::instance()->dynamicsWorld->getDispatcher() ->getManifoldByIndexInternal(i);

                   d->box =static_cast<btCollisionShape*>(contactManifold->getBody0());//-------------------------------------

                   d-> box1=static_cast<btCollisionShape*>(contactManifold->getBody1());//-------------------------------------------------
                //get number of contactpoints between two spheres
                   d-> numContacts = contactManifold->getNumContacts();
                }

               //checkwhether the object is colliding with box shape in the physics world

                 PhysicsWorld::instance()->dynamicsWorld->contactPairTest(box,sphere,renderCallback);//------------------------------------------

                 for (int j=0;j<numManifolds;j++)
                 {

                   btPersistentManifold* contactManifold =PhysicsWorld::instance()->dynamicsWorld->getDispatcher() ->getManifoldByIndexInternal(j);

                   d->box=static_cast<btCollisionShape*>(contactManifold->getBody0());//----------------------------------

                   d-> box=static_cast<btCollisionShape*>(contactManifold->getBody1());//-------------------------------------------------
                  //get number of contact points between sphere and the box
                   d->numContacts = contactManifold->getNumContacts();
                  }

                d->collides =Box->gameObject();//-----------------------------------
             }
        }
}

void BoxCollisionComponent::stop()
{

}

void BoxCollisionComponent::cleanup()
{

     delete d->box;
     delete d->box1;
     delete d->sphere;
}

int BoxCollisionComponent::collisionGroup()const
{
    return d->collisionGroup;
}

btScalar BoxCollisionComponent::radius( )const//--------------------------------------------------
{
    return  d->radius;
}


void BoxCollisionComponent::setCollisionGroup( int numManifolds )
{
    d->collisionGroup = numManifolds;
}

int BoxCollisionComponent::targetGroup() const
{
    return d->targetGroup;
}

 void BoxCollisionComponent::componentDestroyed( QObject* obj )
{
     if( !obj )
      return;

     Component* comp = static_cast<Component*>( obj );
      //if object is destroyed remove the index of it
     if( d->collisionComponents.contains( comp ) )

          d->collisionComponents.remove( d->collisionComponents.indexOf( comp ) );
}

 void BoxCollisionComponent::addComponent( BoxCollisionComponent* comp )
{
    if( comp )
    {   // add the components which are not destroyed in collision
         if( !d->collisionComponents.contains( comp ) )
          {
               d->collisionComponents.append( comp );

               connect( comp, SIGNAL(destroyed(QObject*)), this, SLOT(componentDestroyed(QObject*)) );
           }
     }
}

Q_EXPORT_PLUGIN2( gluon_component_physics, GluonEngine::BoxCollisionComponent )

#include "boxcollisioncomponent.moc"

