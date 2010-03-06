#include "uvspheremesh.h"
#include <cmath>
namespace GluonGraphics
{
    UvSphereMesh::UvSphereMesh(QObject * parent)
        :Mesh(parent)
    {
        setUvSphere(5,4);
    }


    void UvSphereMesh::setUvSphere(float radius, int division)
    {

        clear();
        setGLMode(GL_POLYGON);
        float  t = (1.0 +sqrt(5.0)) / 2.0;

        addVertex(QVector3D(-1,  t,  0));
        addVertex(QVector3D( 1,  t,  0));
        addVertex(QVector3D(-1, -t,  0));
        addVertex(QVector3D( 1, -t,  0));


        addVertex(QVector3D( 0, -1,  t));
        addVertex(QVector3D( 0,  1,  t));
        addVertex(QVector3D( 0, -1, -t));
        addVertex(QVector3D( 0,  1, -t));

        addVertex(QVector3D( t,  0, -1));
        addVertex(QVector3D( t,  0,  1));
        addVertex(QVector3D(-t,  0, -1));
        addVertex(QVector3D(-t,  0,  1));

    }

}
