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

#ifndef GLUON_CREATOR_GAMETHREAD_H
#define GLUON_CREATOR_GAMETHREAD_H

#include <QtCore/QThread>


namespace Gluon {

namespace Creator {

class GameThread : public QThread
{
    Q_OBJECT
    public:
        GameThread(QObject* parent = 0);
        ~GameThread();

    protected:
        virtual void run();
};

}

}

#endif // GLUON_CREATOR_GAMETHREAD_H
