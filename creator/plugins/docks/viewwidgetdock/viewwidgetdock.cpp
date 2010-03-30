/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <>
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

#include "viewwidgetdock.h"
#include "models/componentmodel.h"

#include <core/debughelper.h>
#include <engine/component.h>
#include <graphics/glwidget.h>
#include <objectmanager.h>
#include <engine/game.h>

using namespace GluonCreator;

class ViewWidgetDock::ViewWidgetDockPrivate
{
    public:
        ViewWidgetDockPrivate()
        {
            view = 0;
        };

        GluonGraphics::GLWidget *view;
};

ViewWidgetDock::ViewWidgetDock(const QString& title, QWidget* parent, Qt::WindowFlags flags): Dock(title, parent, flags)
{
    DEBUG_FUNC_NAME
    setObjectName("ViewWidgetDock");

    d = new ViewWidgetDockPrivate();

    d->view = new GluonGraphics::GLWidget(this);
    connect(GluonEngine::Game::instance(), SIGNAL(painted()), d->view, SLOT(updateGL()));

    setWidget(d->view);
}

ViewWidgetDock::~ViewWidgetDock()
{
    delete d;
}

void ViewWidgetDock::setSelection(GluonCore::GluonObject* obj)
{
    Q_UNUSED(obj);
}

QAbstractItemView* ViewWidgetDock::view()
{
    return 0;
}

QAbstractItemModel* ViewWidgetDock::model()
{
    return 0;
}

