#include "mesh.h"
namespace GluonGraphics
{
    Mesh::Mesh(QObject * parent)
            : QObject(parent)
    {
        m_gl_mode = GL_POLYGON;
        m_color = Qt::white;
        m_alpha = 1;
        m_texture = new Texture;
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

    void Mesh::removeVertex(int id)
    {
        m_vector.remove(id);
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
        m_center = QVector3D(0, 0, 0);
        foreach(const Vertex &p, m_vector)
        {
            m_center += QVector3D(p.x(), p.y(), p.z());
        }
        m_center.setX(m_center.x() / vertexCount());
        m_center.setY(m_center.y() / vertexCount());
        m_center.setZ(m_center.z() / vertexCount());
    }
    //-------------------------------------------
    void Mesh::setColor(const QColor& col)
    {
        for (int i = 0; i < vertexes()->size(); ++i)
            (*vertexes())[i].setColor(col);
        m_color = col;
    }
    //-------------------------------------------
    void Mesh::setAlpha(const float& alpha)
    {
        for (int i = 0; i < vertexes()->size(); ++i)
            (*vertexes())[i].setAlpha(alpha);

        m_alpha = alpha;
    }
    //-------------------------------------------
    void Mesh::setGLMode(const GLenum& mode)
    {
        m_gl_mode = mode;
    }
    void Mesh::setTexture(Texture * texture)
    {
        m_texture = texture;
    }
    //------------------------------------------------------------
    void Mesh::setTexture(const QPixmap& pix)
    {
        m_texture = new Texture(pix);
    }
    //------------------------------------------------------------
    void Mesh::setTexture(const QImage& img)
    {
        m_texture = new Texture(img);
    }
    //------------------------------------------------------------
    void Mesh::setTexture(const QString& path)
    {
        m_texture = new Texture(path);
    }
    //------------------------------------------------------------

}
