#include "polygonmesh.h"
namespace GluonGraphics
{
 PolygonMesh::PolygonMesh(QObject * parent)
        :Mesh(parent)
    {
        m_polygon = QPolygonF();
    }
    PolygonMesh::PolygonMesh(const QPolygonF& polygon, QObject * parent)
        :Mesh(parent)
    {
        setPolygon(polygon);
    }
    PolygonMesh::PolygonMesh(const QRectF& rect, QObject * parent)
        :Mesh(parent)
    {
        setPolygon(QPolygonF(rect));
    }
    void PolygonMesh::setPolygon(const QPolygonF &polygon)
    {
        m_polygon = polygon;
        foreach(QPointF p, m_polygon)
        {
           QVector2D textureCoord(p.x(), p.y());
            addVertex(Vertex(p.x(),p.y(),Qt::white,textureCoord ));
        }
    }
}
