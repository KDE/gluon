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

#include "soundasset.h"

REGISTER_OBJECTTYPE(GluonEngine,SoundAsset)

using namespace GluonEngine;

SoundAsset::SoundAsset(QObject *parent)
    : Asset(parent),
      m_buffer(0)
{
    connect(this, SIGNAL(dataChanged()), this, SLOT(updateBuffer()));
}

GluonCore::GluonObject *SoundAsset::instantiate()
{
    return new SoundAsset(this);
}

void SoundAsset::updateBuffer()
{
    if (m_buffer) {
        delete m_buffer;
    }

    m_buffer = new GluonAudio::Buffer(file().toLocalFile());
}

Q_EXPORT_PLUGIN2(gluon_asset_sound, GluonEngine::SoundAsset)

#include "soundasset.moc"
