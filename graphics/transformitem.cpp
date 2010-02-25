#include "transformitem.h"
namespace GluonGraphics
{
    TransformItem::TransformItem(QObject * parent)
        :QObject(parent)
    {
        m_scale = QVector3D(1,1,1);
        m_orientation = QQuaternion(1,0,0,0);
        m_position = QVector3D(0,0,0);



    }


    void  TransformItem::updateTransform()
    {
        m_matrix.setToIdentity();
        m_matrix.translate(m_position);
        m_matrix.scale(m_scale);
        m_matrix.rotate(m_orientation);
    }

    void TransformItem::resetTransform()
    {
        m_matrix.setToIdentity();;
        m_position = QVector3D(0,0,0);
        m_scale = QVector3D(1,1,1);
        m_orientation = QQuaternion(1,0,0,0);
    }
    //------------------------------------------------------

    QVector3D TransformItem::transform(const QVector3D &p) const
    {
        QVector3D vect = m_matrix * QVector3D(p.x(), p.y(), p.y());
        return vect;
    }

    //------------------------------------------------------

    QPointF TransformItem::transform(const QPointF &p) const
    {
        QVector3D vect = m_matrix * QVector3D(p.x(), p.y(), 0);
        return QPointF(vect.x(), vect.y());
    }

    //------------------------------------------------------

    QPolygonF TransformItem::transform(const QPolygonF &p) const
    {
        QPolygonF poly;
        foreach(const QPointF &point, p) {
            poly<<transform(point);
        }
        return poly;
    }

    //------------------------------------------------------

    QRectF TransformItem::transform(const QRectF &r) const
    {
        QVector3D a = m_matrix * QVector3D(r.x(), r.y(), 0);
        QVector3D b = m_matrix * QVector3D(r.width(), r.height(), 0);

        return QRectF(a.x(), a.y(), b.x(), b.y());
    }
    //------------------------------------------------------

    void TransformItem::applyTransform(const QMatrix4x4 &m)
    {
        m_matrix = m * m_matrix;
    }
    //------------------------------------------------------

    QMatrix4x4 TransformItem::matrix(){
        return m_matrix;
    }

    //------------------------------------------------------
    void TransformItem::setMatrix(const QMatrix4x4& m){
        m_matrix = m;
    }
    //------------------------------------------------------
    void TransformItem::setScale(const QVector3D &s)
    {
        m_scale = s;
    }
    void TransformItem::setScale(float sx, float sy, float sz)
    {
        setScale(QVector3D(sx, sy, sz));
    }

    void TransformItem::setPosition(const QVector3D &p)
    {
        m_position = p;
    }

    void TransformItem::setPosition(float x, float y, float z)
    {
        setPosition(QVector3D(x, y, z));
    }

    void TransformItem::setQuaternion(const QQuaternion &orientation)
    {
    m_orientation = orientation;

    }

    void TransformItem::setRotation(const QVector3D &axis, const qreal &angle ){

        m_orientation = QQuaternion::fromAxisAndAngle (axis, angle );

    }

    void TransformItem::translate(const QVector3D &step)
    {
        m_position += step;
    }

    void TransformItem::translate(float x, float y, float z)
    {
        translate(QVector3D(x, y, z));
    }

    void TransformItem::scale(const QVector3D &s)
    {
        m_scale = s;
    }
    void TransformItem::scale(float x, float y, float z)
    {
        scale(QVector3D(x, y, z));
    }






}//namespace
