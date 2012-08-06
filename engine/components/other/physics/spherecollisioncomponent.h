#ifndef GLUON_ENGINE_SPHERECOLLISIONCOMPONENT_H
#define GLUON_ENGINE_SPHERECOLLISIONCOMPONENT_H

#include <engine/component.h>


namespace GluonEngine
{

    class GLUON_COMPONENT_SPHERECOLLISION_EXPORT SphereCollisionComponent : public Component
    {
            Q_OBJECT
            Q_INTERFACES( GluonEngine::Component )
            GLUON_OBJECT( GluonEngine::SphereCollisionComponent )

            Q_PROPERTY( int collisionGroup READ collisionGroup WRITE setCollisionGroup )
            Q_PROPERTY( int targetGroup READ targetGroup WRITE setTargetGroup )
            Q_PROPERTY( float radius READ radius WRITE setRadius )

            Q_CLASSINFO( "org.gluon.category", "Physics" )
            Q_CLASSINFO( "org.gluon.icon", "application-x-executable" )

             public:

            Q_INVOKABLE SphereCollisionComponent( QObject* parent = 0 );      // constructor

            virtual ~SphereCollisionComponent();    //destructor

            virtual QString category() const;

            virtual void  initialize() ;

            virtual void start();

            virtual void update(  );

            virtual void stop();

            virtual void cleanup();

             Q_INVOKABLE bool isColliding() const;

            Q_INVOKABLE QObject* collidesWith() const;


       public Q_SLOTS:

        void setCollisionGroup( int group );

        void setRadius( float radius );

        void componentDestroyed( QObject* obj );

        void addComponent( SphereCollisionComponent*  comp );

        void setTargetGroup( int group );


    private:
        class SphereCollisionComponentPrivate;
        SphereCollisionComponentPrivate* const d;
    };

}

Q_DECLARE_METATYPE( GluonEngine::SphereCollisionComponent* )

#endif // GLUON_ENGINE_SphereCollisionComponent_H
