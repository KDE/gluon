 
#include "gamewindow.h"

#include <QDebug>
#include <QProcess>

GameWindow::GameWindow(QWidget *parent)
{
	//nothing?
}

void GameWindow::playGame( const QString& gameId )
{
	GluonPlayer::AllGameItemsModel *model
	= qobject_cast<GluonPlayer::AllGameItemsModel*>(GluonPlayer::GameManager::instance()->allGamesModel());
    const QString projectPath = model->data(gameId, GluonPlayer::AllGameItemsModel::UriRole).toString();
    
    if( projectPath.isEmpty() )
    {
        return;
    }
	
	//project path
    m_projectPath = projectPath;
    //project path as argument
    QStringList arguments;
    arguments << m_projectPath;
    //absolute string to gluonviewer
    QString viewer_bin = GluonCore::DirectoryProvider::instance()->installPrefix()+"/bin/gluonviewer";
    
    qDebug() << viewer_bin;
    
    QProcess * game_process = new QProcess(this);
    game_process->start(viewer_bin, arguments);
    
    game_process->waitForFinished(-1);

	qDebug() << game_process->readAllStandardOutput();
	qDebug() << game_process->readAllStandardError();
	
}

void GameWindow::endedGame()
{
	qDebug() << "game ended";
	emit finished();
}
