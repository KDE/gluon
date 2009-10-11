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
    void createRect(const QRectF &rect);
    void createRect(float x, float y, float w, float h);
    void createLine(const QLineF &line);
    void createLine(float x1, float y1, float x2, float y2);
    void createPoint(const QPointF &point);
    void createPoint(float x, float y);
    void createCircle(const QPointF &center, float radius, float step=10);
    void createCircle(float cx,float cy, float radius, float step = 10);
    void createPolygon(const QPolygonF & polygon);

    void begin(int mode);
    void end();
    void setColor(const QColor &col);
    void setLineWidth(float width);
    void setPointSize(float size);

    void draw();

private:
    KGLPainterPrivate * d;
};

#endif // KGLPAINTER_H
