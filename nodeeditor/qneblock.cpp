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

#include "qneblock.h"

#include <QPen>
#include <QGraphicsScene>
#include <QFontMetrics>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include "qneport.h"

QNEBlock::QNEBlock(QGraphicsItem *parent) : QGraphicsPathItem(parent)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    horzMargin = 20;
    vertMargin = 5;
    portSpacing = 8;
}

void QNEBlock::relayoutPorts()
{
    int topTextLength = 0, rightTextLength = 0, bottomTextLength = 0, leftTextLength = 0;
    int topCount = 0, rightCount = 0, bottomCount = 0, leftCount = 0;
    QFontMetrics fm(scene()->font());
    Q_FOREACH(QGraphicsItem *port_, childItems()) {
        if (port_->type() != QNEPort::Type)
            continue;

        QNEPort *port = (QNEPort*) port_;
        int w = fm.width(port->portName());

        switch(port->position())
        {
            case QNEPort::TopPosition:
                if(w > topTextLength)
                    topTextLength = w;
                ++topCount;
                break;
            case QNEPort::RightPosition:
                if(w > rightTextLength)
                    rightTextLength = w;
                ++rightCount;
                break;
            case QNEPort::BottomPosition:
                if(w > bottomTextLength)
                    bottomTextLength = w;
                ++bottomCount;
                break;
            case QNEPort::LeftPosition:
                if(w > leftTextLength)
                    leftTextLength = w;
                ++leftCount;
                break;
            default:
                // some terrible error, this should not happen!
                break;
        }
    }

    if(topCount == 0 && bottomCount == 0)
        width = leftTextLength + horzMargin * 2 + rightTextLength;
    else if(topCount > bottomCount)
        width = leftTextLength + horzMargin * 2 + rightTextLength + topCount * (QNEPort::radius() + portSpacing);
    else
        width = leftTextLength + horzMargin * 2 + rightTextLength + bottomCount * (QNEPort::radius() + portSpacing);
    if(leftCount == 0 && rightCount == 0)
        height = topTextLength + vertMargin + bottomTextLength;
    else if(leftCount > rightCount)
        height = topTextLength + QNEPort::radius() * 2  + vertMargin + (leftCount * (QNEPort::radius() + portSpacing)) + vertMargin + bottomTextLength;
    else
        height = topTextLength + QNEPort::radius() * 2  + vertMargin + (rightCount * (QNEPort::radius() + portSpacing)) + vertMargin + bottomTextLength;

    QPainterPath p;
    p.addRoundedRect(-width / 2, -height / 2, width, height, 5, 5);
    setPath(p);

    int topStart = - (((topCount - 1) * portSpacing) + (topCount * QNEPort::radius())) / 2;
    int rightStart = - (height / 2) + (topTextLength + vertMargin + QNEPort::radius() * 2);
    int bottomStart = - (((bottomCount - 1) * portSpacing) + (bottomCount * QNEPort::radius())) / 2;
    int leftStart = - (height / 2) + (topTextLength + vertMargin + QNEPort::radius() * 2);
    int top = 0, right = 0, bottom = 0, left = 0;
    Q_FOREACH(QGraphicsItem *port_, childItems()) {
        if (port_->type() != QNEPort::Type)
            continue;

        QNEPort *port = (QNEPort*) port_;
        switch(port->position())
        {
            case QNEPort::TopPosition:
                port->setPos(topStart + ((portSpacing + port->radius()) * top), - height / 2);
                ++top;
                break;
            case QNEPort::RightPosition:
                port->setPos(width / 2, rightStart + ((portSpacing + port->radius()) * right));
                ++right;
                break;
            case QNEPort::BottomPosition:
                port->setPos(bottomStart + ((portSpacing + port->radius()) * bottom), height / 2);
                ++bottom;
                break;
            case QNEPort::LeftPosition:
                port->setPos(-width / 2, leftStart + ((portSpacing + port->radius()) * left));
                ++left;
                break;
            default:
                // some terrible error, this should not happen!
                break;
        }
    }
}

QNEPort* QNEBlock::addPort(const QString &name, QNEPort::Position position, bool isOutput, int flags, int ptr)
{
    QNEPort *port = new QNEPort(this);
    port->setName(name);
    port->setPosition(position);
    port->setIsOutput(isOutput);
    port->setNEBlock(this);
    port->setPortFlags(flags);
    port->setPtr(ptr);

    relayoutPorts();
    return port;
}

void QNEBlock::addInputPort(const QString &name)
{
    addPort(name, QNEPort::TopPosition, false);
}

void QNEBlock::addOutputPort(const QString &name)
{
    addPort(name, QNEPort::BottomPosition, true);
}

void QNEBlock::addInputPorts(const QStringList &names)
{
    Q_FOREACH(QString n, names)
        addInputPort(n);
}

void QNEBlock::addOutputPorts(const QStringList &names)
{
    Q_FOREACH(QString n, names)
        addOutputPort(n);
}

void QNEBlock::save(QDataStream &ds)
{
    ds << pos();

    int count(0);

    Q_FOREACH(QGraphicsItem *port_, childItems())
    {
        if (port_->type() != QNEPort::Type)
            continue;

        count++;
    }

    ds << count;

    Q_FOREACH(QGraphicsItem *port_, childItems())
    {
        if (port_->type() != QNEPort::Type)
            continue;

        QNEPort *port = (QNEPort*) port_;
        ds << (quint64) port;
        ds << (quint8) port->position();
        ds << port->portName();
        ds << port->isOutput();
        ds << port->portFlags();
    }
}

void QNEBlock::load(QDataStream &ds, QMap<quint64, QNEPort*> &portMap)
{
    QPointF p;
    ds >> p;
    setPos(p);
    int count;
    ds >> count;
    for (int i = 0; i < count; i++)
    {
        QString name;
        bool output;
        int flags;
        int position;
        quint64 ptr;

        ds >> ptr;
        ds >> position;
        ds >> name;
        ds >> output;
        ds >> flags;
        portMap[ptr] = addPort(name, (QNEPort::Position)position, output, flags, ptr);
    }
}

void QNEBlock::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)

    QPalette palette = widget->palette();
    if (isSelected()) {
        painter->setPen(QPen(palette.highlightedText().color()));
        painter->setBrush(palette.highlight());
    } else {
        painter->setPen(QPen(palette.buttonText().color()));
        painter->setBrush(palette.button());
    }

    painter->drawPath(path());
}

QNEBlock* QNEBlock::clone()
{
    QNEBlock *b = new QNEBlock(0);
    this->scene()->addItem(b);

    Q_FOREACH(QGraphicsItem *port_, childItems())
    {
        if (port_->type() == QNEPort::Type)
        {
            QNEPort *port = (QNEPort*) port_;
            b->addPort(port->portName(), port->position(), port->isOutput(), port->portFlags(), port->ptr());
        }
    }

    return b;
}

QVector<QNEPort*> QNEBlock::ports()
{
    QVector<QNEPort*> res;
    Q_FOREACH(QGraphicsItem *port_, childItems())
    {
        if (port_->type() == QNEPort::Type)
            res.append((QNEPort*) port_);
    }
    return res;
}

QVariant QNEBlock::itemChange(GraphicsItemChange change, const QVariant &value)
{
    Q_UNUSED(change);

    return value;
}

