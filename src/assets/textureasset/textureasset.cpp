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

#include <QImage>
#include <kgl/kgltexture.h>

#include "textureasset.h"
#include "textureassetprivate.h"
#include <QUrl>

using namespace Gluon;

REGISTER_OBJECTTYPE(TextureAsset)

TextureAsset::TextureAsset ( QObject* parent ) : Asset ( parent )
{
    d = new TextureAssetPrivate;
    d->texture = new KGLTexture;
    d->image = new QImage;
}

TextureAsset::TextureAsset ( const Gluon::TextureAsset& other )
    : Asset ( other ),
      d(other.d)
{
}

TextureAsset::~TextureAsset()
{
    delete d->texture;
    delete d->image;
}


void TextureAsset::load()
{
    d->image->load(file().encodedPath());
    d->texture->load(*d->image, d->image->width(), d->image->height());
}

Gluon::GluonObject* Gluon::TextureAsset::instantiate()
{
    return new TextureAsset(this);
}

