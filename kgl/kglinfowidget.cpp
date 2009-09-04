#include "kglinfowidget.h"
#include <QVBoxLayout>
#include <KTitleWidget>
#include <KIcon>
#include <KPushButton>
#include <QTextEdit>
#include "kglintroitem.h"
KGLInfoWidget::KGLInfoWidget(QWidget * parent)
    :QWidget(parent)
{

    QVBoxLayout * layout = new QVBoxLayout;


    m_information = new QWidget;
    m_preview = new QWidget;
    KTabWidget *tab = new KTabWidget;
    tab->addTab(m_preview,KIcon("run-build-configure.png"),"premview");
    tab->addTab(m_information,KIcon("run-build-file.png"),"information");

    KGLEngine * engine = new KGLEngine;
    m_view = new KGLView;
    m_view->setEngine(engine);
    m_view->start();
    m_view->setAxisShow(true);
    m_view->setInfoShow(true);
    KGLIntroItem * item = new KGLIntroItem;
    item->setPosition(-5,-5);
    item->updateTransform();

    engine->addItem(item);
    QVBoxLayout * subLayout = new QVBoxLayout;
    subLayout->addWidget(m_view);
    m_preview->setLayout(subLayout);
    layout->addWidget(tab);

    QHBoxLayout *hLayout = new QHBoxLayout;
    KPushButton *toggleButton = new KPushButton(KIcon("go-last.png"),"start/stop");
    hLayout->addWidget(toggleButton);
    hLayout->addStretch();
    subLayout->addLayout(hLayout);

    connect(toggleButton,SIGNAL(pressed()),m_view,SLOT(toogleActive()));
    setLayout(layout);

    setupInformation();

}

void KGLInfoWidget::setupInformation()
{
    QLabel * logo = new QLabel;
    QTextEdit * edit = new QTextEdit;
   logo->setPixmap(KIcon("media-flash").pixmap(128,128));
    logo->setAlignment(Qt::AlignTop);

    QWidget * main = new QWidget;
    QString info("");

    info+="<p>Vendor : <b>"+QString((char*)glGetString(GL_VENDOR)) + "</b></p>";
    info+="<p>Render : <b>"+QString((char*)glGetString(GL_RENDERER))+ "</b></p>";
    info+="<p>Version : <b>"+QString((char*)glGetString(GL_VERSION))+ "</b></p>";
    info+="<p> <b>"+(m_view->isShaderSupported())?"Shader support : yes" : "Shader support : no"; info+="</b></p>";
    info+="<p>extensions : </p>";
    edit->setText(QString((char*)glGetString(GL_EXTENSIONS)));

    QLabel * label = new QLabel;
    label->setText(info);
    QVBoxLayout * lv = new QVBoxLayout;
    lv->addWidget(label);
    lv->addWidget(edit);

    QHBoxLayout * lh = new QHBoxLayout;
    lh->addWidget(logo);
    lh->addLayout(lv);
    m_information->setLayout(lh);


}
