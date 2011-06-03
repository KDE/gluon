/***************************************************************************
 *   Copyright 2007 Robert Gruber <rgruber@users.sourceforge.net>          *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "sceneviewplugin.h"

#include "scenedock.h"

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

K_PLUGIN_FACTORY(SceneFactory, registerPlugin<SceneViewPlugin>(); )
K_EXPORT_PLUGIN(SceneFactory(KAboutData("gluon_creator_viewplugin_sceneview", "gluon_creator_viewplugin_sceneview", ki18n("Scene View"), "0.1", ki18n("view"), KAboutData::License_GPL)))

SceneViewPlugin* SceneViewPlugin::m_self = 0;

class SceneViewFactory: public KDevelop::IToolViewFactory{
public:
    SceneViewFactory(SceneViewPlugin *plugin): m_plugin(plugin) {}

    virtual QWidget* create(QWidget *parent = 0)
    {
        Q_UNUSED(parent)
        return new GluonCreator::SceneDock("Scene View");
    }

    virtual Qt::DockWidgetArea defaultPosition()
    {
        return Qt::RightDockWidgetArea;
    }

    virtual QString id() const
    {
        return "org.gluoncreator.SceneView";
    }

private:
    SceneViewPlugin *m_plugin;
};


SceneViewPlugin::SceneViewPlugin(QObject *parent, const QVariantList &)
  : KDevelop::IPlugin(SceneFactory::componentData(), parent)
{
    Q_ASSERT(!m_self);
    m_self = this;

    m_sceneViewFactory = new SceneViewFactory(this);
    core()->uiController()->addToolView(i18n("Scene View"), m_sceneViewFactory);
    connect( core()->partController(), SIGNAL(partAdded(KParts::Part*)), SLOT(documentLoaded(KParts::Part*)) );
}

SceneViewPlugin::~SceneViewPlugin()
{
    m_self = 0;
}

SceneViewPlugin* SceneViewPlugin::self()
{
    return m_self;
}

void SceneViewPlugin::unload()
{
    core()->uiController()->removeToolView(m_sceneViewFactory);
}

void SceneViewPlugin::viewCreated( KTextEditor::Document*, KTextEditor::View* view )
{
}

void SceneViewPlugin::documentLoaded( KParts::Part* part )
{
    KTextEditor::Document *textDocument = dynamic_cast<KTextEditor::Document*>( part );
    if ( textDocument ) {
        foreach( KTextEditor::View* view, textDocument->views() )
          viewCreated( textDocument, view );

        connect( textDocument, SIGNAL( viewCreated( KTextEditor::Document*, KTextEditor::View* ) ), SLOT( viewCreated(KTextEditor::Document*, KTextEditor::View* ) ) );

    }
}

