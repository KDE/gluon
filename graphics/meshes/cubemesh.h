#ifndef CUBEMESH_H
#define CUBEMESH_H

#include "../gluon_graphics_export.h"
#include "../mesh.h"

namespace GluonGraphics
{
    class GLUON_GRAPHICS_EXPORT CubeMesh: public Mesh
    {
        public:
            CubeMesh(QObject * parent = 0);
            CubeMesh(float dimX, float dimY, float dimZ, QObject * parent = 0);
            explicit CubeMesh(float dim, QObject * parent = 0);
            void setCube(float dimX, float dimY, float dimZ);

        private:
            float m_dimX, m_dimY, m_dimZ;

    };
}

#endif // CUBEMESH_H
