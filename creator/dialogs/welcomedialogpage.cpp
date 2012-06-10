/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (C) 2010 Keith Rusler <xzekecomax@gmail.com>
 * Copyright (C) 2010 Laszlo Papp <lpapp@kde.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include "welcomedialogpage.h"

#include <core/gluon_global.h>
#include <engine/gameproject.h>
#include <engine/scene.h>
#include <engine/game.h>
#include <engine/gameobject.h>
#include <engine/component.h>

#include <KDE/KLocalizedString>
#include <KDE/KIcon>
#include <KDE/KLineEdit>
#include <KDE/KUrlRequester>
#include <KDE/KMessageBox>
#include <KDE/KSqueezedTextLabel>

#include <QtGui/QGroupBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QFormLayout>
#include <QtGui/QLabel>
//#include <QtGui/QLabel>
#include <QtCore/QScopedPointer>

class QLabel;

using namespace GluonCreator;

class WelcomeDialogPage::WelcomeDialogPagePrivate
{
    public:
        WelcomeDialogPagePrivate( WelcomeDialogPage* qq )
            : textView(0)
        {
        }

    public:
        QLabel *textView ;

    private:
        WelcomeDialogPage* q;
};

WelcomeDialogPage::WelcomeDialogPage()
    : KPageWidgetItem( new QWidget, i18n( "Welcome Dialog" ) ),
      d( new WelcomeDialogPagePrivate( this ) )
{

    QVBoxLayout* layout = new QVBoxLayout( widget() );
    QGroupBox* box = new QGroupBox(widget() );

    widget()->setLayout( layout );
    layout->addWidget( box );

    QFormLayout* boxLayout = new QFormLayout( box );
    box->setLayout( boxLayout );

    d->textView = new QLabel( box );
    d->textView->setWordWrap (true);
    d->textView->setText( i18n( "Gluon Creator is a tool that allows designers and artists to easily prototype and create games.With some minimal configuration , it allows for a multitude of games to be created. And what's more, we are free and open source!So here's what more you can do with creator" ) );
    boxLayout->addRow(d->textView );

}

WelcomeDialogPage::~WelcomeDialogPage()
{
    delete d;
}

