/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Dan Leinir Turthra Jensen <admin@leinir.dk>
 * Copyright (C) 2011 Felix Rohrbach <fxrh@gmx.de>
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

#include "prefabcontrols.h"

#include <engine/abstractprefabinstance.h>

#include <QtGui/QHBoxLayout>
#include <QtGui/QPushButton>

using namespace GluonCreator;

PrefabControls::PrefabControls( GluonEngine::AbstractPrefabInstance* instance, QWidget* parent, Qt::WindowFlags f )
    : QWidget(parent, f)
    , m_instance( instance )
{
    m_layout = new QHBoxLayout();
    m_revertButton = new QPushButton( tr("Revert") );
    if( !instance->hasGameObjectChanged() )
        m_revertButton->setEnabled( false );

    m_applyButton = new QPushButton( tr("Apply") );
    if( !instance->hasGameObjectChanged() )
        m_applyButton->setEnabled( false );

    m_layout->addWidget( m_revertButton );
    m_layout->addWidget( m_applyButton );
    setLayout( m_layout );

    connect( instance, SIGNAL(instanceChanged()), this, SLOT(enableButtons()) );
    connect( instance, SIGNAL(instanceReverted()), this, SLOT(disableButtons()) );
    connect( instance, SIGNAL(instanceStored()), this, SLOT(disableButtons()) );
    connect( m_revertButton, SIGNAL(clicked()), instance, SLOT(revertChanges()) );
    connect( m_applyButton, SIGNAL(clicked()), instance, SLOT(storeChanges()) );
}

PrefabControls::~PrefabControls()
{
}

void PrefabControls::propertyChanged()
{
    m_instance->gameObjectChanged();
}

void PrefabControls::enableButtons()
{
    m_applyButton->setEnabled( true );
    m_revertButton->setEnabled( true );
}

void PrefabControls::disableButtons()
{
    m_applyButton->setEnabled( false );
    m_revertButton->setEnabled( false );
}
