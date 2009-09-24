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
#include <KStatusBar>
GluonMainWindow::GluonMainWindow(QWidget * parent)
    :KXmlGuiWindow(parent)
{
    m_view = new KGLView;

    setCentralWidget(m_view);
    setupAction();
    m_view->start();
    connect(m_view,SIGNAL(fpsChanged(int)),this,SLOT(showFps(int)));

}

GluonMainWindow::~GluonMainWindow()
{

}

void GluonMainWindow::setupAction()
{

    KAction* startAction = new KAction(this);
    startAction->setText(i18n("start"));
    startAction->setShortcut(Qt::Key_Enter);
    startAction->setIcon(KIcon("media-playback-start.png"));
    actionCollection()->addAction("start",startAction);
    connect(startAction,SIGNAL(triggered()),m_view,SLOT(start()));

    KAction* stopAction = new KAction(this);
    stopAction->setText(i18n("stop"));
    stopAction->setShortcut(Qt::Key_Pause);
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

    /*    KAction* controlAction = new KAction(this);
    controlAction->setText(i18n("controls...."));
    controlAction->setIcon(KIcon("games-config-options.png"));
    actionCollection()->addAction("setup controls",controlAction);
    connect(controlAction,SIGNAL(triggered()),this,SLOT(showControlWidget()))*/;


    QMenu * menu = menuBar()->addMenu("gluon");
    menu->addAction(kglAction);
    menu->addAction(kalAction);
    menu->addAction(kclAction);
    //     menu->addAction(controlAction);
}

void GluonMainWindow::launchService(QString name)
{

    QString path = KStandardDirs::locate("services",name);
    KService service(path);

    KRun::run(service,KUrl(),this);



}
void GluonMainWindow::showControlWidget()
{
    //    KCLVirtualInputConfig *  m_controlWidget = new KCLVirtualInputConfig(m_inputs);
    //    m_controlWidget->exec();

}
void GluonMainWindow::showFps(int fps)
{

    statusBar()->showMessage("fps:"+QString::number(fps));



}
