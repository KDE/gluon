#ifndef KGLVIEW_H
#define KGLVIEW_H

#include <GL/glew.h>
#include <QGLWidget>
#include <QTimer>

#include "kglengine.h"
class KGLView : public QGLWidget
{
    Q_OBJECT
public:
    explicit KGLView( QSize size, float frameRate ,QWidget* parent = 0);
    explicit KGLView(KGLEngine * engine,QWidget * parent = 0);
    explicit KGLView(QWidget * parent=0);
    void setEngine(KGLEngine * engine){m_engine = engine;}
    KGLEngine * engine(){return m_engine;}

    void start() { m_timer->start(m_frameRate);m_fpsTimer->start(1000); }
    void stop(){ m_timer->stop();  m_fpsTimer->stop();}
    inline void setFrameRate(int f)
    {
        m_frameRate=f;
        stop();
        start();
    }
    inline void setOrthoView(QRectF &rect) {
        m_orthoView = rect;
        resizeGL(width(), height());
    }
    inline void setOrthoView(const float& left,const float& right,const float& bottom,const float& top)
    {
        m_orthoView.setLeft(left);
        m_orthoView.setRight(right);
        m_orthoView.setBottom(bottom);
        m_orthoView.setTop(top);
        resizeGL(width(),height());
    }
    //=== flags ====
    inline void setAxisShow(bool b){m_axisShow=b;}
    inline bool isAxisShow() {return m_axisShow; }
    inline void setInfoShow(bool b){m_infoShow = b;}
    inline bool isInfoShow(){return m_axisShow;}
    bool isExtensionSupported(QString name){return glewIsSupported(name.toUtf8());}
    bool isShaderSupported(){return m_isShaderSupported;}
    float fps(){return m_fps;}

    //===DRAW fonction
    void drawRepere(float scalex, float scaley);
    void drawInfo();
    void drawGLItems();

public slots:
    virtual void nextFrame();
    inline void calculFps()
    {
        m_fps = m_countFrame;
        m_countFrame = 0;
    }


protected:

    bool initGlew();
    void init();
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    KGLEngine * m_engine;
    QRectF m_orthoView;
    float m_countFrame;
    float m_fps;
    float m_frameRate;
    float m_ratio;
    float m_sleep;
    QTimer* m_timer;
    QTimer* m_fpsTimer;

    bool m_axisShow;
    bool m_infoShow;
    bool m_isShaderSupported;


};

#endif // KGLVIEW_H
