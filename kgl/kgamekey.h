/*
 * This file is part of the KGLEngine2D project.
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2008 Olivier Gueudelot <gueudelotolive@gmail.com>
 * Copyright (C) 2008 Charles Huet <packadal@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef KGAMEKEY_H
#define KGAMEKEY_H

#include <set>

#include <QtGui/QKeyEvent>

/**
 * @class KGameKey kgamekey.h <KGameKey>
 * This class provides a simple interface to know which keys are pressed, and if a key is pressed or not.
 * it maintains the list of currently pressed keys in a QSet (which assures unicity of inserted items)
 **/
class KGameKey
{
public:
    KGameKey();

    void pressEvent(const QKeyEvent *event);
    void releaseEvent(const QKeyEvent *event);

    inline bool keyPressed(int id) const {
        return (m_keys.find(id) != m_keys.end());
    }
    inline bool isActive() const {
        return m_keys.size() > 0;
    }

private:
    int m_nbKey;
    std::set<int> m_keys;
};

#endif //KGAMEKEY_H
