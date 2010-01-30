#ifndef GLUON_GRAPHICS_GLPAINTER_H
#define GLUON_GRAPHICS_GLPAINTER_H

#include <QtCore/QObject>
#include <QtGui/QPainter>

#include "gluon_graphics_export.h"
#include "texture.h"
#include "vertex.h"


namespace GluonGraphics
{
class GLPainterPrivate;

class GLUON_GRAPHICS_EXPORT GLPainter : public QObject
{
public:
    GLPainter(QObject * parent=0);
    ~GLPainter();
    void createRect(const QRectF &rect);
    void createRect(float x, float y, float w, float h);
    void createLine(const QLineF &line);
    void createLine(float x1, float y1, float x2, float y2);
    void createCircle(const QPointF &center, float radius, float step=10);
    void createCircle(float cx,float cy, float radius, float step = 10);
    void createPolygon(const QPolygonF & polygon);


    void drawRect(const QRectF &rect);
    void drawRect(float x, float y, float w, float h);
    void drawLine(const QLineF &line);
    void drawLine(float x1, float y1, float x2, float y2);
    void drawPoint(const QPointF &point);
    void drawPoint(float x, float y);
    void drawCircle(const QPointF &center, float radius, float step=10);
    void drawCircle(float cx,float cy, float radius, float step = 10);
    void drawPolygon(const QPolygonF & polygon);

    void setColor(const QColor &col);
    void setLineWidth(float width);
    void setPointSize(float size);
    void setPolygonMode(GLenum mode);

    void draw(GLenum mode=GL_POLYGON);

private:
    Q_DISABLE_COPY(GLPainter)
    GLPainterPrivate * d;
};
}//namespace
#endif // GLUON_GRAPHICS_GLPAINTER_H
