#include "transform.h"
#define Z2D 0
namespace GluonGraphics
{
    Transform::Transform(QObject * parent)
        :QObject(parent)
    {
        m_scale = QVector3D(1,1,1);
        m_orientation = QQuaternion(1,0,0,0);
        m_position = QVector3D(0,0,0);
        m_angle = 0;
    }
    void  Transform::updateTransform()
    {
        m_matrix.setToIdentity();
        m_matrix.translate(m_position);
        m_matrix.scale(m_scale);
        m_matrix.rotate(m_orientation);
    }

    void Transform::resetTransform()
    {
        m_matrix.setToIdentity();
        m_position = QVector3D(0,0,0);
        m_scale = QVector3D(1,1,1);
        m_orientation = QQuaternion(1,0,0,0);
        m_angle = 0;
    }
    //------------------------------------------------------

    QVector3D Transform::transform(const QVector3D &p)
    {
        QVector3D vect = m_matrix * QVector3D(p.x(), p.y(), p.y());
        return vect;
    }

    //------------------------------------------------------
     QVector2D Transform::transform(const QVector2D &p)
    {
        QVector3D vect = m_matrix * QVector3D(p.x(), p.y(), Z2D);
        return QVector2D(vect.x(), vect.y());
    }


    //------------------------------------------------------

    QPolygonF Transform::transform(const QPolygonF &p)
    {
        QPolygonF poly;
        foreach(const QPointF &point, p) {
            QVector2D v = transform(QVector2D(point.x(),point.y()));
            poly<<v.toPointF();
        }
        return poly;
    }

    //------------------------------------------------------

    QRectF Transform::transform(const QRectF &r)
    {
        QVector3D a = m_matrix * QVector3D(r.x(), r.y(), 0);
        QVector3D b = m_matrix * QVector3D(r.width(), r.height(), 0);

        return QRectF(a.x(), a.y(), b.x(), b.y());
    }
    //------------------------------------------------------

    void Transform::applyTransform(const QMatrix4x4 &m)
    {
        m_matrix = m * m_matrix;
    }
    //------------------------------------------------------

    QMatrix4x4 Transform::matrix(){
        return m_matrix;
    }

    //------------------------------------------------------
    void Transform::setMatrix(const QMatrix4x4& m){
        m_matrix = m;
    }
    //------------------------------------------------------
    void Transform::setScale(const QVector3D &s)
    {
        m_scale = s;
    }
    //------------------------------------------------------
    void Transform::setScale(const QVector2D &s)
    {
        m_scale = QVector3D(s.x(),s.y(),Z2D);
    }
    //------------------------------------------------------

    void Transform::setScale(float sx, float sy, float sz)
    {
        setScale(QVector3D(sx, sy, sz));
    }
    //------------------------------------------------------

    void Transform::setScale(float sx, float sy)
    {
        setScale(QVector3D(sx, sy, Z2D));
    }
    //------------------------------------------------------

    void Transform::setPosition(const QVector3D &p)
    {
        m_position = p;
    }
    //------------------------------------------------------

    void Transform::setPosition(const QVector2D &p)
    {
        m_position = QVector3D(p.x(),p.y(),Z2D);
    }
    //------------------------------------------------------

    void Transform::setPosition(float x, float y)
    {
        setPosition(QVector3D(x, y, Z2D));
    }
    //------------------------------------------------------

    void Transform::setQuaternion(const QQuaternion &orientation)
    {
    m_orientation = orientation;

    }
    //------------------------------------------------------

    void Transform::setRotation( const qreal &angle,const QVector3D &axis){

        m_orientation = QQuaternion::fromAxisAndAngle (axis, angle );
        m_angle = angle;

    }
    //------------------------------------------------------

    void Transform::setRotation(const qreal &angle,const QVector2D &center){

        QVector3D axis= QVector3D(center.x(),center.y(),1);
        m_orientation = QQuaternion::fromAxisAndAngle (axis, angle );
        m_angle=angle;

    }
    //------------------------------------------------------

    void Transform::setRotation(const qreal &angle){

        QVector3D axis= QVector3D(0,0,1);
        m_orientation = QQuaternion::fromAxisAndAngle (axis, angle );
        m_angle=angle;

    }
    //------------------------------------------------------

    void Transform::translate(const QVector3D &step)
    {
        m_position += step;
    }
    //------------------------------------------------------

    void Transform::translate(const QVector2D &step)
    {
        m_position += QVector3D(step.x(),step.y(),Z2D);
    }
    //------------------------------------------------------

    void Transform::translate(float x, float y, float z)
    {
        translate(QVector3D(x, y, z));
    }
    //------------------------------------------------------

    void Transform::translate(float x, float y)
    {
        translate(QVector3D(x, y, Z2D));
    }
    //------------------------------------------------------

    void Transform::scale(const QVector3D &s)
    {
        m_scale = s;
    }
    //------------------------------------------------------

    void Transform::scale(const QVector2D &s)
    {
        m_scale = QVector3D(s.x(),s.y(),Z2D);
    }
    //------------------------------------------------------
    void Transform::scale(float x, float y)
    {
        scale(QVector3D(x, y, Z2D));
    }






}//namespace
