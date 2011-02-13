/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (c) 2010 Laszlo Papp <djszapi@archlinux.us>
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
#ifndef GLUON_CREATOR_CONFIGDIALOG_H
#define GLUON_CREATOR_CONFIGDIALOG_H

#include <KDE/KConfigDialog>

class KPluginSelector;

namespace GluonCreator
{

    class ConfigDialog : public KConfigDialog
    {
        public:
            ConfigDialog( QWidget* parent, const QString& name, KConfigSkeleton* config );
            ~ConfigDialog();

            virtual void accept();

        private:
            KPluginSelector* m_plugins;
    };

}

#endif // GLUON_CREATOR_CONFIGDIALOG_H
