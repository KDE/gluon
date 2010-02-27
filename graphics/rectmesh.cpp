#include "rectmesh.h"

namespace GluonGraphics
{
 RectMesh::RectMesh(QObject * parent)
        :Mesh(parent)
    {
        m_rect = QRectF;
    }
    RectMesh::RectMesh(const QRectF& rect, QObject * parent)
        :Mesh(parent)
    {
        setRect(rect);
    }
    void RectMesh::setRect(const QRectF &polygon)
    {

    }
}
