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
//   QFile file("/home/vsrao/Desktop/new.txt");
  ofstream of("/home/vsrao/Desktop/new.txt");
  of << obj->metaObject()->className() << '\n';
  GluonEngine::GamePrivate *d = new GluonEngine::GamePrivate(GluonEngine::Game::instance());
  QList<const GluonCore::GluonObject*> objects = d->listAllChildren( obj );
  foreach(const GluonCore::GluonObject *o, objects)
  {
    QString s = o->metaObject()->className();
    if ( s.compare("GluonEngine::GameObject") == 0)
    {
      of << s.toStdString() <<": "<< o->name().toStdString();
      GluonEngine::GameObject *ob = (GluonEngine::GameObject *)o;
      for(int i = 0; i < o->metaObject()->propertyCount(); i++ )
      {
	GluonCore::GluonObject* o = qobject_cast< GluonCore::GluonObject* >( ob );
	QMetaProperty property = o->metaObject()->property( i );
	of << property.name() << ' ';
	of << property.read( o ).toString().toStdString() << ' ';
      }
      of << '\n';
    }
  }
  of.close();
}

bool GameSave::load()
{
}

bool GameSave::load( QString fileName )
{
}


#include "gamesave.moc"