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

#include <KCoreAddons/KAboutData>
#include <KI18n/KLocalizedString>

#include <gluon_global.h>

namespace GluonCreator
{
    KAboutData aboutData()
    {
        KAboutData data(
            QString("gluoncreator"),
            i18n( "Gluon Creator" ),
            QString( "%1 (%2)" ).arg( GLUON_VERSION_STRING ).arg( GLUON_VERSION_NAME ).toUtf8(),
            i18n( "A game creation environment" ),
            KAboutLicense::LGPL_V2,
            i18n( "Copyright 2009-2014 by the Gluon Team." ),
            QString(),
            QString("http://gluon.gamingfreedom.org")
        );

        data.addAuthor( i18n( "Arjen Hiemstra" ), i18n( "Gluon Core, Gluon Graphics, Gluon Engine, Gluon Creator" ), "ahiemstra@heimr.nl", QByteArray(), "ahiemstra" );
        data.addAuthor( i18n( "Dan Leinir Tuthra Jensen" ), i18n( "Gluon Core, Gluon Engine, Gluon Creator, SMARTS" ), "admin@leinir.dk", "" );
        data.addAuthor( i18n( "Sacha Schutz" ), i18n( "Gluon Graphics, Gluon Audio, Gluon Input" ), "istdasklar@free.fr" );
        data.addAuthor( i18n( "Guillaume Martres" ), i18n( "Gluon Audio, Gluon Graphics" ), "smarter@ubuntu.com" );
        data.addAuthor( i18n( "Shantanu Tushar Jha" ), i18n( "Gluon Player, Gluon Creator" ), "shaan7@gmail.com" );
        data.addAuthor( i18n( "Kim Jung Nissen" ), i18n( "Gluon Input, Mac Compatibility" ), "jungnissen@gmail.com" );
        data.addAuthor( i18n( "Laszlo Papp" ), i18n( "Gluon Creator, Input, Player, Mobile support" ), "lpapp@kde.org" );

        return data;
    }
};

#endif //GLUONCREATOR_ABOUTDATA_H
