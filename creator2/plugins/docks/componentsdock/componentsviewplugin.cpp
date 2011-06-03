/***************************************************************************
 *   Copyright 2007 Robert Gruber <rgruber@users.sourceforge.net>          *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "componentsviewplugin.h"

#include "componentsview.h"

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

K_PLUGIN_FACTORY(ComponentsFactory, registerPlugin<ComponentsViewPlugin>(); )
K_EXPORT_PLUGIN(ComponentsFactory(KAboutData("gluon_creator_viewplugin_componentsview", "gluon_creator_viewplugin_componentsview", ki18n("Components View"), "0.1", ki18n("view"), KAboutData::License_GPL)))

ComponentsViewPlugin* ComponentsViewPlugin::m_self = 0;

class ComponentsViewFactory: public KDevelop::IToolViewFactory{
public:
    ComponentsViewFactory(ComponentsViewPlugin *plugin): m_plugin(plugin) {}

    virtual QWidget* create(QWidget *parent = 0)
    {
        Q_UNUSED(parent)
        return new GluonCreator::ComponentsView("Components View");
    }

    virtual Qt::DockWidgetArea defaultPosition()
    {
        return Qt::RightDockWidgetArea;
    }

    virtual QString id() const
    {
        return "org.gluoncreator.ComponentsView";
    }

private:
    ComponentsViewPlugin *m_plugin;
};


ComponentsViewPlugin::ComponentsViewPlugin(QObject *parent, const QVariantList &)
  : KDevelop::IPlugin(ComponentsFactory::componentData(), parent)
{
    Q_ASSERT(!m_self);
    m_self = this;

    m_componentsViewFactory = new ComponentsViewFactory(this);
    core()->uiController()->addToolView(i18n("Components View"), m_componentsViewFactory);
    connect( core()->partController(), SIGNAL(partAdded(KParts::Part*)), SLOT(documentLoaded(KParts::Part*)) );
}

ComponentsViewPlugin::~ComponentsViewPlugin()
{
    m_self = 0;
}

ComponentsViewPlugin* ComponentsViewPlugin::self()
{
    return m_self;
}

void ComponentsViewPlugin::unload()
{
    core()->uiController()->removeToolView(m_componentsViewFactory);
}

void ComponentsViewPlugin::viewCreated( KTextEditor::Document*, KTextEditor::View* view )
{
}

void ComponentsViewPlugin::documentLoaded( KParts::Part* part )
{
    KTextEditor::Document *textDocument = dynamic_cast<KTextEditor::Document*>( part );
    if ( textDocument ) {
        foreach( KTextEditor::View* view, textDocument->views() )
          viewCreated( textDocument, view );

        connect( textDocument, SIGNAL( viewCreated( KTextEditor::Document*, KTextEditor::View* ) ), SLOT( viewCreated(KTextEditor::Document*, KTextEditor::View* ) ) );

    }
}

