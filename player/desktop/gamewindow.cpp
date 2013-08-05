 
#include "gamewindow.h"

#include <QDebug>

GameWindow::GameWindow(QWidget *parent)
{
	//nothing?
}

void GameWindow::playGame( const QString& gameId )
{
	GluonPlayer::AllGameItemsModel *model
	= qobject_cast<GluonPlayer::AllGameItemsModel*>(GluonPlayer::GameManager::instance()->allGamesModel());
    const QString projectPath = model->data(gameId, GluonPlayer::AllGameItemsModel::UriRole).toString();
    openProject(projectPath);
}

void GameWindow::startGame()
{
	GluonCore::GluonObjectFactory::instance()->loadPlugins();
    GluonEngine::GameProject *project = new GluonEngine::GameProject( this );
    project->loadFromFile(m_projectPath);
    GluonEngine::Game::instance()->setGameProject( project );
    GluonEngine::Game::instance()->setCurrentScene( project->entryPoint() );

    GluonEngine::Game::instance()->runGame();
	
	emit quitted();
	
	close();
}

void GameWindow::openProject( const QString& projectPath )
{
	if( projectPath.isEmpty() )
    {
        return;
    }

    m_projectPath = projectPath;
	
    GluonGraphics::RenderWidget *widget = new GluonGraphics::RenderWidget( this );
    setCentralWidget( widget );
    widget->setFocus();
    connect( GluonEngine::Game::instance(), SIGNAL(painted(int)), widget, SLOT(update()) );
    GluonInput::InputManager::instance()->setFilteredObject( widget );
    QTimer::singleShot( 100, this, SLOT(startGame()) );
}