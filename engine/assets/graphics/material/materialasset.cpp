/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#include "materialasset.h"

#include <QtCore/QUrl>
#include <QtCore/QMimeData>

#include <core/debughelper.h>
#include <graphics/material.h>
#include <graphics/engine.h>

REGISTER_OBJECTTYPE(GluonEngine, MaterialAsset)

using namespace GluonEngine;

class MaterialAsset::MaterialAssetPrivate
{
    public:
        MaterialAssetPrivate()
        {
        }
        ~MaterialAssetPrivate()
        {
        }

        QPixmap icon;

        GluonGraphics::Material* material;
};

MaterialAsset::MaterialAsset(QObject *parent)
    : Asset(parent)
    , d(new MaterialAssetPrivate)
{
    GluonGraphics::Engine::instance()->createMaterial(name());
}

MaterialAsset::~MaterialAsset()
{
    GluonGraphics::Engine::instance()->destroyMaterial(name());
    delete d;
}

QIcon MaterialAsset::icon() const
{
    if(d->icon.isNull())
        return GluonEngine::Asset::icon();

    return QIcon(d->icon);
}

const QStringList MaterialAsset::supportedMimeTypes() const
{
    QStringList types;

    types << "application/x-gluon-material";

    return types;
}

void MaterialAsset::load()
{
    if(!file().isEmpty())
    {
        if(d->material->load(file()))
        {
            mimeData()->setText(name());
            setLoaded(true);
            return;
        }
    }

    debug("Error loading material: %1", name());
}

const QList< AssetTemplate* >
MaterialAsset::templates()
{
    QList<AssetTemplate*> templates;
    templates.append(new AssetTemplate("Material", "material_template.gml", "material", this));
    return templates;
}

void MaterialAsset::setName( const QString& newName )
{
    GluonGraphics::Engine::instance()->removeMaterial(name());
    GluonGraphics::Engine::instance()->addMaterial(newName, d->material);
    GluonEngine::Asset::setName( newName );
}

Q_EXPORT_PLUGIN2(gluon_asset_material, GluonEngine::MaterialAsset)

#include "materialasset.moc"
