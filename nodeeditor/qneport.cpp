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

#include "qneport.h"
#include "qneconnection.h"

#include <QGraphicsScene>
#include <QFontMetrics>

#include <QPen>
#include <QtCore/QRect>
#include <QtGui/QPalette>


QNEPort::QNEPort(QGraphicsItem *parent):
    QGraphicsPathItem(parent)
{
    label = new QGraphicsTextItem(this);

    radius_ = radius();
    margin = 2;

    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);

    m_portFlags = QNEPort::StandardPort;
    m_position = QNEPort::LeftPosition;
    setIsOutput(false);
}

QNEPort::~QNEPort()
{
    Q_FOREACH(QNEConnection *conn, m_connections) {
        delete conn;
    }
}

void QNEPort::setNEBlock(QNEBlock *b)
{
    m_block = b;
}

void QNEPort::setName(const QString &n)
{
    name = n;
    label->setPlainText(n);
}

void QNEPort::setIsOutput(bool o)
{
    isOutput_ = o;
    updatePath();
}

void QNEPort::updatePath()
{
    QPainterPath p;
    if(m_portFlags & NamePort || m_portFlags & TypePort) {
        // don't do anything, as we want an empty path for these
    }
    else if(isOutput_) {
        p.addEllipse(-radius_, -radius_, 2*radius_, 2*radius_);
    }
    else {
        p.addRect(-radius_, -radius_, 2*radius_, 2*radius_);
    }
    setPath(p);

    QPalette palette = scene()->palette();
    setPen(palette.buttonText().color());
    setBrush(palette.link());
}

void QNEPort::setPosition(QNEPort::Position position)
{
    m_position = position;

    switch(position)
    {
        case QNEPort::RightPosition:
            label->setPos(-radius_ - margin - label->boundingRect().width(), -label->boundingRect().height()/2);
            setRotation(0);
            break;
        case QNEPort::TopPosition:
            label->setPos(radius_ + margin, -label->boundingRect().height()/2);
            setRotation(90);
            break;
        case QNEPort::BottomPosition:
            label->setPos(radius_ + margin, -label->boundingRect().height()/2);
            setRotation(-90);
            break;
        case QNEPort::LeftPosition:
            label->setPos(radius_ + margin, -label->boundingRect().height()/2);
            setRotation(0);
            break;
        default:
            // Nuh! Bad position! Bad! Go to your room and think about what you've done.
            break;
    }
}

QNEPort::Position QNEPort::position() const
{
    return m_position;
}

int QNEPort::radius()
{
    return 5;
}

bool QNEPort::isOutput()
{
    return isOutput_;
}

QVector<QNEConnection*>& QNEPort::connections()
{
    return m_connections;
}

void QNEPort::setPortFlags(int f)
{
    m_portFlags = f;

    // If the flaf is type or name, then it's not really
    // a port and consequently is given a non-path, and
    // different font options
    if (m_portFlags & TypePort)
    {
        QFont font(scene()->font());
        font.setItalic(true);
        label->setFont(font);
    } else if (m_portFlags & NamePort)
    {
        QFont font(scene()->font());
        font.setBold(true);
        label->setFont(font);
    }
    updatePath();
}

QNEBlock* QNEPort::block() const
{
    return m_block;
}

quint64 QNEPort::ptr()
{
    return m_ptr;
}

void QNEPort::setPtr(quint64 p)
{
    m_ptr = p;
}

bool QNEPort::isConnected(QNEPort *other)
{
    Q_FOREACH(QNEConnection *conn, m_connections) {
        if (conn->port1() == other || conn->port2() == other)
            return true;
    }

    return false;
}

QVariant QNEPort::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemScenePositionHasChanged)
    {
        Q_FOREACH(QNEConnection *conn, m_connections)
        {
            conn->updatePosFromPorts();
            conn->updatePath();
        }
    }
    return value;
}
