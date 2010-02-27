#include "mesh.h"
namespace GluonGraphics
{
    Mesh::Mesh(QObject * parent)
        :QObject(parent)
    {
    }
    void  Mesh::clear()
    {
        m_vector.clear();
    }
    int Mesh::vertexCount()
    {
        return m_vector.size();
    }

    void Mesh::addVertex(const Vertex& vertex)
    {
        m_vector.append(vertex);
        computeGeometry();
    }
    void Mesh::addVertex(const QVector3D& coord)
    {
        Vertex vertex(coord);
        m_vector.append(vertex);
        computeGeometry();
    }
    void Mesh::addVertex(const QVector2D& coord)
    {
        Vertex vertex(coord);
        m_vector.append(vertex);
        computeGeometry();
    }
    QVector <Vertex> * Mesh::vertexes()
    {
        return &m_vector;
    }
    Vertex * Mesh::vertexAt(int i)
    {
        return &m_vector[i];
    }
    float * Mesh::array()
    {
        return (float*)m_vector.data();
    }

    float *Mesh::vertexArray()
    {
        return array();
    }

    float *Mesh::colorArray()
    {
        return &(array())[3];
    }

    float *Mesh::texCoordsArray()
    {
        return &(array())[7];
    }
    void Mesh::computeGeometry()
    {
        m_center = QVector3D(0,0,0);
        foreach(const Vertex &p, m_vector) {
            m_center += QVector3D(p.x(), p.y(), p.z());
        }
        m_center.setX(m_center.x() / vertexCount());
        m_center.setY(m_center.y() / vertexCount());
        m_center.setZ(m_center.z() / vertexCount());
    }
}
