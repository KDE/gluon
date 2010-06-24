/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Dan Leinir Turthra Jensen <admin@leinir.dk>
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

#include "scriptingasset.h"

#include <QtCore/QFile>
#include <QtCore/QMimeData>
#include "scriptingengine.h"

REGISTER_OBJECTTYPE(GluonEngine, ScriptingAsset);

namespace GluonEngine
{
    class ScriptingAsset::Private
    {
        public:
            Private() {};
            
            QString script;
    };
}

using namespace GluonEngine;

ScriptingAsset::ScriptingAsset(QObject* parent)
    : Asset(parent)
    , d(new Private)
{
}

ScriptingAsset::~ScriptingAsset()
{
    delete(d);
}

const QStringList
ScriptingAsset::supportedMimeTypes() const
{
    QStringList mime;
    
    mime << "application/javascript";
    mime << "text/plain";
    
    return mime;
}

void
ScriptingAsset::load()
{
    ScriptingEngine::instance()->unregisterAsset(this);
    QFile script(file().path());
    if (script.open(QIODevice::ReadOnly))
    {
        d->script = script.readAll();
        mimeData()->setText(d->script);
    }
    ScriptingEngine::instance()->registerAsset(this);
}

QString
ScriptingAsset::className() const
{
    return ScriptingEngine::instance()->className(this);
}

Q_EXPORT_PLUGIN2(gluon_component_scripting, GluonEngine::ScriptingAsset)

#include "scriptingasset.moc"
