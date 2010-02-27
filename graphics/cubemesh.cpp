#include "cubemesh.h"

namespace GluonGraphics
{
    CubeMesh::CubeMesh(QObject * parent)
        :Mesh(parent)
    {
        m_dimX = m_dimY = m_dimZ = 1;
    }
    CubeMesh::CubeMesh(float dimX, float dimY, float dimZ, QObject * parent)
        :Mesh(parent)
    {

    }

    CubeMesh::CubeMesh(float dim, QObject * parent)
        :Mesh(parent)
    {

    }

   void CubeMesh::setCube(float dimX, float dimY, float dimZ)
    {
        m_dimX=dimX;
        m_dimY=dimY;
        m_dimZ=dimZ;





    }
}
