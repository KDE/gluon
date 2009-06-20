#include <QLayout>
#include <QLabel>
#include <QX11Info>
#include <KDebug>
#include <QTextEdit>
#include "kglconfig.h"



KGLConfig::KGLConfig(QWidget * parent)
    :QWidget(parent)
{

    m_tab = new QTabWidget;
    QVBoxLayout * layout = new QVBoxLayout;
    m_desktop = new QDesktopWidget;
    m_view = new KGLView;
    KGLEngine * engine = new KGLEngine;
    m_view->setEngine(engine);
    KGLBoxItem * box = new KGLBoxItem(-5,-5);
    box->setTexture(QPixmap(":kgl.png"));
    engine->addItem(box);


    setupInformation();
    setupTest();

    layout->addWidget(m_tab);
    setLayout(layout);


}
void KGLConfig::setupInformation()
{

    QLabel * logo = new QLabel;
    QPixmap * pix = new QPixmap(64,64);
    QTextEdit * edit = new QTextEdit;
    pix->load(":vga.png");
    logo->setPixmap(pix->scaledToWidth(128));
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
    main->setLayout(lh);
    m_tab->addTab(main,"information");
}


void KGLConfig:: setupTest()
{
    m_tab->addTab(m_view,"test");






}
