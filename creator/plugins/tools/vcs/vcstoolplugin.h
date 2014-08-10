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

#ifndef GLUON_CREATOR_VCSTOOLPLUGIN_H
#define GLUON_CREATOR_VCSTOOLPLUGIN_H

#include <creator/lib/toolplugin.h>

namespace GluonCreator
{

    class VcsToolPlugin : public ToolPlugin
    {
            Q_OBJECT
            GLUON_TOOL_PLUGIN( metadata.json )
        public:
            VcsToolPlugin( QObject* parent=0, const QList<QVariant>& params=QList<QVariant>() );
            ~VcsToolPlugin();

            void initialize() {}

        protected:
            QWidget* createTool( KXmlGuiWindow* parent );
    };

}

#endif // GLUON_CREATOR_MESSAGEDOCKPLUGIN_H
