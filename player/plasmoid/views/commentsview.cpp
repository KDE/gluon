/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Shantanu Tushar <jhahoneyk@gmail.com>
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

#include "commentsview.h"
#include "models/commentsmodel.h"

#include <QTreeView>
#include <QGraphicsLinearLayout>
#include <QGraphicsProxyWidget>

CommentsView::CommentsView (QGraphicsItem* parent, Qt::WindowFlags wFlags) : AbstractItemView (parent, wFlags)
{
    m_model = new GluonPlayer::CommentsModel(this);
    m_treeView = new QTreeView();
    m_treeView->setModel(m_model);
    QGraphicsLinearLayout *layout = new QGraphicsLinearLayout(this);
    QGraphicsProxyWidget *widget = new QGraphicsProxyWidget(this);
    widget->setWidget(m_treeView);
    layout->addItem(widget);
    setLayout(layout);
}

CommentsView::~CommentsView()
{
    delete m_treeView;
}
