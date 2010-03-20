#include "conemesh.h"
#include <cmath>
namespace GluonGraphics
{
    ConeMesh::ConeMesh(QObject * parent)
            : Mesh(parent)
    {

        setCone(2, 5, 10);

    }

    ConeMesh::ConeMesh(float radius, float height, unsigned int nbPoints, QObject *parent)
            : Mesh(parent)
    {
        setCone(radius, height, nbPoints);
    }

    void ConeMesh::setCone(float radius, float height, unsigned int nbPoints)
    {
        m_radius = radius;
        m_height = height;
        m_nbPoints = nbPoints;
        clear();

        QVector3D apex(0, 0, height);
        setGLMode(GL_TRIANGLE_STRIP);
        if (nbPoints < 3)
        {
            return;
        }

        float step = M_PI * 2 / (float)nbPoints;

        for (float i = 0; i < M_PI*2; i += step)
        {
            float x = cos(i) ;
            float y = sin(i) ;
            addVertex(Vertex(x*radius, y*radius, Qt::white, QVector2D(x, y)));
            addVertex(Vertex(apex, Qt::white, QVector2D(0, 0)));

        }
        addVertex(Vertex(QVector2D(1*radius, 0), Qt::white, QVector2D(0, 0)));



    }
}
