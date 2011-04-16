/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Laszlo Papp <djszapi@archlinux.us>
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

#ifndef GLUON_CREATOR_TOOLPLUGIN_H
#define GLUON_CREATOR_TOOLPLUGIN_H

#include "plugin.h"

#include <gluon/core/singleton.h>

#include <QStringList>
#include <QHash>

namespace GluonCreator
{

    class GLUONCREATOR_EXPORT ToolPlugin : public Plugin
    {
            Q_OBJECT
        public:
            ToolPlugin( QObject* parent, const QList<QVariant>& params );
            virtual ~ToolPlugin();

            virtual void load( KXmlGuiWindow* mainWindow );
            virtual void unload( KXmlGuiWindow* mainWindow );

        protected:
            virtual QWidget* createTool( KXmlGuiWindow* parent ) = 0;

        private:
            QWidget* m_tool;

    };

}

#endif // GLUON_CREATOR_TOOLPLUGIN_H
