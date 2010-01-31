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

#include "textureasset.h"

#include <QtCore/QUrl>
#include <QtGui/QImage>

#include <graphics/texture.h>

REGISTER_OBJECTTYPE(GluonEngine, TextureAsset)

using namespace GluonEngine;

class TextureAsset::TextureAssetPrivate {
public:
    TextureAssetPrivate() {
        texture = new GluonGraphics::Texture;
        image = new QImage;
    }
    ~TextureAssetPrivate() {
        delete texture;
        delete image;
    }

    GluonGraphics::Texture *texture;
    QImage *image;
};

TextureAsset::TextureAsset (QObject *parent) :
    Asset(parent)
{
    d = new TextureAssetPrivate;
}

TextureAsset::~TextureAsset()
{
    delete d;
}

void TextureAsset::load()
{
    d->image->load(file().toLocalFile());
    d->texture->load(*d->image, d->image->width(), d->image->height());
}

GluonCore::GluonObject* TextureAsset::instantiate()
{
    return new TextureAsset(this);
}

Q_EXPORT_PLUGIN2(gluon_asset_texture, GluonEngine::TextureAsset)

#include "textureasset.moc"
