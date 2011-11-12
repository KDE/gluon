/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#ifndef GLUONCREATOR_PROJECTINSPECTORPLUGIN_H
#define GLUONCREATOR_PROJECTINSPECTORPLUGIN_H

#include <creator/lib/toolplugin.h>

namespace GluonCreator
{

    class ProjectInspectorPlugin : public GluonCreator::ToolPlugin
    {
        Q_OBJECT
        public:
            ProjectInspectorPlugin( QObject* parent, const QList<QVariant>& params );
            ~ProjectInspectorPlugin();

        public Q_SLOTS:
            void showWindow();

        protected:
            void initialize();

        private:
            class Private;
            const QScopedPointer< Private > d;
    };
}

#endif // GLUON_CREATOR_PROJECTINSPECTORPLUGIN_H
