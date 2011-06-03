/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#ifndef EDGEPROPERTIESWIDGET_H
#define EDGEPROPERTIESWIDGET_H

#include <QtGui/QWidget>
#include "ui_EdgePropertiesWidget.h"
#include <QString>
#include <QColor>

class Edge;
class MainWindow;
#include <QPointF>

class EdgePropertiesWidget : public QWidget, public Ui::EdgePropertiesWidget
{
        Q_OBJECT
    public:
        EdgePropertiesWidget( QWidget* parent );
        void setEdge( Edge* e, QPointF pos );

    public slots:
        void on__color_activated( const QColor& c );
        void on__style_activated( int index );
        void reflectAttributes();
        void on__addProperty_clicked();
        void disconnectEdge();

    private:
        Edge* _edge;
};

#endif // EDGEPROPERTIESWIDGET_H
