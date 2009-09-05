#include "gluonmainwindow.h"
#include <KConfigDialog>
#include <KLocale>
#include <KStandardAction>
#include <KToggleAction>
#include <KAboutData>
#include <KService>
#include <KStandardDirs>
#include <KUrl>
#include <KRun>
#include <KMenuBar>
GluonMainWindow::GluonMainWindow(QWidget * parent)
    :KXmlGuiWindow(parent)
{
    KALEngine::getInstance();
    m_view = new KGLView;
    setCentralWidget(m_view);
    setupAction();



}

GluonMainWindow::~GluonMainWindow()
{

}

void GluonMainWindow::setupAction()
{

    KAction* startAction = new KAction(this);
    startAction->setText(i18n("start"));
    startAction->setIcon(KIcon("media-playback-start.png"));
    actionCollection()->addAction("start",startAction);
    connect(startAction,SIGNAL(triggered()),m_view,SLOT(start()));

    KAction* stopAction = new KAction(this);
    stopAction->setText(i18n("stop"));
    stopAction->setIcon(KIcon("media-playback-stop.png"));
    actionCollection()->addAction("stop",stopAction);
    connect(stopAction,SIGNAL(triggered()),m_view,SLOT(stop()));









    KAction* kglAction = new KAction(this);
    kglAction->setText(i18n("kgl config"));
    kglAction->setIcon(KIcon("kgl.png"));
    actionCollection()->addAction("kgl", kglAction);
    connect(kglAction,SIGNAL(triggered()),this,SLOT(showKglService()));
//

    KAction* kalAction = new KAction(this);
    kalAction->setText(i18n("kal config"));
    kalAction->setIcon(KIcon("kal.png"));
    actionCollection()->addAction("kal",kalAction);
    connect(kalAction,SIGNAL(triggered()),this,SLOT(showKalService()));

    KAction* kclAction = new KAction(this);
    kclAction->setText(i18n("kcl config"));
    kclAction->setIcon(KIcon("kcl.png"));
    actionCollection()->addAction("kcl",kclAction);
    connect(kclAction,SIGNAL(triggered()),this,SLOT(showKclSercice()));
    KStandardAction::fullScreen(m_view,SLOT(toggleFullScreen()),this,actionCollection());

        setupGUI();

        QMenu * menu = menuBar()->addMenu("gluon");
        menu->addAction(kglAction);
        menu->addAction(kalAction);
        menu->addAction(kclAction);
}

void GluonMainWindow::launchService(QString name)
{

    QString path = KStandardDirs::locate("services",name);
    KService service(path);

    KRun::run(service,KUrl(),this);



}
