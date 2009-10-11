#include "kglpainter.h"
#include <math.h>
#include <KDebug>
class KGLPainterPrivate
{
public :
        int mode;
QColor color;
float lineWidth;
float pointSize;
KGLPointList pointList;


};
KGLPainter::KGLPainter(QObject * parent)
    :QObject(parent)
{
    d = new KGLPainterPrivate;
    d->mode = GL_POLYGON;
    d->color = Qt::white;
}
KGLPainter::~KGLPainter(){

}


//============Parameter Function

void KGLPainter::setMode(int mode){
    d->mode = mode;
}

void KGLPainter::setColor(const QColor &col){
    d->color = col;
}
void KGLPainter::setLineWidth(float width){
    d->lineWidth = width;
    glLineWidth(d->lineWidth);
}
void KGLPainter::setPointSize(float size){
    d->pointSize = size;
    glPointSize(d->pointSize);
}
void KGLPainter::createRect(const QRectF &rect)
{
    d->pointList.clear();
    d->pointList.append(KGLPoint(rect.x(), rect.y(),d->color,QPointF(0 , 0)));
    d->pointList.append(KGLPoint(rect.x() + rect.width(), rect.y(),d->color, QPointF(1 , 0)));
    d->pointList.append(KGLPoint(rect.x() + rect.width(), rect.y() + rect.height(),d->color, QPointF(1 , 1)));
    d->pointList.append(KGLPoint(rect.x(), rect.y() + rect.height(),d->color, QPointF(0 , 1)));

}
void KGLPainter::createRect(float x, float y, float w, float h){
    createRect(QRectF(x,y,w,h));}

void KGLPainter::createLine(const QLineF &line )
{
    setMode(GL_LINES);
    d->pointList.clear();
    d->pointList.append(KGLPoint(line.x1(), line.y1(),Qt::white));
    d->pointList.append(KGLPoint(line.x2(), line.y2(),Qt::white));


}
void KGLPainter::createLine(float x1, float y1, float x2, float y2){
    createLine(QLineF(x1,y1,x2,y2));
}

void KGLPainter::createPoint(const QPointF &point )
{

    glBegin(GL_POINT);
    glVertex2d(point.x(),point.y());
    glEnd();

}

void KGLPainter::createPoint(float x, float y){
    createPoint(QPointF(x,y));
}


void KGLPainter::createCircle(const QPointF &center, float radius, float step)
{
    if ( step <3)
    {
        kDebug()<<"cannot create it. Use createline...";
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

}
void KGLPainter::createCircle(float cx, float cy, float radius, float step){
    createCircle(QPointF(cx,cy),radius,step);
}
void KGLPainter::createPolygon(const QPolygonF & polygon)
{
d->pointList.clear();
foreach(QPointF p, polygon)
{

}

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

    //    /* create vertex */
    glDrawArrays(d->mode, 0, d->pointList.size());

    /* disable client state */
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void KGLPainter::begin(int mode){
    setMode(mode);
    glLineWidth(d->lineWidth);
    glPointSize(d->pointSize);
}
void KGLPainter::end(){
    glLineWidth(1);
    glPointSize(1);
}

