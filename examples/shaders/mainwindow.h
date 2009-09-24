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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <KXmlGuiWindow>
#include <gluon/kgl/kglview.h>

class QStackedLayout;
class ShaderWidget;
class MainWindow : public KXmlGuiWindow
{
  Q_OBJECT
  public:
    MainWindow(QWidget* parent = 0);
    ~MainWindow();

  private:
    KGLView* mView;
    KGLEngine* mEngine;

    ShaderWidget* mShaderWidget;
    KGLBoxItem* mItem;
    QStackedLayout* mWidgetStack;
    
    void setupDock();

public slots:
    void shaderChanged(int);
};

#endif // MAINWINDOW_H
