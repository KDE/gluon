#ifndef KGLPAINTER_H
#define KGLPAINTER_H

#include <QObject>
#include <QPainter>
#include <GL/glew.h>
#include "kgltexture.h"
#include "kglpoint.h"
class KGLPainterPrivate;
class KGLPainter;
class KGLPainter : public QObject
{
public:
    KGLPainter(QObject * parent=0);
    ~KGLPainter();
    
        void setMode(int mode);
    void drawRect(const QRectF &rect);
    void drawRect(float x, float y, float w, float h);
    void drawLine(const QLineF &line, float lineWidth=1);
    void drawLine(float x1, float y1, float x2, float y2, float lineWidth=1);
    void drawPoint(const QPointF &point, float pointSize=1);
    void drawPoint(float x, float y);
    void drawCircle(const QPointF &center, float radius, float step=10);
    void drawCircle(float cx,float cy, float radius, float step = 10);


protected:
    void draw();

private:
    Q_DISABLE_COPY(KGLPainter)
    KGLPainterPrivate * d;
};

#endif // KGLPAINTER_H
