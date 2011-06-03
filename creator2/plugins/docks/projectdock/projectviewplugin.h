/***************************************************************************
 *   Copyright 2007 Robert Gruber <rgruber@users.sourceforge.net>          *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef GLUON_CREATOR_PROJECTVIEWPLUGIN_H
#define GLUON_CREATOR_PROJECTVIEWPLUGIN_H

#include <interfaces/iplugin.h>
#include <interfaces/contextmenuextension.h>
#include <QtCore/QVariant>

namespace KParts {
class Part;}

class ProjectViewFactory;
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
class ProjectViewPlugin : public KDevelop::IPlugin
{
    Q_OBJECT

public:
    ProjectViewPlugin(QObject *parent, const QVariantList &args = QVariantList() );
    virtual ~ProjectViewPlugin();

    // KDevelop::IPlugin methods
    virtual void unload();

    static ProjectViewPlugin* self();

private slots:
    void viewCreated( KTextEditor::Document*, KTextEditor::View* view );
    void documentLoaded(KParts::Part*);

private:
    static ProjectViewPlugin* m_self;
    ProjectViewFactory* m_projectViewFactory;
};

#endif

