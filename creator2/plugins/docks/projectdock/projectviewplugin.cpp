/***************************************************************************
 *   Copyright 2007 Robert Gruber <rgruber@users.sourceforge.net>          *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "projectviewplugin.h"

#include "projectview.h"

#include <klocale.h>
#include <kpluginfactory.h>
#include <kaboutdata.h>
#include <kpluginloader.h>
#include <ktexteditor/view.h>
#include <ktexteditor/document.h>
#include <ktexteditor/codecompletioninterface.h>

#include <KActionCollection>
#include <KAction>

#include <KTextEditor/HighlightInterface>

#include <interfaces/ipartcontroller.h>
#include <interfaces/icore.h>
#include <interfaces/iuicontroller.h>
#include <interfaces/idocumentcontroller.h>
#include <language/codecompletion/codecompletion.h>
#include <language/interfaces/editorcontext.h>

#include <QtGui/QMenu>
#include <QtGui/QLabel>
#include <QtGui/QGridLayout>

K_PLUGIN_FACTORY(ProjectFactory, registerPlugin<ProjectViewPlugin>(); )
K_EXPORT_PLUGIN(ProjectFactory(KAboutData("gluon_creator_viewplugin_projectview", "gluon_creator_viewplugin_projectview", ki18n("Project View"), "0.1", ki18n("view"), KAboutData::License_GPL)))

ProjectViewPlugin* ProjectViewPlugin::m_self = 0;

class ProjectViewFactory: public KDevelop::IToolViewFactory {
public:
    ProjectViewFactory(ProjectViewPlugin *plugin): m_plugin(plugin) {}

    virtual QWidget* create(QWidget *parent = 0)
    {
        Q_UNUSED(parent)
        return new GluonCreator::ProjectView();
    }

    virtual Qt::DockWidgetArea defaultPosition()
    {
        return Qt::RightDockWidgetArea;
    }

    virtual QString id() const
    {
        return "org.gluoncreator.ProjectView";
    }

private:
    ProjectViewPlugin *m_plugin;
};


ProjectViewPlugin::ProjectViewPlugin(QObject *parent, const QVariantList &)
  : KDevelop::IPlugin(ProjectFactory::componentData(), parent)
{
    Q_ASSERT(!m_self);
    m_self = this;

    m_projectViewFactory = new ProjectViewFactory(this);
    core()->uiController()->addToolView(i18n("Project View"), m_projectViewFactory);
    connect( core()->partController(), SIGNAL(partAdded(KParts::Part*)), SLOT(documentLoaded(KParts::Part*)) );
}

ProjectViewPlugin::~ProjectViewPlugin()
{
    m_self = 0;
}

ProjectViewPlugin* ProjectViewPlugin::self()
{
    return m_self;
}

void ProjectViewPlugin::unload()
{
    core()->uiController()->removeToolView(m_projectViewFactory);
}

void ProjectViewPlugin::viewCreated( KTextEditor::Document*, KTextEditor::View* view )
{
}

void ProjectViewPlugin::documentLoaded( KParts::Part* part )
{
    KTextEditor::Document *textDocument = dynamic_cast<KTextEditor::Document*>( part );
    if ( textDocument ) {
        foreach( KTextEditor::View* view, textDocument->views() )
          viewCreated( textDocument, view );

        connect( textDocument, SIGNAL( viewCreated( KTextEditor::Document*, KTextEditor::View* ) ), SLOT( viewCreated(KTextEditor::Document*, KTextEditor::View* ) ) );

    }
}

