#ifndef KAL_OGG_STREAMER
#define KAL_OGG_STREAMER

#include <AL/al.h>
#include <ogg/ogg.h>
#include <vorbis/vorbisfile.h>

#include <QThread>
#include <string>
#include "kalsource.h"
#define BUFFER_SIZE (4096 * 4)

using namespace std;

class KALOggStreamer : public QThread
{
Q_OBJECT
    public:
        KALOggStreamer(QString fileName=QString());
        void run();
        bool playing();

     public slots:
        void play(){run();}
        void playThread(){start();}
   protected:
        void open(string path);
        void release();
        void display();
        bool playback();
        bool update();

       void setFileName(QString f) { m_fileName = f;}
    
  

 

        bool stream(ALuint buffer);
        void empty();
        void check();
        string errorString(int code);

    private:

        FILE*           oggFile;
        OggVorbis_File  oggStream;
        vorbis_info*    vorbisInfo;
        vorbis_comment* vorbisComment;

        ALuint buffers[2];
        ALuint source;
        ALenum format;

         QString m_fileName;
};


#endif 
