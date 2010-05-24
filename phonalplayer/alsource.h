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

#ifndef ALSOURCE_H
#define ALSOURCE_H

#include <QtCore/QObject>
#include <QtCore/QMap>
#include <phonon/audiodataoutput.h>

class ALSource : public QObject
{
    Q_OBJECT
    public:
        ALSource(Phonon::AudioDataOutput *out);
        ~ALSource();

    public slots:
        void data(const QMap<Phonon::AudioDataOutput::Channel, QVector<qint16> > &data);

    private:
        class ALSourcePrivate;
        ALSourcePrivate * const d;
};

#endif // ALSOURCE_H
