/***************************************************************************
 *   Copyright 2003-2009 Alexander Dymo <adymo@kdevelop.org>               *
 *   Copyright 2007 Ralf Habacker  <Ralf.Habacker@freenet.de>              *
 *   Copyright 2006-2007 Matt Rogers  <mattr@kde.org>                      *
 *   Copyright 2006-2007 Hamish Rodda <rodda@kde.org>                      *
 *   Copyright 2005-2007 Adam Treat <treat@kde.org>                        *
 *   Copyright 2003-2007 Jens Dagerbo <jens.dagerbo@swipnet.se>            *
 *   Copyright 2001-2002 Bernd Gehrmann <bernd@mail.berlios.de>            *
 *   Copyright 2001-2002 Matthias Hoelzer-Kluepfel <hoelzer@kde.org>       *
 *   Copyright 2003 Roberto Raggi <roberto@kdevelop.org>                   *
 *   Copyright 2010 Niko Sams <niko.sams@gmail.com>                        *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Library General Public License as       *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.         *
 ***************************************************************************/

#include "kdevideextension.h"

#include "dialogs/projectselectiondialog.h"

#include "lib/plugin.h"
#include "lib/pluginmanager.h"
#include "lib/objectmanager.h"
#include "lib/historymanager.h"
#include "lib/selectionmanager.h"
#include "lib/dockmanager.h"
#include "lib/filemanager.h"
#include "lib/widgets/filearea.h"

#include "gluoncreatorsettings.h"
#include "dialogs/configdialog.h"

#include <engine/game.h>
#include <engine/gameproject.h>
#include <engine/scene.h>
#include <core/gluon_global.h>

#include <config.h>

#include <shell/core.h>
#include <shell/mainwindow.h>
#include <shell/projectcontroller.h>
#include <shell/documentcontroller.h>
#include <shell/plugincontroller.h>
#include <shell/sessioncontroller.h>
#include <shell/runcontroller.h>
#include <shell/launchconfiguration.h>
#include <shell/session.h>

#include <interfaces/ilauncher.h>
#include <interfaces/iproject.h>

#include <KDE/KAboutData>
#include <KDE/KApplication>
#include <KDE/KCmdLineArgs>
#include <KDE/KLocalizedString>
#include <KDE/KXmlGuiWindow>
#include <KDE/KStandardDirs>
#include <KDE/KSplashScreen>
#include <KDE/KMessageBox>
#include <ktexteditor/cursor.h>

#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusInterface>
#include <QtDBus/QDBusReply>
#include <QtGui/QPixmap>
#include <QtCore/QFileInfo>
#include <QtCore/QDir>

using KDevelop::Core;

int main( int argc, char *argv[] )
{
    KAboutData aboutData( "gluoncreator", NULL,
            ki18n( "Gluon Creator" ), QString( "%1 (%2)" ).arg( GLUON_VERSION_STRING ).arg( GLUON_VERSION_NAME ).toUtf8(),
            ki18n( "A game creation environment" ),
            KAboutData::License_LGPL_V2,
            ki18n( "Copyright 2009-2010 by multiple contributors." ),
            KLocalizedString(),
            "http://gluon.gamingfreedom.org"
            );

    aboutData.setProgramIconName( "gluon_creator" );
    aboutData.addAuthor( ki18n( "Arjen Hiemstra" ), ki18n( "Gluon Core, Gluon Graphics, Gluon Engine, Gluon Creator" ), "" );
    aboutData.addAuthor( ki18n( "Dan Leinir Tuthra Jensen" ), ki18n( "Gluon Core, Gluon Engine, Gluon Creator" ), "" );
    aboutData.addAuthor( ki18n( "Sacha Schutz" ), ki18n( "Gluon Graphics,Gluon Audio,Gluon Input" ), "" );
    aboutData.addAuthor( ki18n( "Guillaume Martres" ), ki18n( "Gluon Audio, Gluon Graphics" ), "" );
    aboutData.addAuthor( ki18n( "Kim Jung Nissen" ), ki18n( "Gluon Input, Mac compatibility" ), "" );
    aboutData.addAuthor( ki18n( "Rivo Laks" ), ki18n( "Gluon Graphics through KGLLIB" ), "" );
    aboutData.addAuthor( ki18n( "Laszlo Papp" ), ki18n( "Gluon Creator, Input, Player, Mobile support" ), "" );
    aboutData.setProductName( "gluon/gluoncreator" );


    KCmdLineArgs::init( argc, argv, &aboutData );
    KCmdLineOptions options;
    options.add( "+file", ki18n( "GDL file to open" ) );
    KCmdLineArgs::addCmdLineOptions( options );

    KCmdLineArgs* args = KCmdLineArgs::parsedArgs();
    KApplication app;

    // The session-controller needs to arguments to eventually pass them to newly opened sessions
    KDevelop::SessionController::setArguments(argc, argv);

    // if empty, restart kdevelop with last active session, see SessionController::defaultSessionId
    QString session = "default";

    QString sessionId;
    foreach(const KDevelop::SessionInfo& si, KDevelop::SessionController::availableSessionInfo()) {
        if ( si.name == session ) {
            sessionId = si.uuid.toString();
            break;
        }
    }

    forever {
        KDevelop::SessionController::LockSessionState state = KDevelop::SessionController::tryLockSession(sessionId);

        if(!state) {
            QDBusInterface interface(QString("org.kdevelop.kdevelop-%1").arg(state.holderPid),
                                     "/kdevelop/MainWindow", "org.kdevelop.MainWindow",
                                     QDBusConnection::sessionBus());
            if (interface.isValid()) {
                QDBusReply<void> reply = interface.call("ensureVisible");
                if (reply.isValid()) {
                    qDebug() << i18n("made running kdevelop instance (PID: %1) visible", state.holderPid);
                    return 0;
                }
            }

            QString errmsg = i18n("<p>Failed to lock the session <em>%1</em>, "
                                  "already locked by %2 (PID %4) on %3.<br>"
                                  "The given application did not respond to a DBUS call, "
                                  "it may have crashed or is hanging.</p>"
                                  "<p>Do you want to remove the lock file and force a new KDevelop instance?<br/>"
                                  "<strong>Beware:</strong> Only do this if you are sure there is no running"
                                  " KDevelop process using this session.</p>",
                                  session, state.holderApp, state.holderHostname, state.holderPid );

            KGuiItem overwrite = KStandardGuiItem::cont();
            overwrite.setText(i18n("remove lock file"));
            KGuiItem cancel = KStandardGuiItem::quit();
            int ret = KMessageBox::warningYesNo(0, errmsg, i18n("Failed to Lock Session %1", session),
                                                overwrite, cancel, QString() );
            if (ret == KMessageBox::Yes) {
                if (!QFile::remove(state.lockFile)) {
                    KMessageBox::error(0, i18n("Failed to remove lock file %1.", state.lockFile));
                    return 1;
                }
            } else {
                return 1;
            }
        } else {
            break;
        }
    }

    KDevIDEExtension::init();

    KSplashScreen* splash = 0;
    QString splashFile = KStandardDirs::locate( "appdata", "pics/kdevelop-splash.png" );
    if( !splashFile.isEmpty() )
    {
        QPixmap pm;
        pm.load( splashFile );
        splash = new KSplashScreen( pm );
        splash->show();
    }

    if(!Core::initialize(splash, Core::Default, session))
        return 5;

    KGlobal::locale()->insertCatalog( Core::self()->componentData().catalogName() );
    Core* core = Core::self();

    QStringList projectNames = args->getOptionList("project");
    if(!projectNames.isEmpty())
    {
        foreach(const QString& p, projectNames)
        {
            QFileInfo info( p );
            if( info.suffix() == "kdev4" ) {
                // make sure the project is not already opened by the session controller
                bool shouldOpen = true;
                KUrl url(info.absoluteFilePath());
                foreach(KDevelop::IProject* p, core->projectController()->projects()) {
                    if (p->projectFileUrl() == url) {
                        shouldOpen = false;
                        break;
                    }
                }
                if (shouldOpen) {
                    core->projectController()->openProject( url );
                }
            }
        }
    }

    int count=args->count();
    for(int i=0; i<count; ++i)
    {
	QString file=args->arg(i);
	//Allow opening specific lines in documents, like mydoc.cpp:10
	int lineNumberOffset = file.lastIndexOf(':');
	KTextEditor::Cursor line;
	if( lineNumberOffset != -1 )
	{
	    bool isInt;
	    int lineNr = file.mid(lineNumberOffset+1).toInt(&isInt);
	    if (isInt)
	    {
		file = file.left(lineNumberOffset);
		line = KTextEditor::Cursor(lineNr, 0);
	    }
	}

	if( QFileInfo(file).isRelative() ) {
	    file = QDir::currentPath() + QDir::separator() + file;
	}
	KUrl f( "file://"+file );

	if(!core->documentController()->openDocument(f, line))
	    kWarning() << i18n("Could not open %1") << args->arg(i);
    }
    args->clear();

    GluonCreator::ProjectSelectionDialog *projectDialog = new GluonCreator::ProjectSelectionDialog( );
    projectDialog->setModal( true );
    projectDialog->raise( );
    projectDialog->setPage( GluonCreator::ProjectSelectionDialog::NewProjectPage );
    projectDialog->show();

    return app.exec();
}
