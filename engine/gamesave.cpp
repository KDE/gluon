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
#include <iostream>

using namespace std;

using namespace GluonEngine;

REGISTER_OBJECTTYPE( GluonEngine, GameSave )

GameSave::GameSave()
{
}

GameSave::~GameSave()
{
}

void GameSave::debug_print(QObject* obj)
{
  for(int i = 0; i < obj->metaObject()->propertyCount(); i++)
  {
    QMetaProperty property = obj->metaObject()->property( i );
    cout << property.name() << ": " << property.read( obj ).toString().toStdString() << ' ';
  }
  cout << endl;
  foreach(QObject *ob, obj->children())
    debug_print( ob );
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
  QString savefile = QFileDialog::getSaveFileName(0, tr("Save Game"), dir, tr("Save Files (*.gs)"));
  QUrl filename(savefile);
  QList<GluonObject*> objectlist;
  objectlist.append( obj );
  if(!GluonCore::GDLSerializer::instance()->write( filename, objectlist))
    qDebug() << "Error in writing to: " << filename.toString();
  if( !pause_flag )
    GluonEngine::Game::instance()->setPause( false );
}

bool GameSave::save( QString path)
{
  GluonCore::GluonObject *obj = Game::instance()->currentScene()->sceneContents();
  QUrl filename( path );
  QList<GluonObject*> objectlist;
  objectlist.append( obj );
  if(!GluonCore::GDLSerializer::instance()->write( filename, objectlist))
    qDebug() << "Error in writing to: " << filename.toString();
}

bool GameSave::load()
{
  //TODO: Give developer option to present list of saved slots to choose from.
  QList<GluonObject*> objectlist;
  QString dir = QDir::homePath().append( "/Desktop/" );
  QString savefile = QFileDialog::getOpenFileName(0, tr("Load Game"), dir, tr("Save Files (*.gs)"));
  QUrl filename(savefile);
  GluonEngine::Game::instance()->loadScene( filename );
  GluonCore::GluonObject *obj = GluonEngine::Game::instance()->currentScene()->sceneContents();
  save( "/home/vsrao/Desktop/new.gs" );
}

bool GameSave::load( QString fileName )
{
}


#include "gamesave.moc"