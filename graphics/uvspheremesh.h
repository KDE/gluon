#ifndef UVSPHEREMESH_H
#define UVSPHEREMESH_H

#include "gluon_graphics_export.h"
#include "mesh.h"

namespace GluonGraphics
{
    class GLUON_GRAPHICS_EXPORT UvSphereMesh: public Mesh
    {
    public:
        UvSphereMesh(QObject * parent=0);
        void setUvSphere(float radius, int division);
    };
}
#endif // UVSPHEREMESH_H
