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

#ifndef PROPERTYCHANGEDCOMMAND_H
#define PROPERTYCHANGEDCOMMAND_H

#include <QtGui/QUndoStack>

class QVariant;

namespace GluonCreator
{
    class PropertyChangedCommand : public QUndoCommand
    {
        public:
            PropertyChangedCommand(QObject* object, QString property, QVariant oldValue, QVariant newValue);

            virtual void undo();
            virtual void redo();

        private:
            class PropertyChangedCommandPrivate;
            PropertyChangedCommandPrivate *d;
    };
}

#endif // PROPERTYCHANGEDCOMMAND_H
