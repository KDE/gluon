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

#ifndef GLUON_TEXTUREASSETPRIVATE_H
#define GLUON_TEXTUREASSETPRIVATE_H

#include <qt4/QtCore/QSharedData>

class QImage;
class KGLTexture;

namespace Gluon
{

class TextureAssetPrivate : public QSharedData
{
    public:
        TextureAssetPrivate();
        TextureAssetPrivate ( const TextureAssetPrivate& other );

        KGLTexture* texture;
        QImage* image;
};

}

#endif // GLUON_TEXTUREASSETPRIVATE_H