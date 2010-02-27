#ifndef Mesh_H
#define Mesh_H
#include "gluon_graphics_export.h"

#include <QObject>
#include <QVector>
#include <QVector3D>
#include <QPolygonF>
#include "vertex.h"

namespace GluonGraphics
{
    class GLUON_GRAPHICS_EXPORT Mesh : public QObject
    {
    public:
        Mesh(QObject * parent=0);
        void addVertex(const Vertex& vertex);
        void addVertex(const QVector3D& coord);
        void addVertex(const QVector2D& coord);
        int vertexCount();
        Vertex * vertexAt(int i);
        QVector <Vertex> * vertexes();

        void clear();
        float * array();
        float *vertexArray();
        float *colorArray();
        float *texCoordsArray();


    protected:
        virtual void computeGeometry();

    private:
        QVector <Vertex> m_vector;
        QVector3D m_center;


    };
}//namespace

#endif // Mesh_H
