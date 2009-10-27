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

#include <QtGui/QImage>
#include <kgl/kgltexture.h>

#include "textureasset.h"
#include <QtCore/QUrl>

using namespace Gluon;

REGISTER_OBJECTTYPE(TextureAsset)

class Gluon::TextureAssetPrivate {
public:
    TextureAssetPrivate() {
        texture = new KGLTexture;
        image = new QImage;
    }
    ~TextureAssetPrivate() {
        delete texture;
        delete image;
    }

    KGLTexture *texture;
    QImage *image;
};

TextureAsset::TextureAsset (QObject *parent) :
    Asset(parent)
{
    d = new TextureAssetPrivate;
}

TextureAsset::~TextureAsset()
{
    delete d->texture;
    delete d->image;
}

void TextureAsset::load()
{
    d->image->load(file());
    d->texture->load(*d->image, d->image->width(), d->image->height());
}

Gluon::GluonObject* Gluon::TextureAsset::instantiate()
{
    return new TextureAsset(this);
}

#include "textureasset.moc"
