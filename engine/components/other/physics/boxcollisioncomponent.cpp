 
#include<BulletCollision/CollisionShapes/btBoxShape.h>
#include<bullet/BulletCollision/CollisionDispatch/btCollisionWorld.h>
#include<BulletCollision/BroadphaseCollision/btCollisionAlgorithm.h>
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
            radius( 1.0f ),
            collides( 0 ),
            box(0)
        {
        }

        int collisionGroup;
        int targetGroup;
        btScalar radius;
        btScalar radiusSquared;
        GameObject* collides;
        btCollisionShape* box;

        int componentType;
        const char* typeName;

         QVector<Component*> collisionComponents;
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
    d-> box= new btBoxShape( d->radius ) ;
    btDefaultMotionState* sphereMotionState =new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));
    btScalar mass = 1;
    //btRigidBody::setDamping (1, 1);
    btRigidBody::btRigidBodyConstructionInfo  sphereRigidBodyCI(mass,sphereMotionState,d->box,btVector3(0,0,0));
    btRigidBody* boxRigidBody = new btRigidBody(boxRigidBodyCI);
    physicsworld::dynamicsWorld->addRigidBody(boxRigidBody);
}

void BoxCollisionComponent::start()
 {
 //   void btCollisionAlgorithm::processCollision (btCollisionObject *body0, btCollisionObject *body1, const btDispatcherInfo &dispatchInfo, btManifoldResult *resultOut);

    //btScalar btCollisionAlgorithm::calculateTimeOfImpact (btCollisionObject *body0, btCollisionObject *body1, const btDispatcherInfo &dispatchInfo, btManifoldResult *resultOut);

    d->collisionComponents = gameObject()->scene()->sceneContents()->findComponentsInChildrenByType( d->componentType ).toVector();

    int counter = 0;
    foreach( Component *component, d->collisionComponents )
    {
             if( component->enabled() && component->gameObject()->enabled() )
              {
                  connect( component, SIGNAL(destroyed(QObject*)), SLOT(componentDestroyed(QObject*)) );
                  static_cast<BoxCollisionComponent*>( component )->addComponent( this );
              }
              else
              {
                  d->collisionComponents.replace( counter, 0 );
              }
              counter++;
          }
      }

void BoxCollisionComponent::update( int /* elapsedMilliseconds */)
{
    d->collides = 0;
      //our position
    QVector3D position = gameObject()->position();
     //Eliminate the Z-axis
    position.setZ( 0 );

    physicsworld::dynamicsWorld->contactTest(d, ContactDestroyedCallback &resultCallback);
    //Our radius, squared
    btScalar radius = d->radiusSquared;
    //Walk through the list
    const int componentCount = d->collisionComponents.count();
    Component** data = d->collisionComponents.data();
     for( int i = 0; i < componentCount; ++i )
      {
          BoxCollisionComponent* box = qobject_cast< BoxCollisionComponent* >( data[i] );
             if( sphere && sphere != this )
             {
                 //See if we are in the same group
                  if( box->collisionGroup() == d->targetGroup )
                  {
                      //Get the object's position
                      QVector3D otherPosition = box->gameObject()->position();
                      //Eliminate the Z axis
                      position.setZ( 0 );

                      //Get the object's radius
                      btScalar otherRadius = box->radiusSquared();

                      //Calculate the distance between our position and theirs
                      //Note that this is the squared distance to avoid a costly squareroot op
                      btScalar dist = ( otherPosition - position ).lengthSquared();

                      //If the distance between the two positions is smaller then the radius, we
                      //have a collision.
                      if( dist < ( otherRadius + radius ) )
                      {
                          d->collides = box->gameObject();
                      }
                  }
              }
          }
      }

void BoxCollisionComponent::stop()
{

}

void BoxCollisionComponent::cleanup()
{

    delete boxShape;
}

int BoxCollisionComponent::collisionGroup() const
{
    return d->collisionGroup;
}

float BoxCollisionComponent::radius() const
{
    return d->radius;
}

float BoxCollisionComponent::radiusSquared() const
{
    return d->radiusSquared;
}

bool BoxCollisionComponent::isColliding() const
{
     return d->collides != 0;
}

QObject* BoxCollisionComponent::collidesWith() const
{
    return d->collides;
 }

void BoxCollisionComponent::setCollisionGroup( int group )
{
    d->collisionGroup = group;
}

int BoxCollisionComponent::targetGroup() const
{
    return d->targetGroup;
}

 void BoxCollisionComponent::setTargetGroup( int group )
{
    d->targetGroup = group;
}

 void BoxCollisionComponent::setRadius( btScalar radius )
{
    d->radius = radius;
    d->radiusSquared = radius * radius;
}

 void BoxCollisionComponent::componentDestroyed( QObject* obj )
{
     if( !obj )
      return;

     Component* comp = static_cast<Component*>( obj );
      if( d->collisionComponents.contains( comp ) )
         d->collisionComponents.remove( d->collisionComponents.indexOf( comp ) );
}

 void BoxCollisionComponent::addComponent( BoxCollisionComponent* comp )
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

    Q_EXPORT_PLUGIN2( gluon_component_boxcollision, GluonEngine::BoxCollisionComponent )


#include "boxcollisioncomponent.moc"
