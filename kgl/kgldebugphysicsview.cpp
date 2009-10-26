#include "kgldebugphysicsview.h"
#include <QtCore/QDebug>
KGLDebugPhysicsView::KGLDebugPhysicsView(QWidget * parent)
    :KGLView(parent),b2DebugDraw()
{

m_glList=0;


}
void KGLDebugPhysicsView::paintGL()
{

if ( m_glList!=0)
glCallList(m_glList);

    KGLView::paintGL();
}

void KGLDebugPhysicsView::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{

    qDebug()<<"draw poly";
    m_glList = glGenLists(1);
    glNewList(m_glList, GL_COMPILE);


    glColor3f(color.r, color.g, color.b);
    glBegin(GL_LINE_LOOP);
    for (int32 i = 0; i < vertexCount; ++i) {
        glVertex2f(vertices[i].x, vertices[i].y);
    }
    glEnd();


    glEndList();





}

void KGLDebugPhysicsView::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    qDebug()<<"draw solid poly";

}
void KGLDebugPhysicsView::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
    qDebug()<<"draw Circle";
}
void KGLDebugPhysicsView::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
    qDebug()<<"draw Solid circle";
}
void KGLDebugPhysicsView::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
    qDebug()<<"draw Segment";
}
void KGLDebugPhysicsView::DrawXForm(const b2XForm& xf)
{
    qDebug()<<"draw Xform";
}
void KGLDebugPhysicsView::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
{
    qDebug()<<"draw point";
}
void KGLDebugPhysicsView::DrawString(int x, int y, const char* string, ...)
{
    qDebug()<<"draw stringy";
}
void KGLDebugPhysicsView::DrawAABB(b2AABB* aabb, const b2Color& color)
{
    qDebug()<<"draw AAB";
}
void KGLDebugPhysicsView::begin()
{
    m_glList = glGenLists(1);
    glNewList(m_glList, GL_COMPILE);

    glBegin(GL_QUADS);
}
void KGLDebugPhysicsView::end()
{

    glEnd();
}
