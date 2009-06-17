#include "kaloggstreamer.h"
#include <KDebug>

KALOggStreamer::KALOggStreamer(QString fileName)
{
setFileName(fileName);
}

void KALOggStreamer::open(string path)
{
    int result;
    
    if(!(oggFile = fopen(path.c_str(), "rb")))
       kDebug()<<"Could not open Ogg file.";

    if((result = ov_open(oggFile, &oggStream, NULL, 0)) < 0)
    {
        fclose(oggFile);
        
        kDebug()<<"Could not open Ogg stream. ";
    }

    vorbisInfo = ov_info(&oggStream, -1);
    vorbisComment = ov_comment(&oggStream, -1);

    if(vorbisInfo->channels == 1)
        format = AL_FORMAT_MONO16;
    else
        format = AL_FORMAT_STEREO16;
        
        
    alGenBuffers(2, buffers);
    check();
    alGenSources(1, &source);
    check();
    
    alSource3f(source, AL_POSITION,        0.0, 0.0, 0.0);
    alSource3f(source, AL_VELOCITY,        0.0, 0.0, 0.0);
    alSource3f(source, AL_DIRECTION,       0.0, 0.0, 0.0);
    alSourcef (source, AL_ROLLOFF_FACTOR,  0.0          );
    alSourcei (source, AL_SOURCE_RELATIVE, AL_TRUE      );
}




void KALOggStreamer::release()
{
    alSourceStop(source);
    empty();
    alDeleteSources(1, &source);
    check();
    alDeleteBuffers(1, buffers);
    check();

    ov_clear(&oggStream);
}




void KALOggStreamer::display()
{
    kDebug()
        << "version         " << vorbisInfo->version         << "\n"
        << "channels        " << vorbisInfo->channels        << "\n"
        << "rate (hz)       " << vorbisInfo->rate            << "\n"
        << "bitrate upper   " << vorbisInfo->bitrate_upper   << "\n"
        << "bitrate nominal " << vorbisInfo->bitrate_nominal << "\n"
        << "bitrate lower   " << vorbisInfo->bitrate_lower   << "\n"
        << "bitrate window  " << vorbisInfo->bitrate_window  << "\n"
        << "\n"
        << "vendor " << vorbisComment->vendor << "\n";
        
    for(int i = 0; i < vorbisComment->comments; i++)
        kDebug() << "   " << vorbisComment->user_comments[i] << "\n";
        
    
}




bool KALOggStreamer::playback()
{
    if(playing())
        return true;
        
    if(!stream(buffers[0]))
        return false;
        
    if(!stream(buffers[1]))
        return false;
    
    alSourceQueueBuffers(source, 2, buffers);
    alSourcePlay(source);
    
    return true;
}




bool KALOggStreamer::playing()
{
    ALenum state;
    
    alGetSourcei(source, AL_SOURCE_STATE, &state);
    
    return (state == AL_PLAYING);
}




bool KALOggStreamer::update()
{
    int processed;
    bool active = true;

    alGetSourcei(source, AL_BUFFERS_PROCESSED, &processed);

    while(processed--)
    {
        ALuint buffer;
        
        alSourceUnqueueBuffers(source, 1, &buffer);
        check();

        active = stream(buffer);

        alSourceQueueBuffers(source, 1, &buffer);
        check();
    }

    return active;
}




bool KALOggStreamer::stream(ALuint buffer)
{
    char pcm[BUFFER_SIZE];
    int  size = 0;
    int  section;
    int  result;

    while(size < BUFFER_SIZE)
    {
        result = ov_read(&oggStream, pcm + size, BUFFER_SIZE - size, 0, 2, 1, &section);
    
        if(result > 0)
            size += result;
        else
            if(result < 0)
                kDebug()<<"errorString(result)";
            else
                break;
    }
    
    if(size == 0)
        return false;
        
    alBufferData(buffer, format, pcm, size, vorbisInfo->rate);
    check();
    
    return true;
}




void KALOggStreamer::empty()
{
    int queued;
    
    alGetSourcei(source, AL_BUFFERS_QUEUED, &queued);
    
    while(queued--)
    {
        ALuint buffer;
    
        alSourceUnqueueBuffers(source, 1, &buffer);
        check();
    }
}




void KALOggStreamer::check()
{
	int error = alGetError();

	if(error != AL_NO_ERROR)
		kDebug()<<"OpenAL error was raised.";
}



string KALOggStreamer::errorString(int code)
{
    switch(code)
    {
        case OV_EREAD:
            return string("Read from media.");
        case OV_ENOTVORBIS:
            return string("Not Vorbis data.");
        case OV_EVERSION:
            return string("Vorbis version mismatch.");
        case OV_EBADHEADER:
            return string("Invalid Vorbis header.");
        case OV_EFAULT:
            return string("Internal logic fault (bug or heap/stack corruption.");
        default:
            return string("Unknown Ogg error.");
    }
}

   void KALOggStreamer::run()
{


open(m_fileName.toUtf8().data());
display();
if(!playback())
kDebug()<<"Ogg refused to play.";
                    
 while(update())
{
if(!playing())
 {
  if(!playback())
    kDebug()<<"Ogg abruptly stopped.";
  else
    kDebug() << "Ogg stream was interrupted.\n";
 }
}
                   	release();
}