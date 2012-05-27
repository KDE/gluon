#ifndef GLUON_ENGINE_GAMESAVE_H
#define GLUON_ENGINE_GAMESAVE_H

#include "scene.h"
#include "game.h"
#include "gameprivate.h"
#include <core/gluonobject.h>
#include "gluon_engine_export.h"
#include <creator/dialogs/configdialog.h>
#include <core/gdlserializer.h>

namespace GluonEngine
{
    class Scene;
    class GamePrivate;
    class Game;
    
    class GLUON_ENGINE_EXPORT GameSave : public GluonCore::GluonObject
    {
        Q_OBJECT
        GLUON_OBJECT( GluonEngine::GameSave )

    public:
	GameSave();
        ~GameSave();

        bool save();
	bool save( QString );
        bool load();
        bool load( QUrl fileUrl );
        bool load( QString fileName );
	void debug_print(QObject *);
    };
}

Q_DECLARE_METATYPE( GluonEngine::GameSave* )
#endif
