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

#include <config.h>

#include <kaboutdata.h>
#include <kapplication.h>
#include <kcmdlineargs.h>
#include <klocale.h>
#include <kxmlguiwindow.h>
#include <kstandarddirs.h>
#include <ksplashscreen.h>
#include <ktexteditor/cursor.h>

#include <QFileInfo>
#include <QPixmap>
#include <QTimer>
#include <QDir>
#include <QThread>
#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusReply>

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

#include "kdevideextension.h"

#include <KMessageBox>

#include <iostream>
#include <QtCore/QTextStream>

using KDevelop::Core;

int main( int argc, char *argv[] )
{
    static const char description[] = I18N_NOOP( "The KDevelop Integrated Development Environment" );
    KAboutData aboutData( "kdevelop", 0, ki18n( "KDevelop" ), QByteArray(VERSION), ki18n(description), KAboutData::License_GPL,
                          ki18n( "Copyright 1999-2010, The KDevelop developers" ), KLocalizedString(), "http://www.kdevelop.org/" );

    KCmdLineArgs::init( argc, argv, &aboutData );
    KCmdLineOptions options;
    options.add("p")
           .add("project <project>", ki18n( "Open KDevelop and load the given project." ));

    options.add("pid");

    options.add("+files", ki18n( "Files to load" ));

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

    return app.exec();
}
