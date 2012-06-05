#ifndef GLUON_ENGINE_SCENEGRAPH_H
#define GLUON_ENGINE_SCENEGRAPH_H

#include <QObject>
#include <engine/gameobject.h>
#include "gluon_engine_export.h"
#include "scenegraphobject.h"

namespace GluonEngine
{
    class GLUON_ENGINE_EXPORT SceneGraph: public QObject
    {
        Q_OBJECT
	SceneGraphObject* root;

    public:
        Q_INVOKABLE SceneGraph();
        SceneGraph( GluonEngine::GameObject* parent );
        ~SceneGraph();

        Q_INVOKABLE SceneGraphObject* getRoot();

        /**
         * Populate the scene graph with all the scene contents
         */
        Q_INVOKABLE void populate( SceneGraphObject *object, int level );
        /**
         * For testing; print the scene graph
         */
        Q_INVOKABLE void debugprint( SceneGraphObject *object, int level );
        Q_INVOKABLE void debugprint( SceneGraphObject *object );
    };
}

Q_DECLARE_METATYPE( GluonEngine::SceneGraph* )
#endif