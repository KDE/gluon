#ifndef KGLVIEW_H
#define KGLVIEW_H

#include <GL/glew.h>
#include <QDebug>
#include <QGLWidget>
#include <QTimer>
#ifdef Q_WS_X11
	#include <QX11Info>
#endif

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

	void goFullscreen(int width = 0, int height = 0)
	{
		#ifdef Q_WS_X11
			QX11Info *info = new QX11Info();
			qDebug() << "X11" << info->screen();
		#endif
		#ifdef Q_WS_WIN
			qDebug() << "Win";
		#endif
	}

	void leaveFullscreen()
	{
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

   inline QPointF mapToGL(const QPointF &p) {

       float ax = m_orthoView.width() / width();
       float bx = m_orthoView.left();

       float ay = m_orthoView.height() / height();
       float by = -m_orthoView.bottom();

       QPointF pos ( p.x()*ax + bx, p.y()*ay + by+1); //+1 for cursor inversion
       return pos;

//        return QPointF((m_orthoView.width() / 2 * p.x() * 2 / QGLWidget::width()) - m_orthoView.width() / 2, -(m_orthoView.height() / 2 - p.y() * m_orthoView.height() / QGLWidget::height()));
    }
    inline QPointF mapFromGL(const QPointF &p) {
      return QPointF((p.x() + m_orthoView.width() / 2) * QGLWidget::width() / (m_orthoView.width()), -((m_orthoView.height() / 2 - p.y()) * (QGLWidget::height() / m_orthoView.height())));
    }


    //=== flags ====
    inline void setMode(GLenum mode){m_mode=mode; initializeGL();}
    inline void setAxisShow(bool b){m_axisShow=b;}
    inline bool isAxisShow() {return m_axisShow; }
    inline void setInfoShow(bool b){m_infoShow = b;}
    inline bool isInfoShow(){return m_axisShow;}
//    inline void setShadeModel(GLenum mode);
    bool isExtensionSupported(QString name){return glewIsSupported(name.toUtf8());}
    bool isShaderSupported(){return m_isShaderSupported;}
    float fps(){return m_fps;}

    //===DRAW function
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
   GLenum m_mode;

};

#endif // KGLVIEW_H
