/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Arjen Hiemstra <ahiemstra@heimr.nl>
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


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui/QMatrix4x4>

class QMatrix4x4;
class QTimer;
namespace GluonGraphics
{
    class RenderWidget;
    class ParticleMesh;
    class Item;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    public:
        MainWindow( QWidget* parent = 0 );

    public Q_SLOTS:
        void initialize();
        void render();

    private:
        GluonGraphics::RenderWidget* m_widget;
        GluonGraphics::ParticleMesh* m_mesh;
        GluonGraphics::Item* m_item;
        QTimer* m_timer;
        QMatrix4x4 m_itemMatrix;
};
#endif // MAINWINDOW_H
