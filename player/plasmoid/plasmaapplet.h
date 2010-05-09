/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2008 Rivo Laks <rivolaks@hot.ee>
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2008 Olivier Gueudelot <gueudelotolive@gmail.com>
 * Copyright (C) 2008 Charles Huet <packadal@gmail.com>
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (c) 2010 Shantanu Tushar Jha <jhahoneyk@gmail.com>
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

#ifndef PLASMAAPPLET_H
#define PLASMAAPPLET_H

#include <GL/glew.h>
#include "glfboapplet.h"

#include <QModelIndex>

namespace GluonEngine
{
    class GameProject;
}

namespace GluonGraphics
{
    class Camera;
}

namespace GluonPlayer
{
    class GamesModel;
    class GamesView;

    class PlasmaApplet : public GLFBOApplet
    {
        Q_OBJECT

    public:
        PlasmaApplet(QObject *parent, const QVariantList &args);
        virtual ~PlasmaApplet();
        void init();
        virtual void paintGLInterface (QPainter *painter, const QStyleOptionGraphicsItem *option);

    private:
        int m_viewportWidth;
        int m_viewportHeight;
        QString m_gameFileName;
        GluonEngine::GameProject *m_project;
        GluonGraphics::Camera *m_camera;
        GamesModel *m_gamesModel;
        GamesView *m_gamesView;

        void initGL();
        void render();

    protected:
        void resizeEvent(QGraphicsSceneResizeEvent *event);

    protected slots:
        void openProject();
        void setProject(const QModelIndex &index);
        void doPaint();
        void startGame();
        void setCamera(GluonGraphics::Camera* camera);
    };
}

K_EXPORT_PLASMA_APPLET(gluonplayer, GluonPlayer::PlasmaApplet)

#endif // PLASMAAPPLET_H
