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

#include "actionwindow.h"

#include <QtWidgets/QComboBox>

#include <QtCore/QDebug>

#include <input/inputdevice.h>
#include <input/inputmanager.h>
#include <input/inputparameter.h>
#include <input/inputaction.h>

#include "ui_actionwindow.h"

using namespace GluonInput;

class ActionWindow::Private
{
    public:
        Ui::ActionWindow* ui;
        InputAction* action;
};

ActionWindow::ActionWindow( QWidget* parent, Qt::WindowFlags f )
    : QWidget( parent )
{
    d->ui = new Ui::ActionWindow;
    d->ui->setupUi( this );

    InputManager::instance()->setFilterObject( d->ui->focusButton );
    InputManager::instance()->initialize();

    QList< InputDevice* > devices = InputManager::instance()->allDevices();
    for( auto device : devices )
    {
        d->ui->deviceCombo->addItem( device->name(), QVariant::fromValue< InputDevice* >( device ) );
    }

    connect( d->ui->deviceCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(deviceChanged(int)) );
    connect( d->ui->parameterCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(parameterChanged(int)) );

    d->ui->deviceCombo->setCurrentIndex( 0 );

    d->action = new InputAction{ this };

    connect( d->action, &InputAction::valueChanged, this, &ActionWindow::valueChanged );
    connect( d->action, &InputAction::pressed, this, &ActionWindow::pressed );
    connect( d->action, &InputAction::released, this, &ActionWindow::released );
    connect( d->action, &InputAction::triggered, this, &ActionWindow::triggered );
}

ActionWindow::~ActionWindow()
{
    delete d->ui;
}

void ActionWindow::deviceChanged( int index )
{
    InputDevice* device = d->ui->deviceCombo->itemData( index ).value< InputDevice* >();

    d->action->setDevice( device );

    d->ui->parameterCombo->clear();
    auto parameters = device->parameters();
    for( auto parameter : parameters )
    {
        d->ui->parameterCombo->addItem( parameter->name(), QVariant::fromValue< InputParameter* >( parameter ) );
    }

    d->ui->parameterCombo->setCurrentIndex( 0 );
}

void ActionWindow::parameterChanged( int index )
{
    InputParameter* parameter = d->ui->parameterCombo->itemData( index ).value< InputParameter* >();
    d->action->setParameter( parameter );
}

void ActionWindow::valueChanged()
{
    d->ui->valueLabel->setText( QString( "Value: %1" ).arg( d->action->value() ) );
}

void ActionWindow::pressed()
{
    d->ui->stateLabel->setText( "State: Pressed" );
}

void ActionWindow::released()
{
    d->ui->stateLabel->setText( "State: Released" );
}

void ActionWindow::triggered()
{
    d->ui->stateLabel->setText( "State: Triggered" );
}
