/***************************************************************************
 *   Copyright 2007 Robert Gruber <rgruber@users.sourceforge.net>          *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef __DESIGNERPLUGIN_H__
#define __DESIGNERPLUGIN_H__

#include <interfaces/iplugin.h>
#include <interfaces/contextmenuextension.h>
#include <QtCore/QVariant>

namespace KParts {
class Part;}

class DesignerViewFactory;
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
class DesignerPlugin : public KDevelop::IPlugin
{
    Q_OBJECT

public:
    DesignerPlugin(QObject *parent, const QVariantList &args = QVariantList() );
    virtual ~DesignerPlugin();

    // KDevelop::IPlugin methods
    virtual void unload();

    static DesignerPlugin* self();

private slots:
    void viewCreated( KTextEditor::Document*, KTextEditor::View* view );
    void documentLoaded(KParts::Part*);

private:
    static DesignerPlugin* m_self;
    DesignerViewFactory* m_projectFactory;
    DesignerViewFactory* m_sceneFactory;
};

#endif

