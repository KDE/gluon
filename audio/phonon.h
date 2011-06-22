/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2009 Guillaume Martres <smarter@ubuntu.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */
#ifndef KALPHONON_H
#define KALPHONON_H

#include "kal_export.h"

#ifdef Q_WS_X11
#include <Phonon/AudioOutput>
#endif
#ifdef Q_WS_MAC
#include <Phonon/audiooutput.h>
#endif
/**
 * \defgroup KAL KAL
 */
//@{

class KALPhononPrivate;

/**
* @class KALPhonon kalphonon.h <KALPhonon>
* KALPhonon is a wrapper class around Phonon to make it possible to use
* Phonon output device in KALEngine
*/
class KAL_EXPORT KALPhonon : public QObject
{
        Q_OBJECT

    public:
        KALPhonon( QObject* parent = 0 );
        virtual ~KALPhonon();

        void resetOutput();

        QString alDevice() const;
        Phonon::AudioOutput* phononOutput() const;
        Phonon::Category category() const;

    public Q_SLOTS:
        bool setCategory( Phonon::Category category );

    Q_SIGNALS:
        void deviceChanged( const QString& deviceName );

    private:
        Q_DISABLE_COPY( KALPhonon )

        KALPhononPrivate* const d;

    private Q_SLOTS:
        bool setDevice( const Phonon::AudioOutputDevice& device );

};

//@}
#endif // KALPHONON_H
