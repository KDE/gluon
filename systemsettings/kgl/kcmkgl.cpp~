/*
 * kcmmisc.cpp
 *
 * Copyright (c) 1997 Patrick Dowler dowler@morgul.fsh.uvic.ca
 *
 * Layout management, cleanups:
 * Copyright (c) 1999 Dirk A. Mueller <dmuell@gmx.net>
 *
 * Requires the Qt widget libraries, available at no cost at
 * http://www.troll.no/
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <QWhatsThis>
#include <klocale.h>
#include <kconfig.h>
#include <knuminput.h>
#include <kapplication.h>
#include <kglobal.h>
#include <kstandarddirs.h>
#include <KAboutData>
#include <kprocess.h>
#include <kdialog.h>
#include <KPluginFactory>
#include <KPluginLoader>

#include <QLabel>
#include <QVBoxLayout>
#include "kcmkgl.h"
// #include "kal/kalinfowidget.h"

K_PLUGIN_FACTORY(KGLConfigFactory,
        registerPlugin<KGLConfig>();
        )
K_EXPORT_PLUGIN(KGLConfigFactory("kcmkgl"))

KGLConfig::KGLConfig(QWidget *parent, const QVariantList &)
	: KCModule(KGLConfigFactory::componentData(), parent)
{

 KAboutData *about = new KAboutData(
     "kgl", 0, ki18n( "..." ),
     "0.1", KLocalizedString(), KAboutData::License_GPL,
     ki18n( "Copyright 2009" ) );
 
   setAboutData( about );

 
   

}




#include "kcmkgl.moc"

