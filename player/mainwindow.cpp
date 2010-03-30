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

#include "mainwindow.h"
#include <QFileDialog>
#include <QLabel>
#include <QTimer>
#include <engine/game.h>
#include <engine/gameproject.h>
#include <graphics/glwidget.h>
#include <engine/scene.h>
#include <fpscounter.h>
#include <QStatusBar>
#include <QApplication>

using namespace GluonPlayer;

class MainWindow::MainWindowPrivate
{
    public:
        QString fileName;

        GluonEngine::GameProject *project;

        GluonGraphics::GLWidget *widget;

        QLabel *label;
        QString title;
};

GluonPlayer::MainWindow::MainWindow(int argc, char** argv, QWidget* parent, Qt::WindowFlags flags)
        : QMainWindow(parent, flags)
{
    d = new MainWindowPrivate;

    if (argc > 1)
    {
        d->fileName = argv[1];
    }

    d->label = new QLabel(tr("Please select a project"));
    d->label->setAlignment(Qt::AlignCenter);
    setCentralWidget(d->label);

    QTimer* timer = new QTimer(this);
    timer->setSingleShot(true);
    timer->setInterval(10);

    connect(timer, SIGNAL(timeout()), SLOT(openProject()));
    timer->start();
}

void MainWindow::openProject()
{
    if (d->fileName.isEmpty())
    {
        d->fileName = QFileDialog::getOpenFileName(this, tr("Please select a project"), QString(), tr("Gluon Project Files (*.gluon)"));
    }

    GluonCore::GluonObjectFactory::instance()->loadPlugins();

    d->label->setText(tr("Loading..."));
    d->project = new GluonEngine::GameProject();
    d->project->loadFromFile(QUrl(d->fileName));

    setWindowFilePath(d->fileName);
    d->title = windowTitle();

    GluonEngine::Game::instance()->setGameProject(d->project);
    GluonEngine::Game::instance()->setCurrentScene(d->project->entryPoint());

    d->widget = new GluonGraphics::GLWidget(this);
    setCentralWidget(d->widget);
    connect(GluonEngine::Game::instance(), SIGNAL(painted()), d->widget, SLOT(updateGL()));
    connect(GluonEngine::Game::instance(), SIGNAL(painted()), SLOT(updateTitle()));

    GluonEngine::Game::instance()->runGame();
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    GluonEngine::Game::instance()->stopGame();
    QWidget::closeEvent(event);
}

void MainWindow::updateTitle()
{
    QString fps = d->widget->fpsCounter()->fpsString();

    setWindowTitle(d->title + QString(" (%1 FPS)").arg(fps));
}

#include "mainwindow.moc"
