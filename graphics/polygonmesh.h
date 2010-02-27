#ifndef POLYGONMESH_H
#define POLYGONMESH_H

#include "gluon_graphics_export.h"
#include "mesh.h"
#include <QPolygonF>
namespace GluonGraphics
{
    class GLUON_GRAPHICS_EXPORT PolygonMesh: public Mesh
    {
    public:
        PolygonMesh(QObject * parent=0);
        PolygonMesh(const QPolygonF& polygon, QObject * parent=0);
        PolygonMesh(const QRectF& rect, QObject* parent=0);
        void setPolygon(const QPolygonF& polygon);

        const QPolygonF& polygon()
        {
            return m_polygon;
        }

    private:
        QPolygonF m_polygon;


    };
}

#endif // POLYGONMESH_H
