/***************************************************************************
 *   Copyright 2007 Robert Gruber <rgruber@users.sourceforge.net>          *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef GLUON_CREATOR_SCENEVIEWPLUGIN_H
#define GLUON_CREATOR_SCENEVIEWPLUGIN_H

#include <interfaces/iplugin.h>
#include <interfaces/contextmenuextension.h>
#include <QtCore/QVariant>

namespace KParts {
class Part;}

class SceneViewFactory;
namespace KTextEditor
{
class Document;
class View;
}

class KAction;
class QMenu;

/**
 * This is the main class of KDevelop's snippet plugin.
 * @author Robert Gruber <rgruber@users.sourceforge.net>
 */
class SceneViewPlugin : public KDevelop::IPlugin
{
    Q_OBJECT

public:
    SceneViewPlugin(QObject *parent, const QVariantList &args = QVariantList() );
    virtual ~SceneViewPlugin();

    // KDevelop::IPlugin methods
    virtual void unload();

    static SceneViewPlugin* self();

private slots:
    void viewCreated( KTextEditor::Document*, KTextEditor::View* view );
    void documentLoaded(KParts::Part*);

private:
    static SceneViewPlugin* m_self;
    SceneViewFactory* m_sceneViewFactory;
};

#endif

