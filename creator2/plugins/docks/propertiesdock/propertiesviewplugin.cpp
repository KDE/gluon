/***************************************************************************
 *   Copyright 2007 Robert Gruber <rgruber@users.sourceforge.net>          *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "propertiesviewplugin.h"

#include "propertiesview.h"

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

K_PLUGIN_FACTORY(PropertiesFactory, registerPlugin<PropertiesViewPlugin>(); )
K_EXPORT_PLUGIN(PropertiesFactory(KAboutData("gluon_creator_viewplugin_propertiesview", "gluon_creator_viewplugin_propertiesview", ki18n("Properties View"), "0.1", ki18n("view"), KAboutData::License_GPL)))

PropertiesViewPlugin* PropertiesViewPlugin::m_self = 0;

class PropertiesViewFactory: public KDevelop::IToolViewFactory{
public:
    PropertiesViewFactory(PropertiesViewPlugin *plugin): m_plugin(plugin) {}

    virtual QWidget* create(QWidget *parent = 0)
    {
        Q_UNUSED(parent)
        return new GluonCreator::PropertiesView();
    }

    virtual Qt::DockWidgetArea defaultPosition()
    {
        return Qt::RightDockWidgetArea;
    }

    virtual QString id() const
    {
        return "org.gluoncreator.PropertiesView";
    }

private:
    PropertiesViewPlugin *m_plugin;
};

PropertiesViewPlugin::PropertiesViewPlugin(QObject *parent, const QVariantList &)
  : KDevelop::IPlugin(PropertiesFactory::componentData(), parent)
{
    Q_ASSERT(!m_self);
    m_self = this;

    m_propertiesViewFactory = new PropertiesViewFactory(this);
    core()->uiController()->addToolView(i18n("Properties View"), m_propertiesViewFactory);
    connect( core()->partController(), SIGNAL(partAdded(KParts::Part*)), SLOT(documentLoaded(KParts::Part*)) );
}

PropertiesViewPlugin::~PropertiesViewPlugin()
{
    m_self = 0;
}

PropertiesViewPlugin* PropertiesViewPlugin::self()
{
    return m_self;
}

void PropertiesViewPlugin::unload()
{
    core()->uiController()->removeToolView(m_propertiesViewFactory);
}

void PropertiesViewPlugin::viewCreated( KTextEditor::Document*, KTextEditor::View* view )
{
}

void PropertiesViewPlugin::documentLoaded( KParts::Part* part )
{
    KTextEditor::Document *textDocument = dynamic_cast<KTextEditor::Document*>( part );
    if ( textDocument ) {
        foreach( KTextEditor::View* view, textDocument->views() )
          viewCreated( textDocument, view );

        connect( textDocument, SIGNAL( viewCreated( KTextEditor::Document*, KTextEditor::View* ) ), SLOT( viewCreated(KTextEditor::Document*, KTextEditor::View* ) ) );

    }
}

