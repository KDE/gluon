/*
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2014 Arjen Hiemstra <ahiemstra@heimr.nl>
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
 *
 */

#include "welcomewindow.h"

#include <KWindowSystem/KWindowSystem>

using namespace GluonCreator;

WelcomeWindow::WelcomeWindow(QWindow* parent)
    : QQuickView( parent )
{
    setResizeMode( QQuickView::SizeRootObjectToView );
    setFlags( Qt::Dialog | Qt::FramelessWindowHint );
    setModality( Qt::ApplicationModal );
}

WelcomeWindow::~WelcomeWindow()
{
}

void WelcomeWindow::exposeEvent( QExposeEvent* event )
{
    KWindowSystem::setState( winId(), NET::SkipTaskbar | NET::SkipPager );

    QQuickView::exposeEvent( event );
}