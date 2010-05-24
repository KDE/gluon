#include <iostream>

#include <phonon/MediaObject>
#include <phonon/audiodataoutput.h>
#include <QtCore/QMap>

#include <AL/alut.h>

#include "alsource.h"
#include <QtCore/QCoreApplication>

int main(int argc, char **argv) {
    QCoreApplication app(argc, argv);
    app.setApplicationName("phonalplayer");
    if(argc > 1)
    {
        alutInit(&argc, argv);
        
        Phonon::MediaObject *m = new Phonon::MediaObject();
        m->setCurrentSource(Phonon::MediaSource(argv[1]));

        Phonon::AudioDataOutput* out = new Phonon::AudioDataOutput();
        Phonon::createPath(m, out);

        ALSource source(out);

        m->play();
    }

    return app.exec();
}
