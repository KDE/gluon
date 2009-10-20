/*
* This file is part of the Gluon project.
* Copyright (C) 2009 Sacha Schutz <istdasklar@free.fr>
* Copyright (C) 2009 Guillaume Martres <smarter@ubuntu.com>
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; see the file COPYING.  If not, write to
* the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
* Boston, MA 02110-1301, USA.
*/

#ifndef KALENGINE2_H
#define KALENGINE2_H

#include "kal_export.h"

#include <QObject>
#include <QStringList>
#include <phonon/phononnamespace.h>


#include <AL/alc.h>

#include "common/ksingleton.h"

class KALPhonon;

/**
 * \defgroup KAL KAL
 */
//@{

class KALSound;
class KALBuffer;
//TODO do a KALEnginePrivate class
/**
* @class KALEngine kalengine.h <KALEngine>
* KALEngine is an audio engine which uses OpenAL for sound processing
*/

class KAL_EXPORT KALEngine : public KSingleton<KALEngine>
{
public:
    /**
    * Return a reference to the KALEngine singleton instance or create one if none exist
    */
    //static KALEngine *instance(const QString &deviceName = QString());

    /**
    * Return a reference to the KALEngine singleton instance or create one if none exist
    */
    //static KALEngine *instance(Phonon::Category category);

    /**
    * Change the output device to the specified OpenAL device name
    * @param deviceName the OpenAL device name
    * @return true if the new device was successfuly set, false otherwise
    * @see deviceList, setCategory
    */
    bool setDevice(const QString &deviceName);

    static ALCcontext *context() {
        return instance()->getAlContext();
    }

    static ALCdevice* device() {
        return instance()->getAlDevice();
    }

    /**
    * @return a QStringList of the available output devices
    * @see setDevice
    */
    static QStringList deviceList();

    static  bool isExtensionSupported(const QString &name);

    static void close() {
        delete instance();
    }

    ALCdevice *getAlDevice() {
        return m_device;
    }

    ALCcontext *getAlContext() {
        return m_context;
    }

private:
    friend class KSingleton<KALEngine>;
    
    KALEngine();
    //KALEngine(const QString &deviceName = QString(), QObject *parent = 0);
    //KALEngine(Phonon::Category category, QObject *parent = 0);
    ~KALEngine();

    Q_DISABLE_COPY(KALEngine)
    
    static KALEngine *m_instance;
    ALCcontext *m_context;
    ALCdevice *m_device;
    KALPhonon *m_phonon;
};

//@}
#endif // KALENGINE2_H
