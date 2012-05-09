#include "gamesave.h"
#include "scene.h"
#include "game.h"
#include <core/gluonobject.h>

using namespace GluonEngine;

GameSave::GameSave( QObject* parent )
: GluonObject( parent )
, d( new Game )
{
}

GameSave::~GameSave()
{
}