#include<BulletCollision/CollisionShapes/btSphereShape.h>
#include<BulletCollision/CollisionShapes/btBoxShape.h>
#include<BulletCollision/BroadphaseCollision/btCollisionAlgorithm.h>
#include<BulletCollision/CollisionDispatch/btSphereSphereCollisionAlgorithm.h>
#include<BulletCollision/CollisionDispatch/btSphereBoxCollisionAlgorithm.h>
#include "gameobject.h"
#include "scene.h"
#include "spherecollisioncomponent.h"
#include "physicsworld.h"



REGISTER_OBJECTTYPE( GluonEngine, SphereCollisionComponent )

using namespace GluonEngine;

class SphereCollisionComponent::SphereCollisionComponentPrivate
{
    public:
        SphereCollisionComponentPrivate() :
            collisionGroup( 0 ),
            targetGroup( 0 ),
            radius( 1.0f ),
            collides( 0 ),
            sphere(0),
            sphere1(0),
            box(0),
            numContacts(0)
        {
        }

        int collisionGroup;
        int targetGroup;
        btScalar radius;
        int  numContacts;
        GameObject* collides;
        btCollisionShape* sphere;
        btCollisionShape*sphere1;
        btCollisionShape* box;

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

SphereCollisionComponent::SphereCollisionComponent( QObject* parent )
  : Component( parent )
  , d( new SphereCollisionComponentPrivate )
{
     d->componentType = qMetaTypeId<GluonEngine::SphereCollisionComponent*>();
}

SphereCollisionComponent::~SphereCollisionComponent()
{
    delete d;
}

QString SphereCollisionComponent::category() const
{
    return QString( "Physics" );
 }

void  SphereCollisionComponent::initialize()
{
    //creating a sphereshape
    d->sphere= new btSphereShape( d->radius ) ;
    //setting default motionstate making unused Quaterion 1is set for non used coordinate
    btDefaultMotionState* sphereMotionState =new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));
    //setting default mass 1 not zero  because need minimum inertia
    btScalar mass = 1;
    //construction info of sphere Rigidbody
    btRigidBody::btRigidBodyConstructionInfo  sphereRigidBodyCI(mass,sphereMotionState,d->sphere,btVector3(0,0,0));
    //construction of the rigid body
    btRigidBody* sphereRigidBody = new btRigidBody(sphereRigidBodyCI);
    //setting up default
     sphereRigidBody->setDamping(1,1);
    //adding rigidbody to the world
     PhysicsWorld::instance()->dynamicsWorld->addRigidBody(sphereRigidBody);
     //creating a new sphereshape
     d->sphere1=new btSphereShape(d->radius);
     //setting default motionstate making unused Quaterion
      btDefaultMotionState* sphereMotionState1 =new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));
     //setting default mass 1 not zero  because need minimum inertia
      btScalar mass1 = 1;
      //construction info of sphere Rigidbody
      btRigidBody::btRigidBodyConstructionInfo  sphereRigidBodyCI1(mass1,sphereMotionState1,d->sphere1,btVector3(0,0,0));
     //construction of the rigid body
      btRigidBody* sphereRigidBody1 = new btRigidBody(sphereRigidBodyCI1);
      //setting up default
      sphereRigidBody1->setDamping (1, 1);
      //adding rigidbody to the world
       PhysicsWorld::instance()->dynamicsWorld->addRigidBody(sphereRigidBody1);
       btVector3 boxHalfExtents;
      // creation of the box shape
       d->box=new btBoxShape( boxHalfExtents);
       //setSafeMargin(boxHalfExtents,.1f);
      // adding box shape to world
       btDefaultMotionState* boxMotionState =new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));
      //construction info
       btRigidBody::btRigidBodyConstructionInfo  boxRigidBodyCI(mass,boxMotionState,d->box,btVector3(0,0,0));
       //box rigidbody
        btRigidBody* boxRigidBody = new btRigidBody(sphereRigidBodyCI);
       //set damping to default
        boxRigidBody->setDamping(1,1);
       //adding box to world
        PhysicsWorld::instance()->dynamicsWorld->addRigidBody(boxRigidBody);
}

void SphereCollisionComponent::start()
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
               static_cast<SphereCollisionComponent*>( component )->addComponent( this );
           }
           else
           {
                //if no components are enabled make it zero
                 d->collisionComponents.replace( counter, 0 );
             }
              counter++;
      }
}

void SphereCollisionComponent::update( int  elapsedMilliseconds )
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

     btCollisionObject*sphere1;

     btCollisionObject*box;

     Component** data = d->collisionComponents.data();

     btCollisionObject* sphere;

     btDrawingResult renderCallback;

     for( int i = 0; i < componentCount; ++i )
     {
         SphereCollisionComponent* Sphere = qobject_cast< SphereCollisionComponent* >( data[i] );

         if( d->collisionGroup == d->targetGroup )
         {
             PhysicsWorld::instance()->dynamicsWorld->contactTest(sphere,renderCallback);

             int  numManifolds =PhysicsWorld::instance()->dynamicsWorld->getDispatcher()->getNumManifolds();

             PhysicsWorld::instance()-> dynamicsWorld->performDiscreteCollisionDetection();

             Component* component;

             if(numManifolds>0 )
             {
                  //non blockable signal emitted before object is desroyed and  remove that index of  component using Slot
                 connect(  component, SIGNAL(destroyed(QObject*)), SLOT(setCollisionGroup(int numManifolds)) );
                 //append the component,so  counter  gives the count  of enabled components
                  static_cast<SphereCollisionComponent*>( component )->addComponent( this );
               }

                 //check whether the object is colliding with  other sphere
               PhysicsWorld::instance()->dynamicsWorld->contactPairTest(sphere,sphere1,renderCallback);

               btPersistentManifold* contactManifold =PhysicsWorld::instance()->dynamicsWorld->getDispatcher() ->getManifoldByIndexInternal(i);

               d->sphere =static_cast<btCollisionShape*>(contactManifold->getBody0());

               d-> sphere1=static_cast<btCollisionShape*>(contactManifold->getBody1());

               d-> numContacts = contactManifold->getNumContacts();

               //checkwhether the object is colliding with box shape in the physics world

               PhysicsWorld::instance()->dynamicsWorld->contactPairTest(sphere,box,renderCallback);

               for (int j=0;j<numManifolds;j++)
               {

                   btPersistentManifold* contactManifold =PhysicsWorld::instance()->dynamicsWorld->getDispatcher() ->getManifoldByIndexInternal(j);

                   d->sphere =static_cast<btCollisionShape*>(contactManifold->getBody0());

                   d-> box=static_cast<btCollisionShape*>(contactManifold->getBody1());

                   d->numContacts = contactManifold->getNumContacts();
                 }

                d->collides =Sphere->gameObject();
             }
        }
}

void SphereCollisionComponent::stop()
{

}

void SphereCollisionComponent::cleanup()
{

     delete d->sphere;
     delete d->sphere1;
     delete d->box;
}

int SphereCollisionComponent::collisionGroup()const
{
    return d->collisionGroup;
}

btScalar SphereCollisionComponent::radius( )const
{
    return  d->radius;
}


void SphereCollisionComponent::setCollisionGroup( int numManifolds )
{
    d->collisionGroup = numManifolds;
}

int SphereCollisionComponent::targetGroup() const
{
    return d->targetGroup;
}

 void SphereCollisionComponent::componentDestroyed( QObject* obj )
{
     if( !obj )
      return;

     Component* comp = static_cast<Component*>( obj );
      if( d->collisionComponents.contains( comp ) )

          d->collisionComponents.remove( d->collisionComponents.indexOf( comp ) );
}

 void SphereCollisionComponent::addComponent( SphereCollisionComponent* comp )
{
    if( comp )
    {
         if( !d->collisionComponents.contains( comp ) )
          {
               d->collisionComponents.append( comp );

               connect( comp, SIGNAL(destroyed(QObject*)), this, SLOT(componentDestroyed(QObject*)) );
           }
     }
}

Q_EXPORT_PLUGIN2( gluon_component_physics, GluonEngine::SphereCollisionComponent )

#include "spherecollisioncomponent.moc"
