/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Laszlo Papp <djszapi@archlinux.us>
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

#ifndef LOGINFORM_H
#define LOGINFORM_H

#include "overlay.h"

#include <attica/providermanager.h>
#include <attica/provider.h>

#include <KDE/KLineEdit>
#include <KDE/KPushButton>
#include <KDE/KProgressDialog>

#include <QtGui/QLabel>
#include <QtGui/QCheckBox>

class LoginForm : public Overlay
{
        Q_OBJECT

    public:
        explicit LoginForm( QWidget* parent = 0, Qt::WindowFlags wFlags = 0 );

    protected slots:
        void doLogin();
        void doLogout();
        void loginDone();
        void logoutDone();
        void loginFailed();
        void initDone();
        void initFailed();
        void loadCredentials();

    private:
        void initialize();

        KLineEdit* m_usernameEdit;
        KLineEdit* m_passwordEdit;
        KPushButton* m_loginButton;

        QLabel* m_usernameLabel;
        QLabel* m_passwordLabel;
        QLabel* m_usernameFeedbackLabel;
        QCheckBox* m_rememberMeCheckBox;
        KProgressDialog* m_progressDialog;

        bool m_loggedIn;

        Attica::ProviderManager m_manager;
        Attica::Provider m_provider;
};

#endif // LOGINFORM_H
