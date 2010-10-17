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

#include "newcommentform.h"

#include <attica/provider.h>
#include <KTextEdit>
#include <KLineEdit>
#include <Plasma/PushButton>
#include <Plasma/LineEdit>
#include <Plasma/TextEdit>
#include <KDebug>

#include <QGraphicsLinearLayout>

NewCommentForm::NewCommentForm(QGraphicsItem* parent, Qt::WindowFlags wFlags): QGraphicsWidget(parent, wFlags)
{
    QGraphicsLinearLayout *layout = new QGraphicsLinearLayout(Qt::Vertical, this);
    QGraphicsLinearLayout *layout2 = new QGraphicsLinearLayout(Qt::Horizontal, layout);
    layout2->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    m_titleEdit = new Plasma::LineEdit(this);
    m_titleEdit->nativeWidget()->setClickMessage(i18n("Subject"));

    m_bodyEdit = new Plasma::TextEdit(this);
    m_bodyEdit->nativeWidget()->setClickMessage(i18n("Message"));

    m_okButton = new Plasma::PushButton(this);
    m_okButton->setText(i18n("OK"));
    connect(m_okButton, SIGNAL(clicked()), this, SLOT(validateAndSubmit()));

    m_cancelButton = new Plasma::PushButton(this);
    m_cancelButton->setText(i18n("Cancel"));
    connect(m_cancelButton, SIGNAL(clicked()), SIGNAL(canceled()));

    layout->addItem(m_titleEdit);
    layout->addItem(m_bodyEdit);
    layout2->addItem(m_cancelButton);
    layout2->addItem(m_okButton);
    layout->addItem(layout2);

    setLayout(layout);
}

NewCommentForm::~NewCommentForm()
{

}

void NewCommentForm::setParentIndex(QModelIndex parentIndex)
{
    m_parentIndex = parentIndex;
}

void NewCommentForm::validateAndSubmit()
{
    if (m_titleEdit->text().isEmpty() || m_bodyEdit->text().isEmpty()) {
	return;
    }
    emit accepted(m_parentIndex, m_titleEdit->text(), m_bodyEdit->nativeWidget()->toPlainText());
}

#include "newcommentform.moc"
