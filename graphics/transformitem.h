#ifndef TRANSFORMITEM_H
#define TRANSFORMITEM_H
#include <QMatrix4x4>
#include <QVector3D>
#include <QQuaternion>
#include <QSizeF>
#include <QObject>
#include <QPolygonF>
#include <QRectF>
#include "gluon_graphics_export.h"

namespace GluonGraphics
{
class GLUON_GRAPHICS_EXPORT TransformItem : public QObject
{
public:
    TransformItem(QObject * parent=0);
    virtual void updateTransform();
    virtual void resetTransform();
    void applyTransform(const QMatrix4x4 &m);
    QMatrix4x4 matrix();
    void setMatrix(const QMatrix4x4& m);
    inline void setScale(const QVector3D &s);
    inline void setScale(float sx, float sy, float sz);
    inline void setPosition(const QVector3D &p);
    inline void setPosition(float x, float y, float z);
    inline void setQuaternion(const QQuaternion &orientation);
    inline void setRotation(const QVector3D &axis, const qreal &angle );
    inline void translate(const QVector3D &step);
    inline void translate(float x, float y, float z);
    inline void scale(const QVector3D &s);
    inline void scale(float x, float y, float z);

    QVector3D transform(const QVector3D &p) const;
    QPointF transform(const QPointF &p) const;
    QPolygonF transform(const QPolygonF &p) const;
    QRectF transform(const QRectF &r) const;

private:
    QMatrix4x4 m_matrix;

    QVector3D m_position;
    QVector3D m_scale;
    QQuaternion m_orientation;


};
}//namespace
#endif // TRANSFORMITEM_H
