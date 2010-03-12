#ifndef CYLINDREMESH_H
#define CYLINDREMESH_H

#include "../gluon_graphics_export.h"
#include "../mesh.h"
#include <cmath>
namespace GluonGraphics
{
    class GLUON_GRAPHICS_EXPORT CylindreMesh: public Mesh
    {
    public:
        CylindreMesh(QObject * parent=0);
        void setCylindre(float radius, float height, unsigned int nbPoints);
    private:
        float m_radius;
        float m_height;
        int m_nbPoints;

    };
}


#endif // CYLINDREMESH_H
