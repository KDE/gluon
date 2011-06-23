/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Kim Jung Nissen <jungnissen@gmail.com>
 * Copyright (C) 2010 Laszlo Papp <lpapp@kde.org>
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

#include "custominput.h"

#include "inputdevice.h"
#include "custominputprivate.h"

#include <QtCore/QDebug>
#include <QtCore/QStringList>

using namespace GluonInput;

CustomInput::CustomInput( QObject* parent )
    : QObject( parent )
    , d( new CustomInputPrivate() )
{
}

CustomInput::~CustomInput()
{
}

void CustomInput::setButton( const QString& name, InputDevice* input, int keyCode )
{
    if( !input->buttonCapabilities().contains( keyCode ) )
    {
        qDebug() << "Cannot find keyCode for this input...";
        return;
    }
    connect( input, SIGNAL( eventSent( InputEvent* ) ), SLOT( inputEvent( InputEvent* ) ) );
    d->m_buttons.insert( name, qMakePair( input, keyCode ) );

}

void CustomInput::setButton( const QString& name )
{
    InputDevice* input = new InputDevice();
    d->m_buttons.insert( name, qMakePair( input, 0 ) );
}

void CustomInput::setAbsAxis( const QString& name, InputDevice* input, int axis )
{
    if( !input->absAxisCapabilities().contains( axis ) )
    {
        qDebug() << "Cannot find keyCode for this input...";
        return;
    }
    d->m_absAxis.insert( name, qMakePair( input, axis ) );
    connect( input, SIGNAL( eventSent( InputEvent* ) ), SLOT( inputEvent( InputEvent* ) ) );
}

void CustomInput::setRelAxis( const QString& name, InputDevice* input, int axis )
{
    if( !input->relAxisCapabilities().contains( axis ) )
    {
        qDebug() << "Cannot find keyCode for this input...";
        return;
    }
    d->m_absAxis.insert( name, qMakePair( input, axis ) );
    connect( input, SIGNAL( eventSent( InputEvent* ) ), SLOT( inputEvent( InputEvent* ) ) );

}

void CustomInput::remButton( const QString& name )
{
    if( d->m_buttons.contains( name ) )
    {
        disconnect( d->m_buttons[name].first, SIGNAL( eventSent( InputEvent* ) ), this, SLOT( inputEvent( InputEvent* ) ) );
        d->m_buttons.remove( name );
    }
}

void CustomInput::remAbsAxis( const QString& name )
{
    if( d->m_absAxis.contains( name ) )
    {
        disconnect( d->m_buttons[name].first, SIGNAL( eventSent( InputEvent* ) ), this,  SLOT( inputEvent( InputEvent* ) ) );
        d->m_absAxis.remove( name );
    }
}

void CustomInput::remRelAxis( const QString& name )
{
    if( d->m_relAxis.contains( name ) )
    {
        disconnect( d->m_buttons[name].first, SIGNAL( eventSent( InputEvent* ) ), this, SLOT( inputEvent( InputEvent* ) ) );
        d->m_relAxis.remove( name );
    }
}

/*void CustomInput::inputEvent(InputEvent * event)
  {

//-------------IF BUTTON------------
if (event->type() ==  QEvent::Type(GluonInput::Key))
{
QMapIterator  <QString, QPair<InputDevice*, int> >  i(d->m_buttons);
while (i.hasNext())
{
i.next();
if ((i.value().second == event->code()) && (i.value().first == qobject_cast<InputDevice*>(sender())))
{
if (event->value() == 1)
emit buttonPressed(i.key());

if (event->value() == 0)
emit buttonReleased(i.key());
}
}
return;
}

//-------------IF ABS AXIS-----------

if (event->type() ==  QEvent::Type(GluonInput::AbsoluAxis))
{
QMapIterator  <QString, QPair<InputDevice*, int> >  i(d->m_absAxis);
while (i.hasNext())
{
i.next();
if ((i.value().second == event->code()) && (i.value().first == qobject_cast<InputDevice*>(sender())))
{
emit absAxisChanged(i.key(), event->value());
}
}
return;
}

//-------------IF REL AXIS------------
if (event->type() ==  QEvent::Type(GluonInput::RelativeAxis))
{
QMapIterator  <QString, QPair<InputDevice*, int> >  i(d->m_relAxis);
while (i.hasNext())
{
i.next();
if ((i.value().second == event->code()) && (i.value().first == qobject_cast<InputDevice*>(sender())))
{
emit relAxisChanged(i.key(), event->value());
}
}
}
return;
}*/


/*bool CustomInput::button(const QString& name)
  {
  if (d->m_buttons.contains(name))
  return d->m_buttons[name].first->button(d->m_buttons[name].second);
  else return false;
  }*/

/*int CustomInput::relAxisValue(const QString &name)
  {
  if (d->m_relAxis.contains(name))
  return d->m_relAxis[name].first->relAxisValue(d->m_relAxis[name].second);
  else return -1;


  }

  int CustomInput::absAxisValue(const QString &name)
  {
  if (d->m_absAxis.contains(name))
  return d->m_absAxis[name].first->absAxisValue(d->m_absAxis[name].second);
  else return -1;
  }*/

/*InputDevice* CustomInput::inputAt(const QString& name, GluonInput::InputTypeFlag type)
  {
  if (type == GluonInput::Key)
  return d->m_buttons[name].first;

  if (type == GluonInput::AbsoluAxis)
  return d->m_absAxis[name].first;

  if (type == GluonInput::RelativeAxis)
  return d->m_relAxis[name].first;

  return NULL;
  }

  int CustomInput::codeAt(const QString& name, GluonInput::InputTypeFlag type)
  {

  if (type == GluonInput::Key)
  return d->m_buttons[name].second;

  if (type == GluonInput::AbsoluAxis)
  return d->m_absAxis[name].second;

  if (type == GluonInput::RelativeAxis)
  return d->m_relAxis[name].second;

  return -1;

  }*/

QStringList CustomInput::buttonNameList()
{
    QStringList list;
    QMapIterator <QString, QPair<InputDevice*, int> >  i( d->m_buttons );
    while( i.hasNext() )
    {
        i.next();
        list << i.key();
    }
    return list;
}

QStringList CustomInput::absAxisNameList()
{
    QStringList list;
    QMapIterator<QString, QPair<InputDevice*, int> >  i( d->m_absAxis );
    while( i.hasNext() )
    {
        i.next();
        list << i.key();
    }
    return list;
}

QStringList CustomInput::relAxisNameList()
{
    QStringList list;
    QMapIterator <QString, QPair<InputDevice*, int> >  i( d->m_relAxis );
    while( i.hasNext() )
    {
        i.next();
        list << i.key();
    }
    return list;
}

#include "custominput.moc"
