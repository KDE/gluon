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
#include <player/lib/authentication.h>

#include <attica/provider.h>
#include <Plasma/LineEdit>
#include <Plasma/PushButton>
#include <Plasma/Label>
#include <Plasma/BusyWidget>
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

    m_busyWidget = new Plasma::BusyWidget(this);
    m_busyWidget->hide();
    m_usernameLabel = new Plasma::Label(this);
    m_usernameLabel->setText(i18n("Not Logged In"));

    QGraphicsLinearLayout *layout1 = new QGraphicsLinearLayout(m_contentLayout);
    layout1->addItem(m_busyWidget);
    layout1->addItem(m_usernameLabel);

    m_contentLayout->addItem(layout1);
    m_contentLayout->addItem(m_usernameEdit);
    m_contentLayout->addItem(m_passwordEdit);
    m_contentLayout->addItem(m_loginButton);

    connect(m_loginButton, SIGNAL(clicked()), SLOT(doLogin()));
    connect(GluonPlayer::Authentication::instance(), SIGNAL(loggedIn()), SLOT(loginDone()));
    connect(GluonPlayer::Authentication::instance(), SIGNAL(loginFailed()), SLOT(loginFailed()));
}

void LoginForm::doLogin()
{
    if (m_usernameEdit->text().isEmpty() || m_passwordEdit->text().isEmpty()) {
        return;
    }

    m_loginButton->setEnabled(false);
    m_busyWidget->show();
    m_usernameLabel->setText(i18n("Logging in"));
    GluonPlayer::Authentication::instance()->login(m_usernameEdit->text(), m_passwordEdit->text());
}

void LoginForm::loginDone()
{
    m_busyWidget->hide();
    m_usernameLabel->setText(
        i18nc("Logged in as <user name>", "Logged in as %1", GluonPlayer::Authentication::instance()->username()));
    m_loginButton->setEnabled(true);
}

void LoginForm::loginFailed()
{
    m_busyWidget->hide();
    m_usernameLabel->setText(i18n("Login Failed"));
    m_loginButton->setEnabled(true);
}

#include "loginform.moc"
