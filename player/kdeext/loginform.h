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

class KLineEdit;
class KPushButton;
class QLabel;

class LoginForm : public Overlay
{
        Q_OBJECT

    public:
        explicit LoginForm( QWidget* parent = 0, Qt::WindowFlags wFlags = 0 );

    private:
        QLabel* m_usernameLabel;
        KLineEdit* m_usernameEdit;
        QLabel* m_passwordLabel;
        KLineEdit* m_passwordEdit;
        KPushButton* m_loginButton;
        QLabel* m_usernameFeedbackLabel;
        Attica::ProviderManager m_manager;
        Attica::Provider m_provider;

        void initialize();

    protected slots:
        void doLogin();
        void loginDone();
        void loginFailed();
        void initDone();
        void initFailed();
        void loadCredentials();
};

#endif // LOGINFORM_H
