#include "kglview.h"
#include <KDebug>
KGLView:: KGLView( QSize size, float frameRate ,QWidget* parent)
         :QGLWidget(parent)
{
    init();
    resize(size);
    setFrameRate(frameRate);
}

KGLView::KGLView(QWidget * parent)
         :QGLWidget(parent)
{
    init();

}

KGLView::KGLView(KGLEngine * engine,QWidget * parent )
{
   init();
   setEngine(engine);


}
bool KGLView::initGlew()
{

    GLenum code;
    kDebug()<<"Glew initialisation....";
    /* initialisation de GLEW */
    code = glewInit();
    if(code != GLEW_OK)
    {
        kDebug()<< "cannot init GLEW :"<<glewGetErrorString(code);
        return false;
    }
    kDebug()<<"Glew success...";

    if ( isExtensionSupported("GL_ARB_shading_language_100" )
        && isExtensionSupported("GL_ARB_shader_objects")
        && isExtensionSupported("GL_ARB_vertex_shader")
        && isExtensionSupported("GL_ARB_fragment_shader"))
        {
        kDebug()<<"Shaders supported...";
        m_isShaderSupported = true;
    }
    else
    {
        kDebug()<<"Shaders unsupported...";
        m_isShaderSupported = false;
    }

    return true;

}

void  KGLView::init()
{
    m_engine = NULL;
    m_frameRate = 16.6;
    m_timer = new QTimer(this);
    m_fpsTimer = new QTimer(this);
    m_countFrame = 0;
    m_fps = 1000/m_frameRate;
    m_isShaderSupported = false;
    m_sleep=true;
    m_axisShow = false;
    m_infoShow = false;
    m_ratio = width() / height();
    setOrthoView(-10,10,-10,10);
    m_mode = GL_FILL;
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
    setAutoBufferSwap(true);
    glInit();
    initGlew();
    connect(m_timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    connect(m_fpsTimer, SIGNAL(timeout()), this, SLOT(calculFps()));

}
void KGLView::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA ,GL_ONE);
    glPolygonMode(GL_FRONT_AND_BACK, m_mode);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glDisable(GL_DEPTH_TEST);
    setAutoBufferSwap(true);


}
void KGLView::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(m_orthoView.left(),m_orthoView.right() ,m_orthoView.bottom(), m_orthoView.top());
}


void  KGLView::paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if ( engine() != NULL)drawGLItems();
    glColor3ub(255, 255, 255);
    if ( m_axisShow) drawRepere(1,1);
    if ( m_infoShow) drawInfo();

    QGLWidget::paintGL();
}

void KGLView::nextFrame()
{
    if ( engine() != NULL)
        engine()->mainLoop(fps());
    updateGL();
    m_countFrame++;
}
//===============DRAW FONCTION ============================
void KGLView::drawRepere(float scalex, float scaley) // a modifier
{
    glPushMatrix();

    glScalef(scalex, scaley,0);
    renderText(1,0,0,"X");
    renderText(-1,1,0,"Y");
    glBegin(GL_LINES);
    glColor3ub(255, 0, 0);
    glVertex2d(0, 0);
    glColor3ub(255, 0, 0);
    glVertex2d(1, 0);
    glColor3ub(0, 255, 0);
    glVertex2d(0, 0);
    glColor3ub(0, 255, 0);
    glVertex2d(0, 1);
    glEnd();
    glPopMatrix();
}
void  KGLView::drawInfo()
{
    glColor3ub(255, 255, 255);
    renderText(50, 55, "fps : " + QString::number(m_fps));
    renderText(50, 70, "fff : " + QString::number(100 / m_fps));
    renderText(50, 85, (m_isShaderSupported) ? "shader enable" : "shader unvaible" );
}
void KGLView::drawGLItems()
{
    IndexGroupMap::const_iterator i = engine()->items().constBegin();
    while (i != engine()->items().constEnd())
    {
        KGLItem * it;
        foreach ( it, i.value())
        {
            it->draw();
        }
        ++i;
    }
}
