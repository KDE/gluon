/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Dan Leinir Turthra Jensen <admin@leinir.dk>
 * Copyright (C) 2011 Felix Rohrbach <fxrh@gmx.de>
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

#ifndef GLUON_CREATOR_PREFABCONTROLS_H
#define GLUON_CREATOR_PREFABCONTROLS_H

#include <QtWidgets/QWidget>

namespace GluonEngine
{
    class AbstractPrefabInstance;
}

class QHBoxLayout;
class QPushButton;

namespace GluonCreator
{
    class PrefabControls : public QWidget
    {
            Q_OBJECT
        public:
            explicit PrefabControls( GluonEngine::AbstractPrefabInstance* instance, QWidget* parent = 0, Qt::WindowFlags f = 0 );
            virtual ~PrefabControls();

        private Q_SLOTS:
            void propertyChanged();
            void enableButtons();
            void disableButtons();

        private:
            GluonEngine::AbstractPrefabInstance* m_instance;
            QHBoxLayout* m_layout;
            QPushButton* m_revertButton;
            QPushButton* m_applyButton;
    };
}

#endif // GLUON_CREATOR_PREFABCONTROLS_H
