#include "discmesh.h"
#include <cmath>
namespace GluonGraphics
{
    DiscMesh::DiscMesh(QObject * parent)
        :Mesh(parent)
    {
        m_radius=1;
        m_nbPoints=10;
        setDisc(m_radius,m_nbPoints);
    }
    DiscMesh::DiscMesh(float radius, unsigned int nbPoints, QObject *parent)
        :Mesh(parent)
    {

        setDisc(radius, nbPoints);
    }

    void DiscMesh::setDisc(float radius, unsigned int nbPoints)
    {

        clear();
        setGLMode(GL_POLYGON);
        if (nbPoints < 3) {
            return;
        }

        float step = M_PI * 2 / (float)nbPoints;

        for (float i = 0; i < M_PI*2; i += step) {
            float x = cos(i) ;
            float y = sin(i)  ;
            addVertex( Vertex(x*radius, y*radius, Qt::white, QVector2D(x, y)));
        }
    }
}
