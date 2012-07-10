
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

            Q_CLASSINFO( "org.gluon.category", "Physics" )

            Q_CLASSINFO( "org.gluon.icon", "application-x-executable" )

             public:

            Q_INVOKABLE SphereCollisionComponent( QObject* parent = 0 );

            virtual ~SphereCollisionComponent();

            virtual QString category() const;

            virtual void start();

            virtual void update( );

            virtual void stop();

             Q_INVOKABLE bool isColliding() const;

            Q_INVOKABLE QObject* collidesWith() const;

             public Q_SLOTS:


    };

SphereCollisionComponent* d;
}

Q_DECLARE_METATYPE( GluonEngine::SphereCollisionComponent* )

#endif // GLUON_ENGINE_SPHERECOLLISIONCOMPONENT_H
