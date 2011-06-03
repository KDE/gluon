/***************************************************************************
 *   Copyright 2007 Robert Gruber <rgruber@users.sourceforge.net>          *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "designerplugin.h"

#include "projectdock.h"

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

K_PLUGIN_FACTORY(DesignerFactory, registerPlugin<DesignerPlugin>(); )
K_EXPORT_PLUGIN(DesignerFactory(KAboutData("kdevgluoncreatordesigner","kdevgluoncreatordesigner", ki18n("Designer"), "0.1", ki18n("designer"), KAboutData::License_GPL)))

DesignerPlugin* DesignerPlugin::m_self = 0;

class DesignerViewFactory: public KDevelop::IToolViewFactory{
public:
    DesignerViewFactory(DesignerPlugin *plugin, QWidget *widget): m_plugin(plugin), m_widget(widget) {}

    virtual QWidget* create(QWidget *parent = 0)
    {
        Q_UNUSED(parent)
        return m_widget;
    }

    virtual Qt::DockWidgetArea defaultPosition()
    {
        return Qt::RightDockWidgetArea;
    }

    virtual QString id() const
    {
        return "org.kdevelop.DesignerView";
    }

private:
    DesignerPlugin *m_plugin;
    QWidget *m_widget;
};


DesignerPlugin::DesignerPlugin(QObject *parent, const QVariantList &)
  : KDevelop::IPlugin(DesignerFactory::componentData(), parent)
{
    Q_ASSERT(!m_self);
    m_self = this;

    m_projectFactory = new DesignerViewFactory(this, new GluonCreator::ProjectDock("Project View"));
    m_sceneFactory = new DesignerViewFactory(this, new QLabel("Scene View"));
    core()->uiController()->addToolView(i18n("Project"), m_projectFactory);
    core()->uiController()->addToolView(i18n("Scene"), m_sceneFactory);
    connect( core()->partController(), SIGNAL(partAdded(KParts::Part*)), this, SLOT(documentLoaded(KParts::Part*)) );
}

DesignerPlugin::~DesignerPlugin()
{
    m_self = 0;
}

DesignerPlugin* DesignerPlugin::self()
{
    return m_self;
}

void DesignerPlugin::unload()
{
    core()->uiController()->removeToolView(m_projectFactory);
    core()->uiController()->removeToolView(m_sceneFactory);
}

void DesignerPlugin::viewCreated( KTextEditor::Document*, KTextEditor::View* view )
{
}

void DesignerPlugin::documentLoaded( KParts::Part* part )
{
    KTextEditor::Document *textDocument = dynamic_cast<KTextEditor::Document*>( part );
    if ( textDocument ) {
        foreach( KTextEditor::View* view, textDocument->views() )
          viewCreated( textDocument, view );

        connect( textDocument, SIGNAL( viewCreated( KTextEditor::Document*, KTextEditor::View* ) ), SLOT( viewCreated(KTextEditor::Document*, KTextEditor::View* ) ) );

    }
}

