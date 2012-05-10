#include "scene.h"
#include "gameprivate.h"
#include "game.h"
#include <core/gluonobject.h>
#include "gamesave.h"

using namespace GluonEngine;

REGISTER_OBJECTTYPE( GluonEngine, GameSave )

GameSave::GameSave( QObject* parent )
: GluonObject( parent )
{
}

GameSave::GameSave()
{
}

GameSave::~GameSave()
{
}

bool GameSave::save()
{
  Game *d = new Game();
  GamePrivate *d = new GamePrivate(q);
  QList<const GluonCore::GluonObject*> objectlist = d->listAllChildren();
  
}

bool GameSave::load()
{
}

bool GameSave::load( QString fileName )
{
}

#include "gamesave.moc"