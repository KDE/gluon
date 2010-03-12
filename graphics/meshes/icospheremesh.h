#ifndef ICOSPHEREMESH_H
#define ICOSPHEREMESH_H

#include "../gluon_graphics_export.h"
#include "../mesh.h"

namespace GluonGraphics
{
    class GLUON_GRAPHICS_EXPORT IcoSphereMesh: public Mesh
    {
    public:
        IcoSphereMesh(QObject * parent=0);
        void setIcoSphere(float radius, int division);
    };
}

#endif // ICOSPHEREMESH_H
