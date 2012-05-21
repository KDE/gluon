#include "scene.h"
#include "gameprivate.h"
#include "game.h"
#include <core/gluonobject.h>
#include "gamesave.h"
#include "gameobject.h"
#include <QList>
#include <QtCore/QMetaProperty>
#include <QDir>
#include <QFileDialog>
#include <QObject>
#include <core/gdlserializer.h>
#include <QDebug>
#include <engine/gameproject.h>

using namespace GluonEngine;
using namespace GluonCreator;

REGISTER_OBJECTTYPE( GluonEngine, GameSave )

GameSave::GameSave()
{
}

GameSave::~GameSave()
{
}

bool GameSave::save()
{
  GluonCore::GluonObject *obj = Game::instance()->currentScene()->root();
  bool pause_flag = true;
  if( !GluonEngine::Game::instance()->isPaused() )
  {
    GluonEngine::Game::instance()->setPause( true );
    pause_flag = false;
  }
  QString dir = QDir::homePath().append( "/Desktop/" );
  QString savefile = QFileDialog::getOpenFileName(0, tr("Save Game"), dir, tr("Save Files (*.gs)"));
  QUrl filename(savefile);
  GluonEngine::GamePrivate *d = new GluonEngine::GamePrivate(GluonEngine::Game::instance());
  QList< const GluonCore::GluonObject*> objects = d->listAllChildren( obj );
  QList<GluonObject*> objectlist;
  foreach(const GluonCore::GluonObject *o, objects)
  {
    QString s = o->metaObject()->className();
    if ( s.compare("GluonEngine::GameObject") == 0)
      objectlist.append((GluonObject *) o);
  }
  if(!GluonCore::GDLSerializer::instance()->write( filename, objectlist))
    qDebug() << "Error in writing to: " << filename.toString();
  if( !pause_flag )
    GluonEngine::Game::instance()->setPause( false );
}

bool GameSave::load()
{
}

bool GameSave::load( QString fileName )
{
}


#include "gamesave.moc"