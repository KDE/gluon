#ifndef GLUON_ENGINE_BOXCOLLISIONCOMPONENT_H
#define GLUON_ENGINE_BOXCOLLISIONCOMPONENT_H

#include <engine/component.h>
#include <engine/gluon_engine_export.h>
#include<bullet/LinearMath/btScalar.h>

namespace GluonEngine
{

    class GLUON_COMPONENT_PHYSICS_EXPORT  BoxCollisionComponent : public Component
    {
          Q_OBJECT
          Q_INTERFACES( GluonEngine::Component )
          GLUON_OBJECT( GluonEngine::BoxCollisionComponent )

           Q_PROPERTY( int collisionGroup READ collisionGroup WRITE setCollisionGroup )
           Q_PROPERTY( int targetGroup READ targetGroup WRITE setTargetGroup )


            Q_CLASSINFO( "org.gluon.category", "Physics" )
            Q_CLASSINFO( "org.gluon.icon", "application-x-executable" )

        public:

             Q_INVOKABLE BoxCollisionComponent( QObject* parent = 0 );

            virtual ~BoxCollisionComponent();    //destructor

            virtual QString category() const;

            virtual void  initialize() ;

            virtual void start();

            virtual void update(int elapsedMilliseconds );

            virtual void stop();

            virtual void cleanup();

            int collisionGroup() const;

            int targetGroup() const;



       public Q_SLOTS:

            void setCollisionGroup( int );

           void setTargetGroup( int group );

            void componentDestroyed( QObject* obj );

            void addComponent( BoxCollisionComponent*  comp );


 private:
        class BoxCollisionComponentPrivate;
        BoxCollisionComponentPrivate* const d;
    };

}

Q_DECLARE_METATYPE( GluonEngine::BoxCollisionComponent* )

#endif   // GLUON_ENGINE_BoxCollisionComponent_H 
