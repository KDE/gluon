#ifndef CONEMESH_H
#define CONEMESH_H

#include "../gluon_graphics_export.h"
#include "../mesh.h"

namespace GluonGraphics
{
    class GLUON_GRAPHICS_EXPORT ConeMesh: public Mesh
    {
    public:
        ConeMesh(QObject * parent=0);
        ConeMesh(float radius, float height, unsigned int nbPoints, QObject * parent=0 );
        void setCone(float radius, float height, unsigned int nbPoints);

    private:
        float m_radius;
        float m_height;
        float m_nbPoints;

    };
}

#endif // CONEMESH_H
