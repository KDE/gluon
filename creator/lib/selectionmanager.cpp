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

#include "selectionmanager.h"

#include <debughelper.h>

using namespace Gluon::Creator;

class SelectionManager::SelectionManagerPrivate
{
    public:
        SelectionManagerPrivate() { }

        SelectionList selection;
};

template<> GLUONCREATORLIB_EXPORT SelectionManager* KSingleton<SelectionManager>::m_instance = 0;


Gluon::Creator::SelectionManager::SelectionManager()
{
    d = new SelectionManagerPrivate;
}

Gluon::Creator::SelectionManager::~SelectionManager()
{
    delete d;
    d = 0;
}

SelectionManager::SelectionList SelectionManager::selection() const
{
    return d->selection;
}

void SelectionManager::setSelection(const SelectionManager::SelectionList& selection)
{
    d->selection = selection;
    emit selectionChanged(selection);
}
