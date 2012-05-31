#include "scene.h"
#include "gameprivate.h"
#include "game.h"
#include "achievementsmanager.h"
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

void GameSave::save()
{
  GluonCore::GluonObject *obj = Game::instance()->currentScene()->sceneContents();
  debug_print( obj );
  bool pause_flag = Game::instance()->isPaused();
  if( ! pause_flag )
    Game::instance()->setPause( true );
  QString dir = QDir::homePath().append( "/Desktop/" );
  QString savefile = QFileDialog::getSaveFileName(0, tr("Save Game"), dir, tr("Save Files (*.gs)"));
  QUrl filename(savefile);
  QList<GluonObject*> objectlist;
  objectlist.append( obj );
  AchievementsManager am;
  am.readFromProject(Game::instance()->gameProject()->achievements());
  if( am.achievementsCount() > 0 )
    am.save(dir);
  if(!GluonCore::GDLSerializer::instance()->write( filename, objectlist))
    qDebug() << "Error in writing to: " << filename.toString();
  if( ! pause_flag )
    Game::instance()->setPause( false );
}

void GameSave::load()
{
  //TODO: Give developer option to present list of saved slots to choose from.
  QList<GluonObject*> objectlist;
  QString dir = QDir::homePath().append( "/Desktop/" );
  QString savefile = QFileDialog::getOpenFileName(0, tr("Load Game"), dir, tr("Save Files (*.gs)"));
  QUrl filename(savefile);
  GluonEngine::Game::instance()->loadScene( filename );
  GluonCore::GluonObject *obj = GluonEngine::Game::instance()->currentScene()->sceneContents();
  AchievementsManager am;
  am.load(dir);
}

void GameSave::load( QString fileName )
{
}


#include "gamesave.moc"