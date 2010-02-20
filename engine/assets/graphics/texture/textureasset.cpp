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
#include <QtCore/QMimeData>
#include <QtGui/QImage>
#include <QtGui/QImageReader>

#include <core/debughelper.h>
#include <graphics/texture.h>

REGISTER_OBJECTTYPE(GluonEngine, TextureAsset)

using namespace GluonEngine;

class TextureAsset::TextureAssetPrivate {
public:
    TextureAssetPrivate() {
        image = new QImage;
        mime = new QMimeData;
    }
    ~TextureAssetPrivate() {
        delete image;
        delete mime;
    }

    QImage *image;
    QMimeData* mime;
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

const QStringList TextureAsset::supportedMimeTypes() const
{
    QList<QByteArray> supported = QImageReader::supportedImageFormats();

    QStringList supportedTypes;
    foreach(QByteArray type, supported)
    {
        supportedTypes << QString("image/%1").arg(QString(type));
    }

    return supportedTypes;
}

QMimeData* TextureAsset::data() const
{
    return d->mime;
}

void TextureAsset::load()
{
    DEBUG_FUNC_NAME
    d->image->load(file().toLocalFile());
    d->mime->setImageData(*d->image);
}

GluonCore::GluonObject* TextureAsset::instantiate()
{
    return new TextureAsset(this);
}

Q_EXPORT_PLUGIN2(gluon_asset_texture, GluonEngine::TextureAsset)

#include "textureasset.moc"
