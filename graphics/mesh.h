#ifndef Mesh_H
#define Mesh_H
#include "gluon_graphics_export.h"

#include <QObject>
#include <QVector>
#include <QVector3D>
#include <QPolygonF>
#include <QGLWidget>
#include "vertex.h"
#include "texture.h"

namespace GluonGraphics
{
    class GLUON_GRAPHICS_EXPORT Mesh : public QObject
    {
    public:
        Mesh(QObject * parent=0);
        void addVertex(const Vertex& vertex);
        void addVertex(const QVector3D& coord);
        void addVertex(const QVector2D& coord);
        void removeVertex(int id);

        int vertexCount();
        Vertex * vertexAt(int i);
        QVector <Vertex> * vertexes();
        void setGLMode(const GLenum& mode);
        void setColor(const QColor& col);
        void setAlpha(const float& alpha);
        void setTexture(Texture * texture);
        void setTexture(const QPixmap& pix);
        void setTexture(const QImage& img);
        void setTexture(const QString& path);

        void clear();
        float * array();
        float *vertexArray();
        float *colorArray();
        float *texCoordsArray();

        //return
        const GLenum& glMode(){return m_gl_mode;}
        const QColor& color(){return m_color;}
        const float& alpha(){return m_alpha;}
         Texture* texture(){return m_texture;}
    protected:
        virtual void computeGeometry();

    private:
        QVector <Vertex> m_vector;
        QVector3D m_center;
        GLenum m_gl_mode;
        QColor m_color;
        float m_alpha;
        Texture * m_texture;

    };
}//namespace

#endif // Mesh_H
