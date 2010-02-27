#ifndef RECTMESH_H
#define RECTMESH_H

#include "gluon_graphics_export.h"
#include "mesh.h"
#include <QRectF>

namespace GluonGraphics
{
    class GLUON_GRAPHICS_EXPORT RectMesh: public Mesh
    {
    public:
        RectMesh(QObject * parent=0);
        RectMesh(const QRectF& Rect, QObject * parent=0);
        void setRect(const QRectF& rect);
        const QRectF& rect()
        {
            return m_rect;
        }

    private:
        QRectF m_rect;


    };
}

#endif // RECTMESH_H
