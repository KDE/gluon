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

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>

#include <input/inputmanager.h>
#include <input/inputdevice.h>
#include <input/inputparameter.h>

using namespace GluonInput;

int main( int argc, char** argv )
{
    QApplication app( argc, argv );

    InputManager::instance()->initialize();

    InputDevice* mouse = InputManager::instance()->device( "qt_mouse" );

    if( !mouse )
        qFatal( "No mouse found!" );

    InputParameter* button = mouse->parameter( "LeftButton" );
    InputParameter* xAxis = mouse->parameter( "X Axis" );
    InputParameter* yAxis = mouse->parameter( "Y Axis" );
    InputParameter* wheelVertical = mouse->parameter( "Wheel Vertical" );
    InputParameter* wheelHorizontal = mouse->parameter( "Wheel Horizontal" );

    Q_ASSERT( button );
    Q_ASSERT( xAxis );
    Q_ASSERT( yAxis );
    Q_ASSERT( wheelVertical );
    Q_ASSERT( wheelHorizontal );

    auto win = new QWidget{};
    auto layout = new QVBoxLayout{ win };
    win->setLayout( layout );

    auto x = new QLabel{ win };
    layout->addWidget( x );
    auto y = new QLabel{ win };
    layout->addWidget( y );
    auto wx = new QLabel{ win };
    layout->addWidget( wx );
    auto wy = new QLabel{ win };
    layout->addWidget( wy );
    auto b = new QLabel{ win };
    layout->addWidget( b );

    QObject::connect( button, &InputParameter::buttonStateChanged, [&]() {
        b->setText( button->buttonState() == InputParameter::ButtonPressed ? "Button Pressed": "Button Released" );
    } );
    QObject::connect( xAxis, &InputParameter::axisValueChanged, [&]() {
        x->setText( QString( "X Axis: %1" ).arg( xAxis->axisValue() ) );
    } );
    QObject::connect( yAxis, &InputParameter::axisValueChanged, [&]() {
        y->setText( QString( "Y Axis: %1" ).arg( yAxis->axisValue() ) );
    } );
    QObject::connect( wheelVertical, &InputParameter::axisValueChanged, [&]() {
        if( wheelVertical->axisValue() != 0.f )
            wx->setText( QString( "Wheel Vertical: %1" ).arg( wheelVertical->axisValue() ) );
    } );
    QObject::connect( wheelHorizontal, &InputParameter::axisValueChanged, [&]() {
        if( wheelHorizontal->axisValue() != 0.f )
            wy->setText( QString( "Wheel Horizontal: %1" ).arg( wheelHorizontal->axisValue() ) );
    } );

    win->setGeometry( 0, 0, 640, 480 );
    win->show();
    app.exec();

    delete win;
}
