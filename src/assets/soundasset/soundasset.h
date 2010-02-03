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

#ifndef SOUNDASSET_H
#define SOUNDASSET_H

#include "gameproject/asset.h"
#include "kal/kalbuffer.h"
#include <QtCore/QStringList>

namespace Gluon {

class SoundAsset : public Asset
{
Q_OBJECT
public:
    SoundAsset(QObject *parent = 0);

    virtual GluonObject *instantiate();
    virtual const QStringList supportedMimeTypes() const;

    virtual void setFile(const QUrl &newFile);
    
    KALBuffer *buffer() {
        return m_buffer;
    }

private Q_SLOTS:
    void updateBuffer();

private:
    KALBuffer *m_buffer;
};

}
#endif // SOUNDASSET_H
