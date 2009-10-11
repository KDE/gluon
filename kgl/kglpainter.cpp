#include "kglpainter.h"
#include <math.h>
#include <KDebug>
class KGLPainterPrivate
{
public :
        int mode;
QColor color;
KGLPointList pointList;


};
KGLPainter::KGLPainter(QObject * parent)
    :QObject(parent)
{
    d = new KGLPainterPrivate;
    d->mode = GL_POLYGON;
    d->color = Qt::white;
}

//============Parameter Function

void KGLPainter::setMode(int mode){
    d->mode = mode;
}

void KGLPainter::drawRect(const QRectF &rect)
{
    d->pointList.clear();
    d->pointList.append(KGLPoint(rect.x(), rect.y(),d->color,QPointF(0 , 0)));
    d->pointList.append(KGLPoint(rect.x() + rect.width(), rect.y(),d->color, QPointF(1 , 0)));
    d->pointList.append(KGLPoint(rect.x() + rect.width(), rect.y() + rect.height(),d->color, QPointF(1 , 1)));
    d->pointList.append(KGLPoint(rect.x(), rect.y() + rect.height(),d->color, QPointF(0 , 1)));
    draw();
}
void KGLPainter::drawRect(float x, float y, float w, float h){
    drawRect(QRectF(x,y,w,h));}

void KGLPainter::drawLine(const QLineF &line ,float lineWidh)
{
    setMode(GL_LINES);
    d->pointList.clear();
    d->pointList.append(KGLPoint(line.x1(), line.y1(),Qt::white));
    d->pointList.append(KGLPoint(line.x2(), line.y2(),Qt::white));
    glLineWidth(lineWidh);
    draw();
    setMode(GL_POLYGON);
    glLineWidth(1);

}
void KGLPainter::drawLine(float x1, float y1, float x2, float y2, float lineWidth){
    drawLine(QLineF(x1,y1,x2,y2),lineWidth);
}

void KGLPainter::drawPoint(const QPointF &point ,float pointSize)
{
    glPointSize(pointSize);
    glBegin(GL_POINT);
    glVertex2d(point.x(),point.y());
    glEnd();
    glPointSize(1);
}

void KGLPainter::drawPoint(float x, float y){
    drawPoint(QPointF(x,y));
}


void KGLPainter::drawCircle(const QPointF &center, float radius, float step)
{
    if ( step <3)
    {
        kDebug()<<"cannot draw it. Use drawline...";
        return;
    }
    d->pointList.clear();

    setMode(GL_TRIANGLE_FAN);
    d->pointList.append(
            KGLPoint(center.x(),center.y(),d->color,QPointF(center.x() ,center.y())));

    float radStep = 2*M_PI/step;

    for(float i=0; i<=2*M_PI+1; i+=radStep)
    {
        float cosr = (float)cos(i);
        float sinr = (float)sin(i);

        float x = cosr*radius + center.x();
        float y = sinr*radius + center.y();
        d->pointList.append(KGLPoint(x,y,d->color,QPointF(cosr ,sinr)));

    }
    draw();
    setMode(GL_POLYGON);
}
void KGLPainter::drawCircle(float cx, float cy, float radius, float step){
    drawCircle(QPointF(cx,cy),radius,step);
}
void KGLPainter::draw()
{

    /*enable client state */
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    /* send data */
    glVertexPointer(2, GL_FLOAT,sizeof(KGLPoint),d->pointList.vertexStart());
    glTexCoordPointer(2,GL_FLOAT,sizeof(KGLPoint),d->pointList.texCoordStart());
    glColorPointer(4, GL_FLOAT,sizeof(KGLPoint),d->pointList.colorStart());

    //    /* draw vertex */
    glDrawArrays(d->mode, 0, d->pointList.size());

    /* disable client state */
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}



