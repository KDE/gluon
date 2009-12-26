/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef NEWGLUONMAINWINDOW_H
#define NEWGLUONMAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtCore/QSettings>

class NewGluonMainWindow : public QMainWindow
{
    Q_OBJECT
    public:
        NewGluonMainWindow(QWidget* parent = 0, Qt::WindowFlags flags = 0);
        ~NewGluonMainWindow();

    private:
        QSettings* m_settings;
};

#endif // NEWGLUONMAINWINDOW_H
