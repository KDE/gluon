#include<BulletCollision/CollisionShapes/btSphereShape.h>
#include<BulletCollision/CollisionShapes/btBoxShape.h>
#include<bullet/BulletCollision/CollisionDispatch/btCollisionWorld.h>
#include<BulletCollision/BroadphaseCollision/btCollisionAlgorithm.h>
#include<BulletCollision/CollisionDispatch/btSphereSphereCollisionAlgorithm.h>
#include<BulletCollision/CollisionDispatch/btSphereBoxCollisionAlgorithm.h>
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
        //btScalar radiusSquared;
        GameObject* collides;
        btCollisionObject* sphere;
        btCollisionObject*sphere1;
        btCollisionObject* box;


        int componentType;
        const char* typeName;

         QVector<Component*>  collisionComponents;
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
    btRigidBody::sphereRigidBody->setDamping(1,1);
   //adding rigidbody to the world
    physicsworld::dynamicsWorld->addRigidBody(sphereRigidBody);
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
      physicsworld::dynamicsWorld->addRigidBody(sphereRigidBody1);
     // creation of the box shape
      btBoxShape::setSafeMargin(boxHalfExtents);
      d->box=new btBoxShape( btVector3  &boxHalfExtents);
      // adding box shape to world
      physicsworld::dynamicsWorld->addRigidBody(d->box);
}

void SphereCollisionComponent::start()
 {
    // collecting collision components using bullets Numfolds method
    d->collisionComponents = physicsworld::dynamicsWorld->getDispatcher()->getNumManifolds()->findComponentsInChildrenByType( d->componentType ).toVector();
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

void SphereCollisionComponent::update( int /* elapsedMilliseconds */)
{

    d->collides = 0;
    physicsworld::dynamicsWorld->stepSimulation(0.0083,1,0.(1.0/60.0));
    //our position
    QVector3D position = gameObject()->position();
    //Eliminate the Z-axis
    position.setZ( 0 );
   //check wheteher the object is colliding with any other in the physics world
    ContactDestroyedCallback *resultCallback;
     physicsworld::dynamicsWorld->contactTest(d->sphere, resultCallback->m_collisionFilterGroup);
     int  numManifolds =physicsworld::dynamicsWorld->getBulletCollisionWorld()->getDispatcher()->getNumManifolds();
     if(numManifolds>0 )
      {
         //non blockable signal emitted before object is desroyed and  remove that index of  component using Slot
          connect( component, SIGNAL(destroyed(QObject*)), SLOT(setCollisionGroup(int numManifolds)) );
         //append the component,so  counter  gives the count  of enabled components
          static_cast<SphereCollisionComponent*>( component )->addComponent( this );
       }

    //check whether the object is colliding with  other sphere
     ContactDestroyedCallback *ResultCallback;

     physicsworld::dynamicsWorld->contactPairTest(d->sphere,d->sphere,ResultCallback->m_collisionFilterGroup);

     btSphereSphereCollisionAlgorithm (btPersistentManifold *contactManifold, d->sphere, d->sphere1);

     btScalar toc;

     toc=calculateTimeOfImpact (d->sphere, d->sphere1, physicsworld::dynamicsWorld->getDispatchInfo());

     for (int i=0;i<numManifolds;i++)
      {
           btPersistentManifold* contactManifold =physicsworld::dynamicsWorld->getDispatcher() ->getManifoldByIndexInternal(i);
           d->sphere =static_cast<btCollisionObject*>(contactManifold->getBody0());
           d-> sphere1=static_cast<btCollisionObject*>(contactManifold->getBody1());
           d-> numContacts = contactManifold->getNumContacts();
       }
     btSphereSphereCollisionAlgorithm (btPersistentManifold *contactManifold, d->sphere, d->sphere1);

     //checkwhether the object is colliding with box shape in the physics world
     physicsworld::dynamicsWorld->contactPairTest(d->sphere,d->box,ContactDestroyedCallback &resultCallback);

     btSphereBoxCollisionAlgorithm (btPersistentManifold *contactManifold, d->sphere, d->box);

     btScalar TOC;

     TOC=calculateTimeOfImpact (d->sphere, d->box, physicsworld::dynamicsWorld->getDispatchInfo());

     for (int j=0;j<numManifolds;j++)
     {
         btPersistentManifold* contactManifold =physicsworld::dynamicsWorld->getDispatcher() ->getManifoldByIndexInternal(j);
         d->sphere =static_cast<btCollisionObject*>(contactManifold->getBody0());
         d-> box=static_cast<btCollisionObject*>(contactManifold->getBody1());
         d->numContacts = contactManifold->getNumContacts();
      }

     const int componentCount ;

    componentCount= d->collisionComponents.count();

    Component** data;

    data = d->collisionComponents.data();

     d->collides = sphere->gameObject();

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

int SphereCollisionComponent::collisionGroup() const
{
    return d->collisionGroup;
}

float SphereCollisionComponent::radius() const
{
    return d->radius;
}


void SphereCollisionComponent::setCollisionGroup( int numManifolds )
{
    d->collisionGroup = numManifolds;
}

int SphereCollisionComponent::targetGroup() const
{
    return d->targetGroup;
}

 void SphereCollisionComponent::setRadius( btScalar radius )
{
    d->radius = radius;

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

Q_EXPORT_PLUGIN2( gluon_component_spherecollision, GluonEngine::SphereCollisionComponent )


#include "spherecollisioncomponent.moc"
