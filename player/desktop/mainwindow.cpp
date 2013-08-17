#include "mainwindow.h"

#include <KApplication>
#include <KAction>
#include <KDebug>
#include <KLocale>
#include <KActionCollection>
#include <KStandardAction>

#include <QDir>
#include <QtDeclarative>

#include <QGLFormat>
#include <QGLWidget>

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

#include "loginform.h"
#include "registeruserform.h"
#include "userbox.h"

MainWindow::MainWindow(QWidget *parent)
{
	
	connect( GluonPlayer::ServiceProvider::instance(), SIGNAL(initializationFinished()), SLOT(connectedAttica()) );
    connect( GluonPlayer::ServiceProvider::instance(), SIGNAL(initializeFailed()), SLOT(failedAttica()) );
	
	setupActions();
	createQmlView();
}

/**
 * Set every menu item to their respective actions
 */
void MainWindow::setupActions()
{
	KAction * fileAction = new KAction(this);
	KAction * viewAction = new KAction(this);
	KAction * editAction = new KAction(this);
	KAction * settingsAction = new KAction(this);
	KAction * helpAction = new KAction(this);
	
	fileAction->setText(i18n("&File"));
	viewAction->setText(i18n("&View"));
	editAction->setText(i18n("&Edit"));
	settingsAction->setText(i18n("&Settings"));
	helpAction->setText(i18n("&Help"));
	
	actionCollection()->addAction("file", fileAction);
	actionCollection()->addAction("view", viewAction);
	actionCollection()->addAction("edit", editAction);
	//actionCollection()->addAction("settings", settingsAction);
	
	KStandardAction::quit(kapp, SLOT(quit()), actionCollection());
	
	setupGUI(Default, GluonCore::DirectoryProvider::instance()->dataDirectory()+"/apps/playerqmldesktop/gluonplayerdesktopui.rc");
}

/**
 * Create a QML view to be displayed as central widget.
 * This view supports the kdeclarative engine with all the plasma components.
 */
void MainWindow::createQmlView()
{
    qmlRegisterType<GluonPlayer::GameMetadata>( "Gluon.Player.Desktop", GLUON_VERSION_MAJOR,GLUON_VERSION_MINOR, "GameMetadata" );
    qmlRegisterType<GluonPlayer::CommentItemsModel>( "Gluon.Player.Desktop", GLUON_VERSION_MAJOR,GLUON_VERSION_MINOR, "CommentItemsModel" );
    qmlRegisterUncreatableType<GluonPlayer::GameItem>( "Gluon.Player.Desktop", GLUON_VERSION_MAJOR,GLUON_VERSION_MINOR, "GameItem", "To be used only for enums" );
    qmlRegisterUncreatableType<GluonPlayer::GameDownloadJob>( "Gluon.Player.Desktop", GLUON_VERSION_MAJOR,GLUON_VERSION_MINOR, "GameDownloadJob", "Get an instance from serviceProvider" );

	qmlRegisterType<LoginForm>("Gluon.Player.Desktop", GLUON_VERSION_MAJOR,GLUON_VERSION_MINOR, "LoginForm");
	qmlRegisterType<RegisterUserForm>("Gluon.Player.Desktop", GLUON_VERSION_MAJOR,GLUON_VERSION_MINOR, "RegisterUserForm");
	qmlRegisterType<UserBox>("Gluon.Player.Desktop", GLUON_VERSION_MAJOR,GLUON_VERSION_MINOR, "UserBox");
	
	qml_view = new QDeclarativeView (this);
	
	QGLFormat format = QGLFormat::defaultFormat();
	QGLWidget *glWidget = new QGLWidget(format);
	glWidget->setAutoFillBackground(false);
	
	kdeclarative.setDeclarativeEngine(qml_view->engine());
	kdeclarative.initialize();
	kdeclarative.setupBindings();
	
	qml_view->rootContext()->setContextProperty("mainWindow", this);
	qml_view->rootContext()->setContextProperty("_gluon_player_qml_version", "0.1");
	qml_view->rootContext()->setContextProperty( "installedGamesModel",
                                                          GluonPlayer::GameManager::instance()->installedGamesModel() );
    qml_view->rootContext()->setContextProperty( "downloadableGamesModel",
                                                          GluonPlayer::GameManager::instance()->downloadableGamesModel() );
    qml_view->rootContext()->setContextProperty( "serviceProvider",
                                                          GluonPlayer::ServiceProvider::instance() );
	qml_view->setViewport(glWidget);
	qml_view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
	
	loadQml(QString("main.qml"));
	qml_view->setResizeMode (QDeclarativeView::SizeRootObjectToView);
	resize (1300, 750);
	setCentralWidget (qml_view);
	
	rootObject = qml_view->rootObject();
}

/**
 * Load a particular qml file, used to change view by the application
 * 
 * @param filename the path to the QML file to be loaded
 */
void MainWindow::loadQml(QString filename)
{
	qml_view->setSource (QUrl::fromLocalFile (GluonCore::DirectoryProvider::instance()->dataDirectory()+"/apps/playerqmldesktop/qml/"+filename));
}

void MainWindow::connectedAttica()
{
	qDebug() << "attica -> init success!";
}

void MainWindow::failedAttica()
{
	qDebug() << "attica -> init failed!";
}


void MainWindow::playGame(const QString& gameId)
{
	GameWindow * game_window = new GameWindow;
	game_window->playGame(gameId);
}
