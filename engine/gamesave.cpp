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
  GluonCore::GluonObject *obj = Game::instance()->currentScene()->sceneContents();
  bool pause_flag = true;
  if( !GluonEngine::Game::instance()->isPaused() )
  {
    GluonEngine::Game::instance()->setPause( true );
    pause_flag = false;
  }
  QString dir = QDir::homePath().append( "/Desktop/" );
  QString savefile = QFileDialog::getOpenFileName(0, tr("Save Game"), dir, tr("Save Files (*.gs)"));
  QUrl filename(savefile);
  QList<GluonObject*> objectlist;
  objectlist.append( obj );
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