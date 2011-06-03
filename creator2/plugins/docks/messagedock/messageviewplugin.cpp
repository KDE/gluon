/***************************************************************************
 *   Copyright 2007 Robert Gruber <rgruber@users.sourceforge.net>          *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "messageviewplugin.h"

#include "messageview.h"

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

K_PLUGIN_FACTORY(MessageFactory, registerPlugin<MessageViewPlugin>(); )
K_EXPORT_PLUGIN(MessageFactory(KAboutData("gluon_creator_viewplugin_messageview", "gluon_creator_viewplugin_messageview", ki18n("Message View"), "0.1", ki18n("view"), KAboutData::License_GPL)))

MessageViewPlugin* MessageViewPlugin::m_self = 0;

class MessageViewFactory: public KDevelop::IToolViewFactory {
public:
    MessageViewFactory(MessageViewPlugin *plugin): m_plugin(plugin) {}

    virtual QWidget* create(QWidget *parent = 0)
    {
        Q_UNUSED(parent)
        return new GluonCreator::MessageView("Message View");
    }

    virtual Qt::DockWidgetArea defaultPosition()
    {
        return Qt::RightDockWidgetArea;
    }

    virtual QString id() const
    {
        return "org.gluoncreator.MessageView";
    }

private:
    MessageViewPlugin *m_plugin;
};


MessageViewPlugin::MessageViewPlugin(QObject *parent, const QVariantList &)
  : KDevelop::IPlugin(MessageFactory::componentData(), parent)
{
    Q_ASSERT(!m_self);
    m_self = this;

    m_messageViewFactory = new MessageViewFactory(this);
    core()->uiController()->addToolView(i18n("Message View"), m_messageViewFactory);
    connect( core()->partController(), SIGNAL(partAdded(KParts::Part*)), SLOT(documentLoaded(KParts::Part*)) );
}

MessageViewPlugin::~MessageViewPlugin()
{
    m_self = 0;
}

MessageViewPlugin* MessageViewPlugin::self()
{
    return m_self;
}

void MessageViewPlugin::unload()
{
    core()->uiController()->removeToolView(m_messageViewFactory);
}

void MessageViewPlugin::viewCreated( KTextEditor::Document*, KTextEditor::View* view )
{
}

void MessageViewPlugin::documentLoaded( KParts::Part* part )
{
    KTextEditor::Document *textDocument = dynamic_cast<KTextEditor::Document*>( part );
    if ( textDocument ) {
        foreach( KTextEditor::View* view, textDocument->views() )
          viewCreated( textDocument, view );

        connect( textDocument, SIGNAL( viewCreated( KTextEditor::Document*, KTextEditor::View* ) ), SLOT( viewCreated(KTextEditor::Document*, KTextEditor::View* ) ) );

    }
}

