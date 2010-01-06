#include "kglinfowidget.h"
#include <QtGui/QVBoxLayout>
#include <QtGui/QIcon>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>
#include "kglintroitem.h"
KGLInfoWidget::KGLInfoWidget(QWidget * parent)
    :QWidget(parent)
{

    QVBoxLayout * layout = new QVBoxLayout;


    m_information = new QWidget;
    m_preview = new QWidget;
    QTabWidget *tab = new QTabWidget;
    tab->addTab(m_preview,QIcon("run-build-configure.png"), tr("Preview"));
    tab->addTab(m_information,QIcon("run-build-file.png"), tr("Information"));

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
    QPushButton *toggleButton = new QPushButton(QIcon("go-last.png"), tr("Start/Stop"));
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
    logo->setPixmap(QIcon("media-flash").pixmap(128,128));
    logo->setAlignment(Qt::AlignTop);

    QWidget * main = new QWidget;
    QString info("");

    info+=tr("<p>Vendor: <b>%1</b></p>").arg(QString((char*)glGetString(GL_VENDOR)));
    info+=tr("<p>Render: <b>%1</b></p>").arg( QString((char*)glGetString(GL_RENDERER)));
    info+=tr("<p>Version: <b>%1</b></p>").arg( QString((char*)glGetString(GL_VERSION)));
    if (m_view->isShaderSupported()) info+=tr("<p> <b>Shader support: yes</b></p>");
    else info+=tr("<p> Shader support: <b>no</b></p>");
    info+=tr("<p>Extensions: </p>");
    edit->setText(QString((char*)glGetString(GL_EXTENSIONS)).replace(' ', '\n'));
    edit->setReadOnly(true);

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
