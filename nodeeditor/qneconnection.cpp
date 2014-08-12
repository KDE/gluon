/* Copyright (c) 2012, STANISLAW ADASZEWSKI
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
    * Neither the name of STANISLAW ADASZEWSKI nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL STANISLAW ADASZEWSKI BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */

#include "qneconnection.h"

#include "qneport.h"

#include <QBrush>
#include <QPen>
#include <QGraphicsScene>
#include <QtGui/QPalette>

QNEConnection::QNEConnection(QGraphicsItem *parent) : QGraphicsPathItem(parent)
{
    setZValue(-1);
    m_port1 = 0;
    m_port2 = 0;
    arrowSize = 10;
}

QNEConnection::~QNEConnection()
{
    if (m_port1)
        m_port1->connections().remove(m_port1->connections().indexOf(this));
    if (m_port2)
        m_port2->connections().remove(m_port2->connections().indexOf(this));
}

void QNEConnection::setPos1(const QPointF &p)
{
    pos1 = p;
}

void QNEConnection::setPos2(const QPointF &p)
{
    pos2 = p;
}

void QNEConnection::setPort1(QNEPort *p)
{
    m_port1 = p;

    m_port1->connections().append(this);
}

void QNEConnection::setPort2(QNEPort *p)
{
    m_port2 = p;

    m_port2->connections().append(this);
}

void QNEConnection::updatePosFromPorts()
{
    pos1 = m_port1->scenePos();
    pos2 = m_port2->scenePos();
}

//FIXME: width and length for arrow
QPolygonF QNEConnection::createArrowPoly(QPainterPath& p, QNEPort* conn) {
    float arrowStartPercentage;
    float arrowEndPercentage;

    if (conn->isOutput()) {
        arrowStartPercentage = p.percentAtLength(p.length() - conn->radius() - arrowSize);
        arrowEndPercentage = p.percentAtLength(p.length() - conn->radius());
    }
    else {
        //assuming is start connector, should throw exception otherwise?
        arrowStartPercentage = p.percentAtLength(conn->radius() + arrowSize);
        arrowEndPercentage = p.percentAtLength(conn->radius());
    }
    QPointF headStartP = p.pointAtPercent(arrowStartPercentage);
    QPointF headEndP = p.pointAtPercent(arrowEndPercentage);
    QLineF arrowMiddleLine(headStartP, headEndP);
    //QLineF normHead = arrowMiddleLine.normalVector();
    arrowMiddleLine.unitVector();
    QPointF normHead(arrowMiddleLine.dy(), -arrowMiddleLine.dx());
    QPointF arrowP1 = headStartP + normHead * 0.4;
    QPointF arrowP2 = headStartP - normHead * 0.4;

    QPolygonF arrowHeadEnd;
    arrowHeadEnd << headEndP << arrowP1 << arrowP2 << headEndP /*<< headEndP*/;
    return arrowHeadEnd;
}

void QNEConnection::updatePath()
{
    if(!m_port1 || !m_port2) {
        QPainterPath p;

        //QPointF pos1(m_port1->scenePos());
        //QPointF pos2(m_port2->scenePos());

        p.moveTo(pos1);

        qreal dx = pos2.x() - pos1.x();
        qreal dy = pos2.y() - pos1.y();

        QPointF ctr1(pos1.x() + dx * 0.25, pos1.y() + dy * 0.1);
        QPointF ctr2(pos1.x() + dx * 0.75, pos1.y() + dy * 0.9);

        p.cubicTo(ctr1, ctr2, pos2);

        setPath(p);
        return;
    }

    QPointF a(mapFromItem(m_port1, 0, 0));
    QPointF b(mapFromItem(m_port2, 0, 0));

    qreal dist = QLineF(a, b).length();
    qreal diffx = abs(a.x() - b.x());
    qreal diffy = abs(a.y() - b.y());

    QPointF left;
    QPointF right;
    QNEPort* leftConn;
    QNEPort* rightConn;
    if (a.x() < b.x()) {
        left = a;
        leftConn = m_port1;
        right = b;
        rightConn = m_port2;
    }
    else {
        left = b;
        leftConn = m_port2;
        right = a;
        rightConn = m_port1;
    }

    QPointF bottom;
    QPointF top;
    QNEPort* bottomConn;
    QNEPort* topConn;
    if (a.y() < b.y()) {
        top = a;
        topConn = m_port1;
        bottom = b;
        bottomConn = m_port2; 
    }
    else {
        top = b;
        topConn = m_port2;
        bottom = a;
        bottomConn = m_port1;
    }

    
    QPointF controlPoint1 = a;
    QPointF controlPoint2 = b;
    //how much to move control point from start or end point, default as used for simple case
    qreal moveX = 0.45 * diffx;
    qreal moveY = 0.45 * diffy;

    QSizeF combinedSize(30,30);
    if (leftConn->parentItem() != NULL) {
        combinedSize.setWidth(leftConn->parentItem()->boundingRect().width());
        combinedSize.setHeight(leftConn->parentItem()->boundingRect().height());
    }
    else {
        combinedSize.setWidth(5 * leftConn->radius());
        combinedSize.setWidth(5 * leftConn->radius());
    }
    if (rightConn->parentItem() != NULL) {
        combinedSize.setWidth(combinedSize.width() + rightConn->parentItem()->boundingRect().width());
        combinedSize.setHeight(combinedSize.height() + rightConn->parentItem()->boundingRect().height());
    }
    else {
        combinedSize.setWidth(combinedSize.width() + 5 * rightConn->radius());
        combinedSize.setHeight(combinedSize.height() + 5 * rightConn->radius());
    }
    
    

    if (leftConn->position() == rightConn->position() && leftConn->position() == QNEPort::LeftPosition && right.x() - left.x() < combinedSize.width()/2.0) {
        controlPoint1.setX(controlPoint1.x() - moveY/2.0 /*- combinedSize.width()/2.0*/);
        controlPoint2.setX(controlPoint2.x() - moveY/2.0 /*- combinedSize.width()/2.0*/);
    }
    else if (leftConn->position() == rightConn->position() && leftConn->position() == QNEPort::RightPosition && right.x() - left.x() < combinedSize.width()/2.0) {
        controlPoint1.setX(controlPoint1.x() + moveY/2.0 /*+ combinedSize.width()/2.0*/);
        controlPoint2.setX(controlPoint2.x() + moveY/2.0 /*+ combinedSize.width()/2.0*/);
    }
    else if (leftConn->position() == rightConn->position() && leftConn->position() == QNEPort::TopPosition && bottom.y() - top.y() < combinedSize.height()/2.0) {
        controlPoint1.setY(controlPoint1.y() - moveX/2.0 /*- combinedSize.height()/2.0*/);
        controlPoint2.setY(controlPoint2.y() - moveX/2.0 /*- combinedSize.height()/2.0*/);
    }
    else if (leftConn->position() == rightConn->position() && leftConn->position() == QNEPort::BottomPosition && bottom.y() - top.y() < combinedSize.height()/2.0) {
        controlPoint1.setY(controlPoint1.y() + moveX/2.0 /*+ combinedSize.height()/2.0*/);
        controlPoint2.setY(controlPoint2.y() + moveX/2.0 /*+ combinedSize.height()/2.0*/);
    }
    else
    //the simple case, they face each other the "good" way
    if (leftConn->position() != QNEPort::LeftPosition && rightConn->position() != QNEPort::RightPosition
            && topConn->position() != QNEPort::TopPosition && bottomConn->position() != QNEPort::BottomPosition) {

        //very simple: straight line
        //controlPoint1 = a + 0.3 * (b-a);
        //controlPoint2 = a + 0.7 * (b-a);

        controlPoint1 = a;
        controlPoint2 = b;
        //how much to move control point from start or end point
        qreal moveX = 0.45 * diffx;
        qreal moveY = 0.45 * diffy;
        if (dist > 5 * (m_port1->radius() + arrowSize)) {
            /* does mess up good case because moves there too
            if (abs(diffx-diffy) > 0.3 * dist) {
                moveX += abs(diffx-diffy);
                moveY += abs(diffx-diffy);
            }
            */
                
            if (moveX < 3 * (m_port1->radius() + arrowSize)) {
                moveX = 3 * (m_port1->radius() + arrowSize);
            }
            if (moveY < 3 * (m_port1->radius() + arrowSize)) {
                moveY = 3 * (m_port1->radius() + arrowSize);
            }
        }

        if (m_port1->position() == QNEPort::LeftPosition) {
            controlPoint1.setX(controlPoint1.x() - moveX);
        }
        else if (m_port1->position() == QNEPort::RightPosition) {
            controlPoint1.setX(controlPoint1.x() + moveX);
        }
        else if (m_port1->position() == QNEPort::BottomPosition) {
            controlPoint1.setY(controlPoint1.y() + moveY);
        }
        else if (m_port1->position() == QNEPort::TopPosition) {
            controlPoint1.setY(controlPoint1.y() - moveY);
        }

        if (m_port2->position() == QNEPort::LeftPosition) {
            controlPoint2.setX(controlPoint2.x() - moveX);
        }
        else if (m_port2->position() == QNEPort::RightPosition) {
            controlPoint2.setX(controlPoint2.x() + moveX);
        }
        else if (m_port2->position() == QNEPort::BottomPosition) {
            controlPoint2.setY(controlPoint2.y() + moveY);
        }
        else if (m_port2->position() == QNEPort::TopPosition) {
            controlPoint2.setY(controlPoint2.y() - moveY);
        }
    }
    //the bad case, method needs cleanup
    else {
        controlPoint1 = a;
        controlPoint2 = b;
        qreal maxMove = 0.5 * dist;
        moveX = 0.5 * dist;
        moveY = 0.5 * dist;
        if (m_port1->parentItem() != NULL) {
            maxMove = 1 * (m_port1->parentItem()->boundingRect().width() + m_port1->parentItem()->boundingRect().height());
        }
        else if (m_port2->parentItem() != NULL) {
            maxMove = 1 * (m_port2->parentItem()->boundingRect().width() + m_port2->parentItem()->boundingRect().height());
        }
        if (moveX > maxMove) {
            moveX = maxMove + 0.1 * (moveX-maxMove);
        }
        if (moveY > maxMove) {
            moveY = maxMove + 0.1 * (moveY-maxMove);
        }
        if (m_port1->position() == QNEPort::LeftPosition) {
            moveX *= -1;
            if ((m_port1 == topConn) == (m_port1 == rightConn)) {
                moveY *= -1;//relevantHeight;
            }
        }
        else if (m_port1->position() == QNEPort::RightPosition) {
            //moveX *= 1;
            if ((m_port1 == topConn) == (m_port1 == leftConn)) {
                moveY *= -1;//relevantHeight;
            }
        }
        else if (m_port1->position() == QNEPort::BottomPosition) {
            //moveY *= 1;
            if ((m_port1 == leftConn) == (m_port1 == topConn)) {
                moveX *= -1;
            }
        }
        else if (m_port1->position() == QNEPort::TopPosition) {
            moveY *= -1;
            if ((m_port1 == leftConn) == (m_port1 == bottomConn)) {
                moveX *= -1;
            }
        }

        /*
        if (m_port1->connectorAlignment() == m_port2->connectorAlignment()) {
            moveX *= 2;
            moveY *= 2;
        }
        */

        //ugly shit: handle some cases that don't look nice
        if (m_port2 == topConn && topConn->position() == QNEPort::TopPosition && (bottomConn->position() == QNEPort::LeftPosition || bottomConn->position() == QNEPort::RightPosition)) {
            moveY *= -1;
            //moveY = 0;
        }
        else if (m_port2 == bottomConn && bottomConn->position() == QNEPort::BottomPosition && (topConn->position() == QNEPort::LeftPosition || topConn->position() == QNEPort::RightPosition)) {
            moveY *= -1;
            //moveY = 0;
        }
        else if (m_port2 == leftConn && leftConn->position() == QNEPort::LeftPosition && (rightConn->position() == QNEPort::TopPosition || rightConn->position() == QNEPort::BottomPosition)) {
            moveX *= -1;
            //moveX = 0;
        }
        else if (m_port2 == rightConn && rightConn->position() == QNEPort::RightPosition && (leftConn->position() == QNEPort::TopPosition || leftConn->position() == QNEPort::BottomPosition)) {
            moveX *= -1;
            //moveX = 0;
        }

        controlPoint1.setX(controlPoint1.x() + moveX);
        controlPoint1.setY(controlPoint1.y() + moveY);


        moveX = 0.5 * dist;
        moveY = 0.5 * dist;
        // if start was null, then it was already set to end.
        if (m_port1->parentItem() != NULL && m_port2->parentItem() != NULL) {
            maxMove = 1 * (m_port2->parentItem()->boundingRect().width() + m_port2->parentItem()->boundingRect().height());
        }
        if (moveX > maxMove) {
            moveX = maxMove + 0.1 * (moveX-maxMove);
        }
        if (moveY > maxMove) {
            moveY = maxMove + 0.1 * (moveY-maxMove);
        }
        if (m_port2->position() == QNEPort::LeftPosition) {
            moveX *= -1;
            if ((m_port2 == topConn) == (m_port2 == rightConn)) {
                moveY *= -1;//relevantHeight;
            }
        }
        else if (m_port2->position() == QNEPort::RightPosition) {
            //moveX *= 1;
            if ((m_port2 == topConn) == (m_port2 == leftConn)) {
                moveY *= -1;//relevantHeight;
            }
        }
        else if (m_port2->position() == QNEPort::BottomPosition) {
            //moveY *= 1;
            if ((m_port1 == leftConn) == (m_port1 == topConn)) {
                moveX *= -1;
            }
        }
        else if (m_port2->position() == QNEPort::TopPosition) {
            moveY *= -1;
            if ((m_port1 == leftConn) == (m_port1 == bottomConn)) {
                moveX *= -1;
            }
        }

        /*
        if (m_port1->connectorAlignment() == m_port2->connectorAlignment()) {
            moveX *= 2;
            moveY *= 2;
        }*/


        //ugly shit: handle some cases that don't look nice
        if (m_port1 == topConn && topConn->position() == QNEPort::TopPosition && (bottomConn->position() == QNEPort::LeftPosition || bottomConn->position() == QNEPort::RightPosition)) {
            moveY *= -1;
            //moveY = 0;
        }
        else if (m_port1 == bottomConn && bottomConn->position() == QNEPort::BottomPosition && (topConn->position() == QNEPort::LeftPosition || topConn->position() == QNEPort::RightPosition)) {
            moveY *= -1;
            //moveY = 0;
        }
        else if (m_port1 == leftConn && leftConn->position() == QNEPort::LeftPosition && (rightConn->position() == QNEPort::TopPosition || rightConn->position() == QNEPort::BottomPosition)) {
            moveX *= -1;
            //moveX = 0;
        }
        else if (m_port1 == rightConn && rightConn->position() == QNEPort::RightPosition && (leftConn->position() == QNEPort::TopPosition || leftConn->position() == QNEPort::BottomPosition)) {
            moveX *= -1;
            //moveX = 0;
        }

        controlPoint2.setX(controlPoint2.x() + moveX);
        controlPoint2.setY(controlPoint2.y() + moveY);
    }


    QPainterPath p(a);
    p.cubicTo(controlPoint1, controlPoint2, b);
    if(m_port1->isOutput())
        p.addPolygon(createArrowPoly(p, m_port1));
    if(m_port2->isOutput())
        p.addPolygon(createArrowPoly(p, m_port2));
    this->setPath(p);

    QPalette palette = scene()->palette();
    setPen(QPen(palette.dark().color(), 2));
    setBrush(Qt::NoBrush);
}

QNEPort* QNEConnection::port1() const
{
    return m_port1;
}

QNEPort* QNEConnection::port2() const
{
    return m_port2;
}

void QNEConnection::save(QDataStream &ds)
{
    ds << (quint64) m_port1;
    ds << (quint64) m_port2;
}

void QNEConnection::load(QDataStream &ds, const QMap<quint64, QNEPort*> &portMap)
{
    quint64 ptr1;
    quint64 ptr2;
    ds >> ptr1;
    ds >> ptr2;

    setPort1(portMap[ptr1]);
    setPort2(portMap[ptr2]);
    updatePosFromPorts();
    updatePath();
}
