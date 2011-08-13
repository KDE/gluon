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

#include "scriptingengine.h"

#include <QtCore/QFile>
#include <QtCore/QMimeData>

REGISTER_OBJECTTYPE( GluonEngine, ScriptingAsset );

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

ScriptingAsset::ScriptingAsset( QObject* parent )
    : Asset( parent )
    , d( new Private )
{
}

ScriptingAsset::~ScriptingAsset()
{
    unload();
    delete d;
}

const QStringList
ScriptingAsset::supportedMimeTypes() const
{
    QStringList mime;

    mime << "application/javascript";
    mime << "text/plain";

    return mime;
}

const QList<AssetTemplate*>
ScriptingAsset::templates()
{
    QList<AssetTemplate*> templates;
    templates.append( new AssetTemplate( "Scripted Logic", "scripting_template.js", "scripting", this ) );
    return templates;
}

QString
ScriptingAsset::className() const
{
    return ScriptingEngine::instance()->className( this );
}

void ScriptingAsset::load()
{
    if( !isLoaded() )
    {
        d->script.clear();
        mimeData()->setText(d->script);
        QFile script( file().toLocalFile() );
        if( script.open( QIODevice::ReadOnly ) )
        {
            d->script = script.readAll();
            mimeData()->setText( d->script );
        }
        // Don't attempt to do anything if the script is empty
        if( d->script.isEmpty() )
            return;

        QScriptSyntaxCheckResult result = ScriptingEngine::instance()->registerAsset( this );
        if( result.state() != QScriptSyntaxCheckResult::Valid )
        {
            debug( tr( "Script error %1 (%2,%3): %4" ).arg( fullyQualifiedName() ).arg( result.errorLineNumber() ).arg( result.errorColumnNumber() ).arg( result.errorMessage() ) );
        }
        else
        {
            Asset::load();
        }
    }
}

void ScriptingAsset::unload()
{
    if( isLoaded() )
    {
        ScriptingEngine::instance()->unregisterAsset( this );
        Asset::unload();
    }
}

Q_EXPORT_PLUGIN2( gluon_component_scripting, GluonEngine::ScriptingAsset )

#include "scriptingasset.moc"
