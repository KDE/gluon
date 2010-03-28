/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <>
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

#include "textureasset.h"

#include <QtCore/QUrl>
#include <QtCore/QMimeData>
#include <QtGui/QImage>
#include <QtGui/QImageReader>

#include <core/debughelper.h>
#include <graphics/texture.h>

REGISTER_OBJECTTYPE(GluonEngine, TextureAsset)

using namespace GluonEngine;

class TextureAsset::TextureAssetPrivate
{
    public:
        TextureAssetPrivate()
        {
            image = new QImage;
        }
        ~TextureAssetPrivate()
        {
            delete image;
        }

        QImage *image;
};

TextureAsset::TextureAsset(QObject *parent) :
        Asset(parent)
{
    d = new TextureAssetPrivate;
}

TextureAsset::~TextureAsset()
{
    delete d;
}

const QStringList TextureAsset::supportedMimeTypes() const
{
    QList<QByteArray> supported = QImageReader::supportedImageFormats();

    QStringList supportedTypes;
    foreach(const QByteArray &type, supported)
    {
        supportedTypes << QString("image/%1").arg(QString(type));
    }

    return supportedTypes;
}

void TextureAsset::load()
{
    DEBUG_FUNC_NAME
    if (d->image->load(file().toLocalFile()))
    {
        mimeData()->setImageData(*d->image);
        setLoaded(true);
    }
    else
    {
        DEBUG_TEXT("Error loading texture!");
    }
}

Q_EXPORT_PLUGIN2(gluon_asset_texture, GluonEngine::TextureAsset)

#include "textureasset.moc"
