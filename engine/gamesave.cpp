#include "scene.h"
#include "gameprivate.h"
#include "game.h"
#include <core/gluonobject.h>
#include "gamesave.h"
#include "gameobject.h"
#include <fstream>
#include <iostream>
#include <QList>
#include <QtCore/QMetaProperty>
#include <QFile>
#include <QObject>
#include <QUrl>
#include <core/gdlserializer.h>

using namespace GluonEngine;
using namespace std;
using namespace GluonCreator;

REGISTER_OBJECTTYPE( GluonEngine, GameSave )

GameSave::GameSave()
{
}

GameSave::~GameSave()
{
}

bool GameSave::save(GluonCore::GluonObject *obj)
{
  QUrl filename("/home/vsrao/Desktop/new.txt");
  GluonEngine::GamePrivate *d = new GluonEngine::GamePrivate(GluonEngine::Game::instance());
  QList< const GluonCore::GluonObject*> objects = d->listAllChildren( obj );
  QList<GluonObject*> objectlist;
  foreach(const GluonCore::GluonObject *o, objects)
  {
    QString s = o->metaObject()->className();
    if ( s.compare("GluonEngine::GameObject") == 0)
      objectlist.append((GluonObject *) o);
  }
  GluonCore::GDLSerializer::instance()->write( filename, objectlist);
}

bool GameSave::load()
{
}

bool GameSave::load( QString fileName )
{
}


#include "gamesave.moc"