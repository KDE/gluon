#ifndef KGLBASEITEM_H
#define KGLBASEITEM_H
#include <QObject>
#include <Eigen/Geometry>
#include <QRectF>
#include <QPolygonF>
#include <QTransform>
#include <QSizeF>
#include <QMatrix>
#include "glpoint.h"

const Eigen::Vector3d AXIS_X(1, 0, 0);
const Eigen::Vector3d AXIS_Y(0, 1, 0);
const Eigen::Vector3d AXIS_Z(0, 0, 1);

class KGLBaseItem: public QObject
{
    Q_OBJECT
public:
    KGLBaseItem(QObject *parent=0);
    ~KGLBaseItem();
    virtual inline void addVertex(GLPoint* p) {
        m_vertexList.push_back(p);
        computeGeometry();
    }
    GLPointList vertexList(){return m_vertexList;}
    virtual void removeVertex(GLPoint * p)
    {
        m_vertexList.removeOne (p);
        computeGeometry();
    }
    virtual void clear(){m_vertexList.clear();}
    virtual void updateTransform();
    virtual void resetTransform();
    void applyTransform(const Eigen::Transform3d &m){m_matrix = m * m_matrix;}



    void createBox(const QSizeF &s);
    void createBox(const float &w, const float &h){createBox(QSizeF(w,h));}

    void createPolygon(const QPolygonF &poly);
    void createLine(const QLineF &line);

    //Get
    unsigned int vertexNumber(){return m_vertexList.size();}
    inline const QPointF &position(){return m_position;}
    inline const float &scaleValue(){return m_scale;}
    inline const float &angle(){return m_angle;}
    inline const float &radius(){return m_radius;}
    inline unsigned int zindex(){return m_zindex;}

    inline const QPointF center(){return transform(m_center);}
    inline const QPointF &itemCenter(){return  m_center;}

    inline const QPolygonF polygon(){return transform(m_polygon);}
    inline const QPolygonF itemPolygon(){return m_polygon;}

    virtual inline const QRectF boundingBox(){return polygon().boundingRect();}
    virtual inline const QRectF itemBoundingBox(){return itemPolygon().boundingRect();}

    inline  bool contains(QPointF &p) {return polygon().containsPoint(p,Qt::WindingFill);}




    inline  Eigen::Transform3d& matrix() {
        return m_matrix;
    }

    inline void setMatrix(const Eigen::Transform3d& m){
        m_matrix = m;
    }
    //set
    inline void setCenter(const QPointF &c){m_center = c;}
    inline void setAngle(const float &a){m_angle = a;}
    inline void setScale(const float &s){m_scale = s;}
    inline void setPosition(const QPointF &p){m_position = p;}
    inline void setPosition(qreal x, qreal y ){setPosition(QPointF(x,y));}
    inline void setZIndex(int i){m_zindex = i;}


    inline void translate(QPointF step){m_position+=step;}
    inline void scale(float s){m_scale +=s;}
    inline void rotate(float angle){  m_angle += angle;}

protected:
    void computeGeometry();


    QPointF transform(QPointF p);
    QPolygonF transform(QPolygonF p);
    QRectF transform(QRectF r);
private:
    Eigen::Transform3d m_matrix;
    float m_angle;
    float m_scale;
    QPointF m_position;
    QPointF m_center;
    QPolygonF m_polygon;
    float m_radius;
    QSizeF m_dim;
    unsigned int m_zindex;
    GLPointList m_vertexList;




};





#endif // KGLBASEITEM_H
