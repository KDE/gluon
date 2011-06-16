#include "btcomponents-testapp.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtCore/QUrl>

#include <core/gluonobjectfactory.h>
#include <engine/gameproject.h>
#include <engine/game.h>
#include <core/gdlhandler.h>

btcomponentstestapp::btcomponentstestapp()
{
    GluonCore::GluonObjectFactory::instance()->loadPlugins();
}

btcomponentstestapp::~btcomponentstestapp()
{}

void
btcomponentstestapp::run(QUrl gdlFile)
{
    GluonEngine::GameProject *gameProject = new GluonEngine::GameProject(QCoreApplication::instance());
    gameProject->loadFromFile(gdlFile);
    
    GluonEngine::Game::instance()->setParent(QCoreApplication::instance());
    GluonEngine::Game::instance()->setGameProject(gameProject);
    
    //qDebug() << "The gameProject turned into GDL:" << gameProject->toGDL();
    
    // Run the game at severely reduced speed (one frame per second) so we can
    // actually see what's happening
    GluonEngine::Game::instance()->runGameFixedTimestep(1);
}

#include "btcomponents-testapp.moc"
