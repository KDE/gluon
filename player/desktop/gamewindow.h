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

class GameWindow : public KXmlGuiWindow
{
	Q_OBJECT
	public:
		GameWindow(QWidget *parent=0);
	
	public slots:
		void playGame( const QString& gameId );
	
	private slots:
		void startGame();
		
	private:
		QGraphicsObject *rootObject;
		QString m_projectPath;
		//methods
		void openProject( const QString& projectPath );
	
	signals:
		void quitted();
};

#endif
