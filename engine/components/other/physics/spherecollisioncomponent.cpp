#include<BulletCollision/CollisionShapes/btSphereShape.h>
//#include<bullet/BulletCollision/CollisionDispatch/btCollisionWorld.h>
#include<BulletCollision/BroadphaseCollision/btCollisionAlgorithm.h>
#include<bullet/BulletCollision/CollisionDispatch/btSphereSphereCollisionAlgorithm.h>
#include<bullet/BulletCollision/CollisionDispatch/btSphereBoxCollisionAlgorithm.h>
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
            sphere(0)
        {
        }

        int collisionGroup;
        int targetGroup;
        btScalar radius;
        btScalar radiusSquared;
        GameObject* collides;
        btCollisionShape* sphere;

        int componentType;
        const char* typeName;

   QVector< Component * > collisionComponents;
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
    d-> sphere= new btSphereShape( radius ) ;
    btDefaultMotionState* sphereMotionState =new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,-1,0)));
    btRigidBody::btRigidBodyConstructionInfo  sphereRigidBodyCI(1,sphereMotionState,sphereShape,btVector3(0,0,0));
    btRigidBody* sphereRigidBody = new btRigidBody(sphereRigidBodyCI);
    physicsworld::dynamicsWorld->addRigidBody(sphereRigidBody);
    btCollisionShape* box=new btBoxShape();
    physicsworld::dynamicsWorld->addRigidBody(body1);
}

void SphereCollisionComponent::start()
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
                  static_cast<SphereCollisionComponent*>( component )->addComponent( this );
              }
              else
              {
                  d->collisionComponents.replace( counter, 0 );
              }
              counter++;
          }
      }

void SphereCollisionComponent::update( int /* elapsedMilliseconds */)
{
    d->collides = 0;
      //our position
    QVector3D position = gameObject()->position();
     //Eliminate the Z-axis
    position.setZ( 0 );


    //Our radius, squared
    btScalar radius = d->radiusSquared;
    //Walk through the list
    const int componentCount = d->collisionComponents.count();
    Component** data = d->collisionComponents.data();
     for( int i = 0; i < componentCount; ++i )
      {
          SphereCollisionComponent* sphere = qobject_cast< SphereCollisionComponent* >( data[i] );
             if( sphere && sphere != this )
             {
                 //See if we are in the same group
                  if( sphere->collisionGroup() == d->targetGroup )
                  {
                      //Get the object's position
                      QVector3D otherPosition = sphere->gameObject()->position();
                      //Eliminate the Z axis
                      position.setZ( 0 );

                      //Get the object's radius
                      btScalar otherRadius = sphere->radiusSquared();

                      //Calculate the distance between our position and theirs
                      //Note that this is the squared distance to avoid a costly squareroot op
                      btScalar dist = ( otherPosition - position ).lengthSquared();

                      //If the distance between the two positions is smaller then the radius, we
                      //have a collision.
                      if( dist < ( otherRadius + radius ) )
                      {
                          d->collides = sphere->gameObject();
                      }
                  }
              }
          }
      }

void SphereCollisionComponent::stop()
{

}

void SphereCollisionComponent::cleanup()
{

    delete sphereShape;
}

int SphereCollisionComponent::collisionGroup() const
{
    return d->collisionGroup;
}

float SphereCollisionComponent::radius() const
{
    return d->radius;
}

float SphereCollisionComponent::radiusSquared() const
{
    return d->radiusSquared;
}

bool SphereCollisionComponent::isColliding() const
{
     return d->collides != 0;
}

QObject* SphereCollisionComponent::collidesWith() const
{
    return d->collides;
 }

void SphereCollisionComponent::setCollisionGroup( int group )
{
    d->collisionGroup = group;
}

int SphereCollisionComponent::targetGroup() const
{
    return d->targetGroup;
}

 void SphereCollisionComponent::setTargetGroup( int group )
{
    d->targetGroup = group;
}

 void SphereCollisionComponent::setRadius( btScalar radius )
{
    d->radius = radius;
    d->radiusSquared = radius * radius;
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
