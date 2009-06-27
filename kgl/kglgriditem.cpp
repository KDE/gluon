#include "kglgriditem.h"
#include <KDebug>
KGLGridItem::KGLGridItem(QSizeF size, float tile, KGLEngine * parent)
    :KGLItem(parent)
{
    setMode(GL_TRIANGLE_STRIP);
    m_size = size;
    m_tile = tile;
    createGrid();
}
KGLGridItem::KGLGridItem(float width, float height, float tile, KGLEngine * parent)
    :KGLItem(parent)
{
    setMode(GL_TRIANGLE_STRIP);
    m_size = QSizeF(width,height);
    m_tile = tile;
    createGrid();
}
void KGLGridItem::createGrid()
{
    clear();

for ( float j=0; j<=m_size.height();j+=m_tile)
    {

         for ( float i=0; i<=m_size.width(); i+=m_tile)
            {
                addVertex(new KGLPoint(i,j,Qt::white,QPointF(i/m_size.width(),j/m_size.height())));
                addVertex(new KGLPoint(i,j+m_tile,Qt::white,QPointF(i/m_size.width(),(j+m_tile)/m_size.height())));
            }
     }







}


   KGLPoint * KGLGridItem::pointAt(QPoint p)
   {


      int id =  m_size.width()*p.y() + p.x();
      return pointList().at(id);

   }
