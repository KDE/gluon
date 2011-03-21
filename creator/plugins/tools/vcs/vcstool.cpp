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

#include "vcstool.h"

#include "widgets/vcscommitdialog.h"
#include "widgets/vcslogwidget.h"
#include "widgets/vcsdiffwidget.h"

#include <core/gluon_global.h>
#include <engine/game.h>

#include <kdevplatform/shell/core.h>
#include <kdevplatform/shell/shellextension.h>
#include <kdevplatform/interfaces/iplugincontroller.h>
#include <kdevplatform/vcs/interfaces/ibasicversioncontrol.h>

#include <KDE/KLocalizedString>
#include <KDE/KAction>
#include <KDE/KUrl>
#include <KDE/KDialog>

class ConsoleIDEExtension : public KDevelop::ShellExtension
{
    public:
        static void init() { s_instance = new ConsoleIDEExtension(); }

        virtual QString xmlFile() { return QString(); }
        virtual QString binaryPath() { return QString(); };
        virtual QString defaultProfile() { return QString(); }
        virtual KDevelop::AreaParams defaultArea(){
            KDevelop::AreaParams params = {"code", i18n("Code")};
            return params;
        }
        virtual QString projectFileExtension() { return QString(); }
        virtual QString projectFileDescription() { return QString(); }
        virtual QStringList defaultPlugins() { return QStringList(); }

    protected:
        ConsoleIDEExtension() {}
};

using namespace GluonCreator;

VcsTool::VcsTool( const QString& title, QWidget* parent, Qt::WindowFlags flags )
    : QWidget( parent, flags )
{
    setWindowTitle( title );
    setObjectName( "VcsTool" );
    setupActions( );
    KConfigGroup kcg;
    loadVersionControlPlugin(kcg);
}

VcsTool::~VcsTool()
{
}

void VcsTool::setupActions()
{
    KAction* vcsToolCommit = new KAction( KIcon( "svn-commit" ), i18n( "Commit" ), this );
    vcsToolCommit->setObjectName( "VcsToolCommit" );
    insertAction(0, vcsToolCommit);
    connect( vcsToolCommit, SIGNAL( triggered( bool ) ), SLOT( commit() ) );

    KAction* vcsToolDiff = new KAction( i18n( "Diff" ), this );
    vcsToolDiff->setObjectName( "VcsToolDiff" );
    insertAction(0, vcsToolDiff);
    connect( vcsToolDiff, SIGNAL( triggered( bool ) ), SLOT( diff() ) );

    KAction* vcsToolLog = new KAction( KIcon( "view-history" ), i18n( "Log" ), this );
    vcsToolLog->setObjectName( "VcsToolLog" );
    insertAction(0, vcsToolLog);
    connect( vcsToolLog, SIGNAL( triggered( bool ) ), SLOT( log() ) );

    KAction* vcsToolPush = new KAction( KIcon( "arrow-up-double" ), i18n( "Push" ), this );
    vcsToolPush->setObjectName( "VcsToolPush" );
    insertAction(0, vcsToolPush);
    connect( vcsToolPush, SIGNAL( triggered( bool ) ), SLOT( push() ) );

    KAction* vcsToolPull = new KAction( KIcon( "arrow-down-double" ), i18n( "Pull" ), this );
    vcsToolPull->setObjectName( "VcsToolPull" );
    insertAction(0, vcsToolPull);
    connect( vcsToolPull, SIGNAL( triggered( bool ) ), SLOT( pull() ) );
}

void VcsTool::commit()
{
    KDialog *dialog = new KDialog( 0 );
    dialog->setCaption( i18n("Commit Message") );
    dialog->setButtons( KDialog::Ok | KDialog::Cancel );

    VcsCommitDialog* vcsCommitWidget = new VcsCommitDialog();
    dialog->setMainWidget( vcsCommitWidget );
    dialog->show();
    connect(dialog, SIGNAL( okClicked() ), dialog, SLOT( ok() ) );
    connect(dialog, SIGNAL( cancelClicked() ), dialog, SLOT( cancel() ) );
}

void VcsTool::diff()
{
    KDialog *dialog = new KDialog( 0 );
    dialog->setCaption( i18n("Diff Output") );
    dialog->setButtons( KDialog::Ok | KDialog::Cancel );

    VcsDiffWidget* vcsDiffWidget = new VcsDiffWidget(0, 0);
    dialog->setMainWidget( vcsDiffWidget );
    dialog->show();
    connect(dialog, SIGNAL( okClicked() ), dialog, SLOT( ok() ) );
    connect(dialog, SIGNAL( cancelClicked() ), dialog, SLOT( cancel() ) );
}

void VcsTool::log()
{
    KDialog *dialog = new KDialog( 0 );
    dialog->setCaption( i18n("Log Message") );
    dialog->setButtons( KDialog::Ok | KDialog::Cancel );

    VcsLogWidget* vcsLogWidget = new VcsLogWidget(KUrl(), 0, 0);
    dialog->setMainWidget( vcsLogWidget );
    dialog->show();
    connect(dialog, SIGNAL( okClicked() ), dialog, SLOT( ok() ) );
    connect(dialog, SIGNAL( cancelClicked() ), dialog, SLOT( cancel() ) );
}

void VcsTool::push()
{
}

void VcsTool::pull()
{
}

void VcsTool::loadVersionControlPlugin(KConfigGroup& projectGroup)
{
    // helper method for open()
    ConsoleIDEExtension::init();
    KDevelop::Core::initialize(0, KDevelop::Core::NoUi);
    KDevelop::IPluginController* pluginManager = KDevelop::Core::self()->pluginController();
    if( projectGroup.hasKey( "VersionControlSupport" ) )
    {
        // QString vcsPluginName = projectGroup.readEntry("VersionControlSupport", "");
        // if( !vcsPluginName.isEmpty() )
        // {
            // vcsPlugin = pluginManager->pluginForExtension( "org.kdevelop.IBasicVersionControl", vcsPluginName );
        // }
    } else
    {
        foreach( KDevelop::IPlugin* p, pluginManager->allPluginsForExtension( "org.kdevelop.IBasicVersionControl" ) )
        {
            KDevelop::IBasicVersionControl* iface = p->extension<KDevelop::IBasicVersionControl>();
            // if( iface && iface->isVersionControlled( topItem->url() ) )
            // {
                m_vcsPlugin = p;
                projectGroup.writeEntry("VersionControlSupport", pluginManager->pluginInfo( p ).pluginName() );
                projectGroup.sync();
             // }
        }
    }

}

