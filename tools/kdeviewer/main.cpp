/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Laszlo Papp <lpapp@kde.org>
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

#include <engine/game.h>
#include <engine/gameproject.h>
#include <graphics/renderwidget.h>

#include <input/inputmanager.h>

#include <QtGui/QApplication>

#include <QtCore/QFileInfo>
#include <QtCore/QDebug>
#include <QtCore/QString>
#include <QtCore/QTimer>

class Player : public QObject
{
    Q_OBJECT

    public:
        explicit Player(const QString &fileName, QObject *parent = 0) : QObject(parent), m_fileName(fileName) {}
        ~Player() { delete m_renderWidget; }

    public slots:
        void openProject() {
            m_renderWidget = new GluonGraphics::RenderWidget( );
            m_renderWidget->installEventFilter(this);
            m_renderWidget->setFocus();

            connect( GluonEngine::Game::instance(), SIGNAL(painted(int)), m_renderWidget, SLOT(updateGL()) );

            GluonInput::InputManager::instance()->setFilteredObject( m_renderWidget );
            QTimer::singleShot(100, this, SLOT(startGame()));
        }

        void startGame() {
            GluonCore::GluonObjectFactory::instance()->loadPlugins();

            m_gameProject = new GluonEngine::GameProject();
            m_gameProject->loadFromFile( m_fileName );

            GluonEngine::Game::instance()->setGameProject( m_gameProject );
            GluonEngine::Game::instance()->setCurrentScene( m_gameProject->entryPoint() );

            m_renderWidget->show();
            GluonEngine::Game::instance()->runGame();
            QApplication::instance()->exit();
        }

        bool eventFilter(QObject *obj, QEvent *event) {
            if (obj == m_renderWidget) {
                if (event->type() == QEvent::Close) {
                    GluonEngine::Game::instance()->stopGame();
                    QApplication::instance()->quit();
                    return true;
                }
            } else {
                QObject::eventFilter(obj, event);
            }
            return false;
        }

    private:
        QString m_fileName;
        GluonEngine::GameProject* m_gameProject;
        GluonGraphics::RenderWidget* m_renderWidget;
};

#include "main.moc"

int main( int argc, char** argv )
{
    if( argc > 1 )
    {
        if (!QFile::exists( argv[1] )) {
            qDebug() << "File does not exist:" << argv[1];
            return 1;
        }

        QApplication app( argc, argv );

        QFileInfo fi = QFileInfo( argv[1] );
        QString fileName;
        if( fi.isRelative() )
            fileName = fi.canonicalFilePath();
        else
            fileName = argv[1];

        Player player(fileName);
        QTimer::singleShot(0, &player, SLOT(openProject()));

        return app.exec();
    }
    else
    {
        qDebug() << "Usage:" << argv[0] << "<gameproject>";
    }
}
