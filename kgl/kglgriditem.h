#ifndef KGLGRIDITEM_H
#define KGLGRIDITEM_H
#include "kglitem.h"
#include <QSizeF>
#include <QList>
class KGLGridItem : public KGLItem
{
public:
    KGLGridItem(QSizeF size, float tile=1, KGLEngine * engine=0);
    KGLGridItem(float width, float height, float tile=1, KGLEngine * engine=0);
    void init();
   void createGrid();
   KGLPoint * pointAt(QPoint p);
   KGLPoint * pointAt(int x, int y){return pointAt(QPoint(x,y));}

   inline void setSize(const QSizeF &s){m_size = s;}
   inline void setTile(const float &t){m_tile = t;}
   private:
   QSizeF m_size;
   float m_tile;

};

#endif // KGLGRIDITEM_H
