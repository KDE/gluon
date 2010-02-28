#include "cylindremesh.h"
namespace GluonGraphics
{
    CylindreMesh::CylindreMesh(QObject * parent)
        :Mesh(parent)
    {
   setCylindre(3,5,10);
    }

       void CylindreMesh::setCylindre(float radius, float height, unsigned int nbPoints)
       {

clear();
m_radius=radius;
m_height= height;
m_nbPoints=nbPoints;
setGLMode(GL_POINTS);

           float step = M_PI * 2 / (float)nbPoints;

           for (float i = 0; i < M_PI*2; i += step)
           {
               float x = cos(i) ;
               float y = sin(i) ;
               addVertex(Vertex(x*radius, y*radius,0, Qt::white, QVector2D(x, y)));
               addVertex(Vertex(x*radius, y*radius,height, Qt::white, QVector2D(x, y)));

           }

           addVertex(Vertex(1*radius, 0*radius,0, Qt::white, QVector2D(1, 0)));
           addVertex(Vertex(1*radius, 0*radius,height, Qt::white, QVector2D(1, 0)));

       }
}
