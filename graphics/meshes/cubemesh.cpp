#include "cubemesh.h"

namespace GluonGraphics
{
    CubeMesh::CubeMesh(QObject * parent)
            : Mesh(parent)
    {
        setCube(1, 1, 1);
    }
    CubeMesh::CubeMesh(float dimX, float dimY, float dimZ, QObject * parent)
            : Mesh(parent)
    {
        setCube(dimX, dimY, dimZ);
    }

    CubeMesh::CubeMesh(float dim, QObject * parent)
            : Mesh(parent)
    {
        setCube(dim, dim, dim);
    }

    void CubeMesh::setCube(float dimX, float dimY, float dimZ)
    {
        m_dimX = dimX;
        m_dimY = dimY;
        m_dimZ = dimZ;

        clear();
        setGLMode(GL_QUADS);
        addVertex(Vertex(QVector3D(dimX, dimY, dimZ), Qt::red, QVector2D(1, 1)));
        addVertex(Vertex(QVector3D(dimX, dimY, -dimZ), Qt::red, QVector2D(1, 0)));
        addVertex(Vertex(QVector3D(-dimX, dimY, -dimZ), Qt::red, QVector2D(0, 0)));
        addVertex(Vertex(QVector3D(-dimX, dimY, dimZ), Qt::red, QVector2D(0, 1)));

        addVertex(Vertex(QVector3D(dimX, -dimY, dimZ), Qt::blue, QVector2D(0, 1)));
        addVertex(Vertex(QVector3D(dimX, -dimY, -dimZ), Qt::blue, QVector2D(0, 0)));
        addVertex(Vertex(QVector3D(dimX, dimY, -dimZ), Qt::blue, QVector2D(1, 0)));
        addVertex(Vertex(QVector3D(dimX, dimY, dimZ), Qt::blue, QVector2D(1, 1)));

        addVertex(Vertex(QVector3D(-dimX, -dimY, dimZ), Qt::green, QVector2D(0, 1)));
        addVertex(Vertex(QVector3D(-dimX, -dimY, -dimZ), Qt::green, QVector2D(0, 0)));
        addVertex(Vertex(QVector3D(dimX, -dimY, -dimZ), Qt::green, QVector2D(1, 0)));
        addVertex(Vertex(QVector3D(dimX, -dimY, dimZ), Qt::green, QVector2D(1, 1)));

        addVertex(Vertex(QVector3D(-dimX, dimY, dimZ), Qt::yellow, QVector2D(1, 1)));
        addVertex(Vertex(QVector3D(-dimX, dimY, -dimZ), Qt::yellow, QVector2D(1, 0)));
        addVertex(Vertex(QVector3D(-dimX, -dimY, -dimZ), Qt::yellow, QVector2D(0, 0)));
        addVertex(Vertex(QVector3D(-dimX, -dimY, dimZ), Qt::yellow, QVector2D(0, 1)));

        addVertex(Vertex(QVector3D(dimX, dimY, -dimZ), Qt::white, QVector2D(1, 1)));
        addVertex(Vertex(QVector3D(dimX, -dimY, -dimZ), Qt::white, QVector2D(1, 0)));
        addVertex(Vertex(QVector3D(-dimX, -dimY, -dimZ), Qt::white, QVector2D(0, 0)));
        addVertex(Vertex(QVector3D(-dimX, dimY, -dimZ), Qt::white, QVector2D(0, 1)));

        addVertex(Vertex(QVector3D(dimX, -dimY, dimZ), Qt::cyan, QVector2D(1, 0)));
        addVertex(Vertex(QVector3D(dimX, dimY, dimZ), Qt::cyan, QVector2D(1, 1)));
        addVertex(Vertex(QVector3D(-dimX, dimY, dimZ), Qt::cyan, QVector2D(0, 1)));
        addVertex(Vertex(QVector3D(-dimX, -dimY, dimZ), Qt::cyan, QVector2D(0, 0)));



    }
}
