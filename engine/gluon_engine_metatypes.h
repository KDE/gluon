#ifndef GLUON_ENGINE_METATYPES_H
#define GLUON_ENGINE_METATYPES_H

#include <QtCore/QMetaType>

#include <core/gluonobject.h>
#include "asset.h"
#include "component.h"
#include "gameobject.h"
#include "gameproject.h"
#include "scene.h"

namespace
{
    struct GluonEngineMetaTypes
    {
        public:
            GluonEngineMetaTypes()
            {
                qRegisterMetaType<GluonEngine::Asset*>();
                qRegisterMetaType<GluonEngine::Component*>();
                qRegisterMetaType<GluonEngine::GameObject*>();
                qRegisterMetaType<GluonEngine::GameProject*>();
                qRegisterMetaType<GluonEngine::Scene*>();
            }
    };

    GluonEngineMetaTypes gluonEngineMetaTypes;
}

#endif // GLUON_ENGINE_METATYPES_H
