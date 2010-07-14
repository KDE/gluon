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

#include "highscoresview.h"
#include <models/highscoresmodel.h>
#include <qtableview.h>
#include <QGraphicsLinearLayout>
#include <QGraphicsProxyWidget>

HighScoresView::HighScoresView(QGraphicsItem* parent, Qt::WindowFlags wFlags)
    : AbstractItemView(parent, wFlags), m_model(0)
{
    m_model = new GluonPlayer::HighScoresModel(this);
    m_view = new QTableView();
    m_view->setModel(m_model);
    QGraphicsLinearLayout *layout = new QGraphicsLinearLayout(this);
    QGraphicsProxyWidget *widget = new QGraphicsProxyWidget(this);
    widget->setWidget(m_view);
    layout->addItem(widget);
    setLayout(layout);
}

HighScoresView::~HighScoresView()
{
    delete m_view;
}
