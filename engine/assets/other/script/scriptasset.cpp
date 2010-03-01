/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "scriptasset.h"

#include <QtCore/QMimeData>
#include <QtCore/QFile>

REGISTER_OBJECTTYPE(GluonEngine, ScriptAsset)

using namespace GluonEngine;

class ScriptAsset::ScriptAssetPrivate
{
    public:
        QString script;
};

ScriptAsset::ScriptAsset(QObject* parent): Asset(parent)
{
    d = new ScriptAssetPrivate;
}

ScriptAsset::~ScriptAsset()
{
    delete d;
}

const QStringList ScriptAsset::supportedMimeTypes() const
{
    QStringList mime;

    mime << "application/javascript";
    mime << "text/plain";

    return mime;
}

void ScriptAsset::load()
{
    QFile script(file().path());
    if(script.open(QIODevice::ReadOnly)) {
        d->script = script.readAll();
        mimeData()->setText(d->script);
    }
}

Q_EXPORT_PLUGIN2(gluon_asset_script, GluonEngine::ScriptAsset)

#include "scriptasset.moc"
