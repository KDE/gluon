#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <KXmlGuiWindow>
#include <QGraphicsObject>

#include <QDir>
#include <QtDeclarative>

#include <core/gluon_global.h>
#include <core/directoryprovider.h>

#include <lib/gamemetadata.h>
#include <lib/gamemanager.h>
#include <lib/models/commentitemsmodel.h>
#include <lib/serviceprovider.h>
#include <lib/models/allgameitemsmodel.h>
#include <lib/models/gameitem.h>
#include <lib/gamedownloadjob.h>

#include <engine/game.h>
#include <input/inputmanager.h>
#include <graphics/renderwidget.h>

#include <player/lib/serviceprovider.h>
#include <attica/providermanager.h>
#include <attica/provider.h>

class GameWindow : public QObject
{
	Q_OBJECT
	public:
		GameWindow(QWidget *parent=0);
	
	public slots:
		void playGame( const QString& gameId );
		void endedGame();
		
	private:
		QString m_projectPath;
	
	signals:
		void finished();
};

#endif
