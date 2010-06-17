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

#include "componentsdock.h"
#include "componentslistmodelsortproxy.h"
#include "models/componentmodel.h"

#include <KCategorizedView>
#include <KDebug>

#include <core/gluonobjectfactory.h>
#include <core/gluonobject.h>
#include <core/debughelper.h>
#include <engine/component.h>

using namespace GluonCreator;

class ComponentsDock::ComponentsDockPrivate
{
    public:
        ComponentsDockPrivate()
            : view(0)
            , sortModel(0)
            , model(0)
        { };

        KCategorizedView *view;
        ComponentsListModelSortProxy *sortModel;
        ComponentModel *model;
};

ComponentsDock::ComponentsDock(const QString& title, QWidget* parent, Qt::WindowFlags flags)
    : QDockWidget(title, parent, flags)
{
    DEBUG_FUNC_NAME
    setObjectName("ComponentsDock");

    d = new ComponentsDockPrivate();

    d->view = new KCategorizedView(this);
    d->view->setSelectionMode(QAbstractItemView::SingleSelection);
    d->view->setDragEnabled(true);
    d->view->setAcceptDrops(false);
    d->view->setDropIndicatorShown(false);

    d->model = new ComponentModel(this);
    d->sortModel = new ComponentsListModelSortProxy(this);
    d->sortModel->setSourceModel(d->model);
    d->sortModel->setCategorizedModel(true);
    d->view->setModel(d->sortModel);

    setWidget(d->view);
}

ComponentsDock::~ComponentsDock()
{
    delete d;
}
