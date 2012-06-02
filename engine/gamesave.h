#ifndef GLUON_ENGINE_GAMESAVE_H
#define GLUON_ENGINE_GAMESAVE_H

#include <core/gluonobject.h>
#include "gluon_engine_export.h"

namespace GluonEngine
{
    class Scene;
    class GamePrivate;
    class Game;

    /*
     * For saving and loading game states, by serializing the 
     * current scene.
     */
    class GLUON_ENGINE_EXPORT GameSave : public GluonCore::GluonObject
    {
        Q_OBJECT
        GLUON_OBJECT( GluonEngine::GameSave )

    public:
	Q_INVOKABLE GameSave();
        ~GameSave();

        Q_INVOKABLE void save();
        Q_INVOKABLE void load();

        /*
         * Print the current contents of the scene, along with their properties.
         */
	Q_INVOKABLE void debugPrint(QObject *);
    };
}

Q_DECLARE_METATYPE( GluonEngine::GameSave* )
#endif
