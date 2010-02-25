#ifndef SHAPEITEM_H
#define SHAPEITEM_H
#include "gluon_graphics_export.h"

#include <QObject>
#include <QVector>
#include <QVector3D>
#include <QPolygonF>
#include "vertex.h"

namespace GluonGraphics
{
    class GLUON_GRAPHICS_EXPORT ShapeItem : public QObject
    {
    public:
        ShapeItem(QObject * parent=0);
        void addVertex(const Vertex& vertex)
        {
        m_vector.append(vertex);
        }

        void clear(){m_vector.clear();}


        void createRect(const QSizeF &s){}
        void createPolygon(const QPolygonF &poly){}
        void createCube(){}
        void createPlane(){}
        void createTube(){}
        void createGrid(){}
        void createUVSphere(){}
        void createCone(){}
        void createIcoSphere(){}
        void createCylinder(){}
        void createGrid(){}

        float * array()
        {
            return (float*)m_vector.data();
        }

        float *vertexStart()
        {
            return array();
        }

        float *colorStart()
        {
            return &(array())[3];
        }

        float *texCoordStart()
        {
            return &(array())[7];
        }

        const QPolygonF polygon() const{}
        const QPolygonF boundingBox() const{}
        const QVector3D center()const{}
        unsigned int vertexCount() const{}


    protected:
        void computeGeometry(){};

    private:
        QVector <Vertex> m_vector;
        QPolygonF m_polygon;
        QVector3D m_center;
        float m_radius;




    };
}//namespace

#endif // SHAPEITEM_H
