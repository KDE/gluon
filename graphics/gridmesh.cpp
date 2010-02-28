#include "gridmesh.h"
namespace GluonGraphics
{
    GridMesh::GridMesh(QObject* parent)
        :Mesh(parent)
    {
        m_tile=1;
        m_size=QSizeF();
    }
    GridMesh::GridMesh(QSizeF size, float tile, QObject* parent)
        :Mesh(parent)
    {
        setGrid(size,tile);
    }


    void GridMesh::setGrid(QSizeF size, float tile)
    {
        m_tile = tile;
        m_size = size;
        clear();
        setGLMode(GL_TRIANGLE_STRIP);
        for ( float j=0; j<=m_size.height();j+=m_tile)
        {
            for ( float i=0; i<=m_size.width(); i+=m_tile)
            {
                addVertex(Vertex(i,j,Qt::white,QVector2D(i/m_size.width(),j/m_size.height())));
                addVertex(Vertex(i,j+m_tile,Qt::white,QVector2D(i/m_size.width(),(j+m_tile)/m_size.height())));
            }
        }

    }

}
