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

#ifndef LOGINFORM_H
#define LOGINFORM_H

#include "overlay.h"
#include <attica/providermanager.h>
#include <attica/provider.h>

namespace Plasma
{
    class LineEdit;
    class PushButton;
    class Label;
    class BusyWidget;
}

class LoginForm : public Overlay
{
    Q_OBJECT

    public:
        LoginForm(QGraphicsItem* parent = 0, Qt::WindowFlags wFlags = 0);

    private:
        Plasma::LineEdit *m_usernameEdit;
        Plasma::LineEdit *m_passwordEdit;
        Plasma::PushButton *m_loginButton;
        Plasma::BusyWidget *m_busyWidget;
        Plasma::Label *m_usernameLabel;
        Attica::ProviderManager m_manager;
        Attica::Provider m_provider;

    protected slots:
        void doLogin();
        void loginDone();
        void loginFailed();
};

#endif // LOGINFORM_H
