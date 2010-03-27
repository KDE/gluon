#include "glpainter.h"
#include <math.h>
#include <QtCore/QDebug>

#ifndef M_PI
#define M_PI           3.14159265358979323846
#endif
namespace GluonGraphics
{
    class GLPainterPrivate
    {
        public :
            QColor color;
            float lineWidth;
            float pointSize;
            GLenum polygonMode;
            VertexList pointList;

    };

    GLPainter::GLPainter(QObject * parent)
            : QObject(parent)
    {
        d = new GLPainterPrivate;
        d->color = Qt::white;
        d->lineWidth = 1;
        d->pointSize = 1;
    }

    GLPainter::~GLPainter()
    {
        delete d;
    }

//============Parameter Function
    void GLPainter::setColor(const QColor &col)
    {
        d->color = col;
    }
    void GLPainter::setLineWidth(float width)
    {
        d->lineWidth = width;

    }
    void GLPainter::setPointSize(float size)
    {
        d->pointSize = size;
        glPointSize(d->pointSize);
    }
    void GLPainter::setPolygonMode(GLenum mode)
    {
        d->polygonMode = mode;
        glPolygonMode(GL_FRONT_AND_BACK, mode);
    }
    void GLPainter::createRect(const QRectF &rect)
    {
        d->pointList.clear();
        d->pointList.append(Vertex(rect.x(), rect.y(), d->color, QVector2D(0 , 0)));
        d->pointList.append(Vertex(rect.x() + rect.width(), rect.y(), d->color, QVector2D(1 , 0)));
        d->pointList.append(Vertex(rect.x() + rect.width(), rect.y() + rect.height(), d->color, QVector2D(1 , 1)));
        d->pointList.append(Vertex(rect.x(), rect.y() + rect.height(), d->color, QVector2D(0 , 1)));

    }
    void GLPainter::createRect(float x, float y, float w, float h)
    {
        createRect(QRectF(x, y, w, h));
    }

    void GLPainter::createLine(const QLineF &line)
    {

        d->pointList.clear();
        d->pointList.append(Vertex(line.x1(), line.y1(), Qt::white));
        d->pointList.append(Vertex(line.x2(), line.y2(), Qt::white));


    }
    void GLPainter::createLine(float x1, float y1, float x2, float y2)
    {
        createLine(QLineF(x1, y1, x2, y2));
    }

    void GLPainter::createCircle(const QVector2D &center, float radius, float step)
    {
        if (step < 3)
        {
            qDebug() << "cannot create it. Use createline...";
            return;
        }
        d->pointList.clear();
        d->pointList.append(
            Vertex(center.x(), center.y(), d->color, QVector2D(center.x() , center.y())));

        float radStep = 2 * M_PI / step;

        for (float i = 0; i <= 2*M_PI + 1; i += radStep)
        {
            float cosr = (float)cos(i);
            float sinr = (float)sin(i);

            float x = cosr * radius + center.x();
            float y = sinr * radius + center.y();
            d->pointList.append(Vertex(x, y, d->color, QVector2D(cosr , sinr)));
        }

    }
    void GLPainter::createCircle(float cx, float cy, float radius, float step)
    {
        createCircle(QVector2D(cx, cy), radius, step);
    }
    void GLPainter::createPolygon(const QPolygonF & polygon)
    {
        d->pointList.clear();
        foreach(const QPointF &p, polygon)
        {
            d->pointList.append(Vertex(p.x(), p.y(), d->color, QVector2D(p.x() , p.y())));
        }
    }
    void GLPainter::draw(GLenum mode)
    {
        glLineWidth(d->lineWidth);
        glPointSize(d->pointSize);
        glPolygonMode(GL_FRONT_AND_BACK, d->polygonMode);


        /*enable client state */
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);

        /* send data */
        glVertexPointer(3, GL_FLOAT, sizeof(Vertex), d->pointList.vertexStart());
        glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), d->pointList.texCoordStart());
        glColorPointer(4, GL_FLOAT, sizeof(Vertex), d->pointList.colorStart());

        //    /* create vertex */
        glDrawArrays(mode, 0, d->pointList.size());

        /* disable client state */
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);

        glLineWidth(1);
        glPointSize(1);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    void GLPainter::drawRect(const QRectF &rect)
    {
        createRect(rect);
        draw(GL_POLYGON);
    }
    void GLPainter::drawRect(float x, float y, float w, float h)
    {
        createRect(x, y, w, h);
        draw(GL_POLYGON);
    }
    void GLPainter::drawLine(const QLineF &line)
    {
        createLine(line);
        draw(GL_LINE);

    }
    void GLPainter::drawLine(float x1, float y1, float x2, float y2)
    {
        createLine(x1, y1, x2, y2);
        draw(GL_LINE);
    }
    void GLPainter::drawPoint(const QVector2D &point)
    {
        glBegin(GL_POINT);
        glVertex2d(point.x(), point.y());
        glEnd();
    }
    void GLPainter::drawPoint(float x, float y)
    {
        glBegin(GL_POINT);
        glVertex2d(x, y);
        glEnd();

    }
    void GLPainter::drawCircle(const QVector2D &center, float radius, float step)
    {
        createCircle(center, radius, step);
        draw(GL_TRIANGLE_FAN);
    }
    void GLPainter::drawCircle(float cx, float cy, float radius, float step)
    {
        createCircle(cx, cy, radius, step);
        draw(GL_TRIANGLE_FAN);
    }
    void GLPainter::drawPolygon(const QPolygonF & polygon)
    {
        createPolygon(polygon);
        draw(GL_POLYGON);

    }
}
#include "glpainter.moc"

