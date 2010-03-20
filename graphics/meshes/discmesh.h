#ifndef DISCMESH_H
#define DISCMESH_H

#include "../gluon_graphics_export.h"
#include "../mesh.h"

namespace GluonGraphics
{
    class GLUON_GRAPHICS_EXPORT DiscMesh: public Mesh
    {
        public:
            DiscMesh(QObject * parent = 0);
            DiscMesh(float radius, unsigned int nbPoints, QObject * parent = 0);
            void setDisc(float radius, unsigned int nbPoints);
        private:
            unsigned int m_nbPoints;
            float m_radius;

    };
}

#endif // DISCMESH_H
