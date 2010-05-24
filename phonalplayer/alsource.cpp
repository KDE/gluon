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

#include "alsource.h"
#include <AL/al.h>
#include <AL/alc.h>

class ALSource::ALSourcePrivate
{
    public:
        ALuint source;
        ALuint buffers[4];
};


ALSource::ALSource(Phonon::AudioDataOutput* out): QObject(out), d(new ALSourcePrivate)
{
    connect(out, SIGNAL(dataReady(QMap<Phonon::AudioDataOutput::Channel,QVector<qint16> >)),
            this, SLOT(data(QMap<Phonon::AudioDataOutput::Channel,QVector<qint16> >)));

    alGenSources(1, &d->source);
    alGenBuffers(4, d->buffers);

    alSource3f(d->source, AL_POSITION, 0.0f, 0.0f, 0.0f);

    alSourceQueueBuffers(d->source, 4, d->buffers);
    alSourcePlay(d->source);
}

ALSource::~ALSource()
{
    alDeleteSources(1, &d->source);
    alDeleteBuffers(4, d->buffers);
}

void ALSource::data(const QMap< Phonon::AudioDataOutput::Channel, QVector< qint16 > >& data)
{
    int processed;

    alGetSourcei(d->source, AL_BUFFERS_PROCESSED, &processed);

    while(processed--)
    {
        ALuint buffer;

        alSourceUnqueueBuffers(d->source, 1, &buffer);

        QVector<qint16> leftData = data.value(Phonon::AudioDataOutput::LeftChannel);

        alBufferData(buffer, AL_FORMAT_MONO16, leftData.data(), leftData.size(), 44100);

        alSourceQueueBuffers(d->source, 1, &buffer);
    }
}

#include "alsource.moc"