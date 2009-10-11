#ifndef KGLDEBUGPHYSICSVIEW_H
#define KGLDEBUGPHYSICSVIEW_H
#include "kglview.h"
#include "kglphysicsengine.h"
class KGLDebugPhysicsView : public KGLView, public b2DebugDraw
{
public:
    KGLDebugPhysicsView(QWidget * parent=0);

    void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
    void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
    void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);
    void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);
    void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
    void DrawXForm(const b2XForm& xf);
    void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color);
    void DrawString(int x, int y, const char* string, ...);
    void DrawAABB(b2AABB* aabb, const b2Color& color);


    protected:
    void paintGL();
void begin();
void end();

private:
    int m_glList;
};

#endif // KGLDEBUGPHYSICSVIEW_H
