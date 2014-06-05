/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (c) 2011 Dan Leinir Turthra Jensen <admin@leinir.dk>
 * Copyright (c) 2011 Sacha Schutz <istdasklar@free.fr>
 * Copyright (c) 2011 Guillaume Martres <smarter@ubuntu.com>
 * Copyright (c) 2011 Shantanu Tushar Jha <shaan7in@gmail.com>
 * Copyright (c) 2011 Kim Jung Nissen <jungnissen@gmail.com>
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

#ifndef GLUONCREATOR_ABOUTDATA_H
#define GLUONCREATOR_ABOUTDATA_H

#include <KDE/KAboutData>
#include <KDE/KLocalizedString>

#include <gluon_global.h>

namespace GluonCreator
{
    KAboutData aboutData()
    {
        KAboutData data(
            "gluoncreator",
            0,
            ki18n( "Gluon Creator" ),
            QString( "%1 (%2)" ).arg( GLUON_VERSION_STRING ).arg( GLUON_VERSION_NAME ).toUtf8(),
            ki18n( "A game creation environment" ),
            KAboutData::License_LGPL_V2,
            ki18n( "Copyright 2009-2011 by the Gluon Team." ),
            KLocalizedString(),
            "http://gluon.gamingfreedom.org"
        );

        data.addAuthor( ki18n( "Arjen Hiemstra" ), ki18n( "Gluon Core, Gluon Graphics, Gluon Engine, Gluon Creator" ), "ahiemstra@heimr.nl", QByteArray(), "ahiemstra" );
        data.addAuthor( ki18n( "Dan Leinir Tuthra Jensen" ), ki18n( "Gluon Core, Gluon Engine, Gluon Creator, SMARTS" ), "admin@leinir.dk", "" );
        data.addAuthor( ki18n( "Sacha Schutz" ), ki18n( "Gluon Graphics, Gluon Audio, Gluon Input" ), "istdasklar@free.fr" );
        data.addAuthor( ki18n( "Guillaume Martres" ), ki18n( "Gluon Audio, Gluon Graphics" ), "smarter@ubuntu.com" );
        data.addAuthor( ki18n( "Shantanu Tushar Jha" ), ki18n( "Gluon Player, Gluon Creator" ), "shaan7@gmail.com" );
        data.addAuthor( ki18n( "Kim Jung Nissen" ), ki18n( "Gluon Input, Mac Compatibility" ), "jungnissen@gmail.com" );
        data.addAuthor( ki18n( "Laszlo Papp" ), ki18n( "Gluon Creator, Input, Player, Mobile support" ), "lpapp@kde.org" );

        return data;
    }
};

#endif //GLUONCREATOR_ABOUTDATA_H