/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010-2013 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#include "gettingstarteddialogpage.h"

#include <KDE/KLocalizedString>
#include <KDE/KIcon>

#include <QtGui/QFormLayout>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

class QLabel;

using namespace GluonCreator;

class GettingStartedDialogPage::Private
{
    public:
        Private() : textView(0)
        {
        }

        QLabel *textView ;
        QPushButton *button;
};

GettingStartedDialogPage::GettingStartedDialogPage()
    : KPageWidgetItem( new QWidget, i18n( "Getting Started" ) ), d( new Private )
{
    setIcon( KIcon( "help-hint" ) );

    QWidget* w = widget();

    QFormLayout* boxLayout = new QFormLayout( w );
    w->setLayout( boxLayout );

    d->textView = new QLabel( w );
    d->textView->setWordWrap (true);
    d->textView->setText( i18n( "Gluon Creator is a tool that allows designers and artists to easily prototype and create games.With some minimal configuration , it allows for a multitude of games to be created. And what's more, we are free and open source! Follow this quick tour to learn the main elements of the Gluon Creator UI." ) );
    boxLayout->addRow(d->textView );

    d->button = new QPushButton( w );
    d->button->setText( i18n( "Start Tour") );
    connect(d->button, SIGNAL(clicked(bool)), SIGNAL(startTour()) );
    boxLayout->addRow(d->button);
}

GettingStartedDialogPage::~GettingStartedDialogPage()
{
    delete d;
}

