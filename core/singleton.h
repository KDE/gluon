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

#ifndef GLUON_CORE_SINGLETON
#define GLUON_CORE_SINGLETON

#include <QtCore/QObject>

namespace GluonCore
{
    template <typename T>
    class Singleton : public QObject
    {
    public:
        static T* instance()
        {
            if(!m_instance) {
                m_instance = new T;
            }
            return m_instance;
        }

    protected:
        static T* m_instance;
    };
}

#endif //GLUON_CORE_SINGLETON
