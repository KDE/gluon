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

#include "loginform.h"

#include <attica/provider.h>
#include <Plasma/LineEdit>
#include <Plasma/PushButton>
#include <KLineEdit>
#include <KLocalizedString>     //FIXME: Why is this required?

#include <QGraphicsLinearLayout>
#include <QDebug>

LoginForm::LoginForm(QGraphicsItem* parent, Qt::WindowFlags wFlags) : Overlay(parent, wFlags)
{
    m_usernameEdit = new Plasma::LineEdit(this);
    m_usernameEdit->nativeWidget()->setClickMessage(i18n("Username"));
    m_passwordEdit = new Plasma::LineEdit(this);
    m_passwordEdit->nativeWidget()->setClickMessage(i18n("Password"));
    m_passwordEdit->nativeWidget()->setPasswordMode(true);
    m_loginButton = new Plasma::PushButton(this);
    m_loginButton->setIcon(KIcon("network-connect"));
    m_loginButton->setText(i18n("Login"));

    m_contentLayout->addItem(m_usernameEdit);
    m_contentLayout->addItem(m_passwordEdit);
    m_contentLayout->addItem(m_loginButton);

    connect(m_loginButton, SIGNAL(clicked()), SLOT(doLogin()));
    connect(&m_manager, SIGNAL(defaultProvidersLoaded()), SLOT(processProviders()));
    m_manager.loadDefaultProviders();

    emit isBusy();
}

void LoginForm::doLogin()
{
    if (m_usernameEdit->text().isEmpty() || m_passwordEdit->text().isEmpty()) {
        return;
    }
}

void LoginForm::processProviders()
{
    if (!m_manager.providers().isEmpty()) {
        m_provider = m_manager.providerByUrl(QUrl("https://api.opendesktop.org/v1/"));
        if (!m_provider.isValid()) {
            qDebug() << "Could not find opendesktop.org provider.";
            return;
        }

        m_provider.saveCredentials(m_usernameEdit->text(), m_passwordEdit->text());
        qDebug() << "Done";
    } else {
        qDebug() << "No providers found.";
    }
}

#include "loginform.moc"
