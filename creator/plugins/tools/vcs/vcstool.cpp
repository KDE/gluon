/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Laszlo Papp <djszapi@archlinux.us>
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

#include "vcstool.h"

#include "widgets/vcscommitdialog.h"
// #include "widget/vcsdiffdialog.h"
// #include "widget/vcspushdialog.h"
// #include "widget/vcspulldialog.h"

#include <core/gluon_global.h>
#include <engine/game.h>

#include <KDE/KLocalizedString>
#include <KDE/KAction>

using namespace GluonCreator;

VcsTool::VcsTool( const QString& title, QWidget* parent, Qt::WindowFlags flags )
    : QWidget( parent, flags )
{
    setWindowTitle( title );
    setObjectName( "VcsTool" );
    setupActions( );
}

VcsTool::~VcsTool()
{
}

void VcsTool::setupActions()
{
    KAction* vcsToolCommit = new KAction( i18n( "Commit" ), this );
    vcsToolCommit->setObjectName( "VcsToolCommit" );
    connect( vcsToolCommit, SIGNAL( triggered( bool ) ), SLOT( commit() ) );

    KAction* vcsToolDiff = new KAction( i18n( "Diff" ), this );
    vcsToolDiff->setObjectName( "VcsToolDiff" );
    connect( vcsToolDiff, SIGNAL( triggered( bool ) ), SLOT( diff() ) );

    KAction* vcsToolPush = new KAction( i18n( "Push" ), this );
    vcsToolPush->setObjectName( "VcsToolPush" );
    connect( vcsToolPush, SIGNAL( triggered( bool ) ), SLOT( push() ) );

    KAction* vcsToolPull = new KAction( i18n( "Pull" ), this );
    vcsToolPull->setObjectName( "VcsToolPull" );
    connect( vcsToolPull, SIGNAL( triggered( bool ) ), SLOT( pull() ) );
}

void VcsTool::commit()
{
    VcsCommitDialog* vcsCommitDialog = new VcsCommitDialog();
    vcsCommitDialog->show();
}

void VcsTool::diff()
{

}

void VcsTool::push()
{

}

void VcsTool::pull()
{

}
