#include "mainwindow.h"

#include <KApplication>
#include <KAction>
#include <KDebug>
#include <KLocale>
#include <KActionCollection>
#include <KStandardAction>

#include <QDir>
#include <QtDeclarative>

#include "loginform.h"
#include "registeruserform.h"

MainWindow::MainWindow(QWidget *parent) : KXmlGuiWindow(parent)
{
	//needed by the ocs server
	connect( GluonPlayer::ServiceProvider::instance(), SIGNAL(initializationFinished()), SLOT(initDone()) );
	connect( GluonPlayer::ServiceProvider::instance(), SIGNAL(initializeFailed()), SLOT(initFailed()) );
	
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
	
	setupGUI(Default, QDir::currentPath()+"/bin/gluonplayerdesktopui.rc");
}

/**
 * Create a QML view to be displayed as central widget.
 * This view supports the kdeclarative engine with all the plasma components.
 */
void MainWindow::createQmlView()
{
	
	qmlRegisterType<LoginForm>("GluonComponents", 1,0, "LoginForm");
	qmlRegisterType<RegisterUserForm>("GluonComponents", 1,0, "RegisterUserForm");
	
	qml_view = new QDeclarativeView (this);
	
	kdeclarative.setDeclarativeEngine(qml_view->engine());
	kdeclarative.initialize();
	kdeclarative.setupBindings();
	
	qml_view->rootContext()->setContextProperty("mainwindow", this);
	qml_view->rootContext()->setContextProperty("_gluon_player_qml_version", "0.1");
	
	loadQml(QString("main.qml"));
	qml_view->setResizeMode (QDeclarativeView::SizeRootObjectToView);
	resize (300, 300);
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
	qml_view->setSource (QUrl::fromLocalFile ("bin/qml/"+filename));
}

/**
 * Used to initialize the attica connection to the OCS server.
 * Must be called before the first request.
 */
void MainWindow::initAttica()
{
	GluonPlayer::ServiceProvider::instance()->init();
}

/**
 * Handle the case in which attica could connect to the specified OCS server
 */
void MainWindow::initDone()
{
    kDebug() << "INFO: successfully connected to OCS server";
}

/**
 * Handle the case in which attica could not connect to the specified OCS server
 */
void MainWindow::initFailed()
{
    kDebug() << "WARNING: could not connect to OCS server";
}

