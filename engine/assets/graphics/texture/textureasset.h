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

#ifndef GLUON_ENGINE_TEXTUREASSET_H
#define GLUON_ENGINE_TEXTUREASSET_H

#include <gluon_engine_export.h>
#include <asset.h>

namespace GluonEngine
{

class GLUON_ENGINE_EXPORT TextureAsset : public Asset
{
    Q_OBJECT
    Q_INTERFACES(GluonEngine::Asset)

    public:
        TextureAsset(QObject *parent = 0);
        ~TextureAsset();

        GluonObject* instantiate();

        void load();

    private:
        class TextureAssetPrivate;
        TextureAssetPrivate *d;
};

}

#endif // GLUON_ENGINE_TEXTUREASSET_H
