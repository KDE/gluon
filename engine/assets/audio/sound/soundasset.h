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

#ifndef GLUON_ENGINE_SOUNDASSET_H
#define GLUON_ENGINE_SOUNDASSET_H

#include <engine/asset.h>
#include <engine/gluon_engine_export.h>
#include <audio/buffer.h>

#include <QtCore/QStringList>

namespace GluonEngine {

class GLUON_ENGINE_EXPORT SoundAsset : public Asset
{
Q_OBJECT
Q_INTERFACES(GluonEngine::Asset)
public:
    SoundAsset(QObject *parent = 0);

    virtual GluonCore::GluonObject *instantiate();

    virtual const QStringList supportedMimeTypes() const;

    //virtual QMimeData* data() const;

    /*virtual void setFile(const QUrl &newFile);

    GluonAudio::Buffer *buffer() {
        return m_buffer;
    }*/

private Q_SLOTS:
    void updateBuffer();

private:
    GluonAudio::Buffer *m_buffer;
};

}
#endif // SOUNDASSET_H
