#include "mainwindow.h"

#include <KApplication>
#include <KAction>
#include <KDebug>
#include <KLocale>
#include <KActionCollection>
#include <KStandardAction>

#include <QDir>
 
MainWindow::MainWindow(QWidget *parent) : KXmlGuiWindow(parent)
{
	setupActions();
	createQmlView();
}

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
	
	setupGUI(Default, QDir::currentPath()+"/gluonplayerdesktopui.rc");
}

/*
 * Create a QML view to be displayed as central widget
 */
void MainWindow::createQmlView()
{
	qml_view = new QDeclarativeView (this);
	
	kdeclarative.setDeclarativeEngine(qml_view->engine());
	kdeclarative.initialize();
	kdeclarative.setupBindings();
	
	qml_view->rootContext()->setContextProperty("mainwindow", this);
	qml_view->rootContext()->setContextProperty("_gluon_player_qml_version", "0.1");
	
	qml_view->setSource (QUrl::fromLocalFile ("qml/loginscreen.qml"));
	qml_view->setResizeMode (QDeclarativeView::SizeRootObjectToView);
	resize (300, 300);
	setCentralWidget (qml_view);
}
