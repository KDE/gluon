/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright 2011 Shantanu Tushar <shaan7in@gmail.com>
 * Copyright 2011 Sebastian Kügler <sebas@kde.org>
 * Copyright 2011 Marco Martin <mart@kde.org>
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

#ifndef VIEW_H
#define VIEW_H

#include <QDeclarativeView>
#include <QAction>

#include <KActionCollection>
#include <KMainWindow>
#include <KPluginInfo>

class KMainWindow;
class QDeclarativeItem;
class QProgressBar;
class QSignalMapper;
class Page;
class ScriptApi;
class DirModel;
;
namespace Plasma
{
class Package;
}

class AppView : public QDeclarativeView
{
    Q_OBJECT

public:
    AppView( QWidget *parent = 0 );
    ~AppView();

    QString name() const;

    void setUseGL(const bool on);
    bool useGL() const;

private Q_SLOTS:
    void onStatusChanged(QDeclarativeView::Status status);

private:
    Plasma::Package *m_package;
    bool m_useGL;
};

#endif // VIEW_H
