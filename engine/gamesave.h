#ifndef GLUON_ENGINE_GAME_H
#define GLUON_ENGINE_GAME_H

#include "scene.h"
#include "game.h"
#include <core/gluonobject.h>
#include "gluon_engine_export.h"
#include <core/gdlserializer.h>

namespace GluonEngine
{
    class Scene;
    class Game;
    class gdlserializer;
    
    class GLUON_ENGINE_EXPORT GameSave : public GluonCore::GluonObject
    {
        Q_OBJECT
        GLUON_OBJECT( GluonEngine::GameSave )

    public:
        GameSave( QObject* parent );
	GameSave();
        ~GameSave();

        bool save();
        bool load();
        bool load( QUrl fileUrl );
        bool load( QString fileName );
    };
}
Q_DECLARE_METATYPE( GluonEngine::GameSave* )
#endif