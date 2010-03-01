#ifndef GRIDMESH_H
#define GRIDMESH_H

#include "gluon_graphics_export.h"
#include "mesh.h"

namespace GluonGraphics
{
    class GLUON_GRAPHICS_EXPORT GridMesh: public Mesh
    {
    public:
        GridMesh(QObject * parent=0);
        GridMesh(QSizeF size, float tile, QObject *parent=0);
        void setGrid(QSizeF size, float tile=1);
    private:
    private:
         QSizeF m_size;
         float m_tile;

    };
}


#endif // GRIDMESH_H
