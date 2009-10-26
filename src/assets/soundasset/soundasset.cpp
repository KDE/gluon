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

using namespace Gluon;

REGISTER_OBJECTTYPE(SoundAsset)

SoundAsset::SoundAsset(QObject *parent)
    : Asset(parent),
      m_buffer(0)
{
    connect(this, SIGNAL(dataChanged()), this, SLOT(setBuffer()));
}

Gluon::GluonObject *SoundAsset::instantiate()
{
    return new SoundAsset(this);
}

void SoundAsset::setBuffer()
{
    if (m_buffer) {
        delete m_buffer;
    }

    m_buffer = new KALBuffer(file());
}