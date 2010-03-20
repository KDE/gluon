#ifndef Transform_H
#define Transform_H
#include <QMatrix4x4>
#include <QVector3D>
#include <QVector2D>
#include <QQuaternion>
#include <QSizeF>
#include <QObject>
#include <QPolygonF>
#include <QRectF>
#include "gluon_graphics_export.h"



namespace GluonGraphics
{
    class GLUON_GRAPHICS_EXPORT Transform : public QObject
    {
        public:
            Transform(QObject * parent = 0);
            virtual void updateTransform();
            virtual void resetTransform();
            void applyTransform(const QMatrix4x4 &m);
            QMatrix4x4 matrix();
            void setMatrix(const QMatrix4x4& m);
            void setScale(const QVector3D &s);
            void setScale(float sx, float sy, float sz);
            void setScale(float sx, float sy);
            void setScale(const QVector2D &s);

            void setPosition(const QVector3D &p);
            void setPosition(float x, float y, float z);
            void setPosition(float x, float y);
            void setPosition(const QVector2D &p);


            void setQuaternion(const QQuaternion &orientation);
            void setRotation(const qreal &angle, const QVector3D &axis);
            void setRotation(const qreal &angle, const QVector2D &center);
            void setRotation(const qreal &angle);

            void translate(const QVector3D &step);
            void translate(float x, float y, float z);
            void translate(float x, float y);
            void translate(const QVector2D &step);

            void scale(const QVector3D &s);
            void scale(float x, float y, float z);
            void scale(float x, float y);
            void scale(const QVector2D &s);
            //void rotate(const qreal &angle,const QVector3D &axis){}
            //void rotate(const qreal &angle, const QVector2D &center){}


            QVector3D transform(const QVector3D &p) ;
            QVector2D transform(const QVector2D &p) ;
            QPolygonF transform(const QPolygonF &p) ;
            QRectF transform(const QRectF &r) ;

        private:
            QMatrix4x4 m_matrix;

            QVector3D m_position;
            QVector3D m_scale;
            qreal m_angle;
            QQuaternion m_orientation;


    };
}//namespace
#endif // Transform_H
