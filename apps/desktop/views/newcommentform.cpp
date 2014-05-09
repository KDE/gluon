/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Laszlo Papp <lpapp@kde.org>
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

#include "newcommentform.h"

#include <attica/provider.h>

NewCommentForm::NewCommentForm( QWidget* parent, Qt::WindowFlags wFlags )
    : QWidget( parent, wFlags )
    , m_titleEdit( new KLineEdit( this ) )
    , m_bodyEdit( new KTextEdit( this ) )
    , m_okButton( new KPushButton( this ) )
    , m_cancelButton( new KPushButton( this ) )
{
    QGridLayout* layout = new QGridLayout( this );

    m_okButton->setText( i18n( "OK" ) );
    connect( m_okButton, SIGNAL(clicked()), SLOT(validateAndSubmit()) );

    m_cancelButton->setText( i18n( "Cancel" ) );
    connect( m_cancelButton, SIGNAL(clicked()), SIGNAL(canceled()) );

    layout->addWidget( m_okButton );
    layout->addWidget( m_cancelButton );
    layout->addWidget( m_titleEdit );
    layout->addWidget( m_bodyEdit );

    setLayout( layout );
}

NewCommentForm::~NewCommentForm()
{
}

void NewCommentForm::setParentIndex( QModelIndex parentIndex )
{
    m_parentIndex = parentIndex;
}

void NewCommentForm::validateAndSubmit()
{
    if( m_titleEdit->text().isEmpty() )
    {
        kDebug() << "Empty title";
    }
    if( m_bodyEdit->toPlainText().isEmpty() )
    {
        kDebug() << "Empty body";
        return;
    }
    emit accepted( m_parentIndex, m_titleEdit->text(), m_bodyEdit->toPlainText() );
}

QString NewCommentForm::titleText() const
{
    return m_titleEdit->text();
}

void NewCommentForm::setTitleText( const QString& titleText )
{
    m_titleEdit->setText( titleText );
}

QString NewCommentForm::bodyText() const
{
    return m_bodyEdit->toPlainText();
}

void NewCommentForm::setBodyText( const QString& bodyText )
{
    m_bodyEdit->setPlainText( bodyText );
}
