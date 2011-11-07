/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Laszlo Papp <lpapp@kde.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef NODEITEM_H
#define NODEITEM_H

#include "node.h"

#include <QGraphicsSvgItem>
#include <QPropertyAnimation>
#include <QSvgRenderer>
#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsColorizeEffect>
#include <QFont>
#include <QPixmap>
#include <QGraphicsItem>

//#include <QtGui/QGraphicsTextItem>
//#include <QtGui/QGraphicsPixmapItem>
//#include <QtGui/QGraphicsColorizeEffect>
//#include <QtGui/QFont>
//#include <QtGui/QPixmap>
//#include <QtGui/QGraphicsItem>

#include <QtSvg/QGraphicsSvgItem>
#include <QtSvg/QSvgRenderer>

#include <QtCore/QStateMachine>
#include <QtCore/QState>
#include <QtCore/QString>
#include <QtCore/QEvent>
#include <QtCore/QMap>
#include <QtCore/QList>
#include <QtCore/QHash>
#include <QtCore/QListIterator>
#include <QtCore/QByteArray>

class NodeItem : public QGraphicsSvgItem
{
        Q_OBJECT
        qreal _originalWidth;
        qreal _width;
    public:
        NodeItem( Node* n );
        enum { Type = 65578 };
        Node* node() const
        {
            return _node;
        }
        static QMap<QString, QSvgRenderer*> _renders;
        /**
         * Hash used to associate name value with graphical representation.
         */
        QHash<QString, QGraphicsSvgItem*> connectors();
        /**
         * Type of Node to display.
         */
        int type() const
        {
            return Type;
        }
    public slots:
        /**
        * Sets up Node of Graph. Main function to call, which calls other functions.
         */
        void setupNode();
    private slots:
        void updateRenderer();
        void updateIcon();
        void updateName();
        void updateValue();
        void updateColor();
        void updatePos();
        void updateSize();
        /**
         * Updates visual representation of Nodes and Edges.
         * @todo    Clean up section into separate Node and Edge updater.
         */
        void updateConnectors();
        void updateImage();
    private:
        Node* _node;
        QString _iconPackage;
        QString _element;
        QGraphicsSimpleTextItem* _name;
        QGraphicsSimpleTextItem* _value;
        QGraphicsPixmapItem* _image;
        QHash<QString, QGraphicsSvgItem*> _connectors;
        QGraphicsColorizeEffect* _colorizer;
        QFont _font;
        int ldown;
        int rdown;
        int previousCount;
};

#endif

