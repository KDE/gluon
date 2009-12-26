#include "kglpainter.h"
#include <math.h>
#include <QtCore/QDebug>
class KGLPainterPrivate
{
public :
        QColor color;
float lineWidth;
float pointSize;
GLenum polygonMode;
KGLPointList pointList;



};
KGLPainter::KGLPainter(QObject * parent)
    :QObject(parent)
{
    d = new KGLPainterPrivate;
    d->color = Qt::white;
    d->lineWidth = 1;
    d->pointSize = 1;
}

KGLPainter::~KGLPainter()
{
    delete d;
}

//============Parameter Function
void KGLPainter::setColor(const QColor &col){
    d->color = col;
}
void KGLPainter::setLineWidth(float width){
    d->lineWidth = width;

}
void KGLPainter::setPointSize(float size){
    d->pointSize=size;
    glPointSize(d->pointSize);
}
void KGLPainter::setPolygonMode(GLenum mode){
    d->polygonMode = mode;
    glPolygonMode(GL_FRONT_AND_BACK,mode);
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

    d->pointList.clear();
    d->pointList.append(KGLPoint(line.x1(), line.y1(),Qt::white));
    d->pointList.append(KGLPoint(line.x2(), line.y2(),Qt::white));


}
void KGLPainter::createLine(float x1, float y1, float x2, float y2){
    createLine(QLineF(x1,y1,x2,y2));
}

void KGLPainter::createCircle(const QPointF &center, float radius, float step)
{
    if ( step <3)
    {
        qDebug()<<"cannot create it. Use createline...";
        return;
    }
    d->pointList.clear();
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
        d->pointList.append(KGLPoint(p.x(),p.y(),d->color,QPointF(p.x() ,p.y())));
}
void KGLPainter::draw(GLenum mode)
{
    glLineWidth(d->lineWidth);
    glPointSize(d->pointSize);
    glPolygonMode(GL_FRONT_AND_BACK,d->polygonMode);


    /*enable client state */
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    /* send data */
    glVertexPointer(2, GL_FLOAT,sizeof(KGLPoint),d->pointList.vertexStart());
    glTexCoordPointer(2,GL_FLOAT,sizeof(KGLPoint),d->pointList.texCoordStart());
    glColorPointer(4, GL_FLOAT,sizeof(KGLPoint),d->pointList.colorStart());

    //    /* create vertex */
    glDrawArrays(mode, 0, d->pointList.size());

    /* disable client state */
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    glLineWidth(1);
    glPointSize(1);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
}

void KGLPainter::drawRect(const QRectF &rect){
    createRect(rect);
    draw(GL_POLYGON);
}
void KGLPainter::drawRect(float x, float y, float w, float h){
    createRect(x,y,w,h);
    draw(GL_POLYGON);
}
void KGLPainter::drawLine(const QLineF &line){
    createLine(line);
    draw(GL_LINE);

}
void KGLPainter::drawLine(float x1, float y1, float x2, float y2){
    createLine(x1,y1,x2,y2);
    draw(GL_LINE);
}
void KGLPainter::drawPoint(const QPointF &point){
    glBegin(GL_POINT);
    glVertex2d(point.x(),point.y());
    glEnd();
}
void KGLPainter::drawPoint(float x, float y){
    glBegin(GL_POINT);
    glVertex2d(x,y);
    glEnd();

}
void KGLPainter::drawCircle(const QPointF &center, float radius, float step){
    createCircle(center,radius,step);
    draw(GL_TRIANGLE_FAN);
}
void KGLPainter::drawCircle(float cx,float cy, float radius, float step ){
    createCircle(cx,cy,radius,step);
    draw(GL_TRIANGLE_FAN);
}
void KGLPainter::drawPolygon(const QPolygonF & polygon){
    createPolygon(polygon);
    draw(GL_POLYGON);

}

#include "kglpainter.moc"

