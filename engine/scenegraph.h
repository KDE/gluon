#ifndef GLUON_ENGINE_SCENEGRAPH_H
#define GLUON_ENGINE_SCENEGRAPH_H

#include <QObject>
#include <core/gluonobject.h>
#include "gluon_engine_export.h"
#include "scenegraphobject.h"

namespace GluonEngine
{
    class GLUON_ENGINE_EXPORT SceneGraph : public GluonCore::GluonObject
    {
        Q_OBJECT
        GLUON_OBJECT( GluonEngine::SceneGraph )

	SceneGraphObject* root;

    public:
        Q_INVOKABLE SceneGraph();
        ~SceneGraph();
    };
}

Q_DECLARE_METATYPE( GluonEngine::SceneGraph* )
#endif