/*
 * ALURE  OpenAL utility library
 * Copyright (c) 2009 by Chris Robinson.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

/* Title: File I/O */

#include "config.h"

#include "main.h"

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include <iostream>

#ifndef O_BINARY
#define O_BINARY 0
#endif

MemStreamBuf::int_type MemStreamBuf::underflow()
{
    if(gptr() == egptr())
    {
        char_type *data = (char_type*)memInfo.Data;
        setg(data, data + memInfo.Pos, data + memInfo.Length);
        memInfo.Pos = memInfo.Length;
    }
    if(gptr() == egptr())
        return traits_type::eof();
    return (*gptr())&0xFF;
}

MemStreamBuf::pos_type MemStreamBuf::seekoff(off_type offset, std::ios_base::seekdir whence, std::ios_base::openmode mode)
{
    if((mode&std::ios_base::out))
        return traits_type::eof();

    pos_type pos;
    switch(whence)
    {
        case std::ios_base::beg:
            pos = pos_type(offset);
            break;
        case std::ios_base::cur:
            pos = pos_type(memInfo.Pos) - pos_type(egptr()-gptr());
            pos += offset;
            break;
        case std::ios_base::end:
            pos = memInfo.Length + pos_type(offset);
            break;
        default:
            return traits_type::eof();
    }

    return seekpos(pos, mode);
}

MemStreamBuf::pos_type MemStreamBuf::seekpos(pos_type pos, std::ios_base::openmode mode)
{
    if((mode&std::ios_base::out))
        return traits_type::eof();

    if(pos < 0 || pos > pos_type(memInfo.Length) || pos != pos_type(size_t(pos)))
        return traits_type::eof();
    memInfo.Pos = pos;

    setg(0, 0, 0);
    return pos;
}


int FileStreamBuf::underflow()
{
    if(usrFile && gptr() == egptr())
    {
        ALsizei amt = fio.read(usrFile, reinterpret_cast<ALubyte*>(&buffer[0]), sizeof(buffer));
        if(amt >= 0) setg(buffer, buffer, buffer+amt);
    }
    if(gptr() == egptr())
        return traits_type::eof();
    return (*gptr())&0xFF;
}

FileStreamBuf::pos_type FileStreamBuf::seekoff(off_type offset, std::ios_base::seekdir whence, std::ios_base::openmode mode)
{
    if(!usrFile || (mode&std::ios_base::out))
        return traits_type::eof();

    pos_type pos;
    switch(whence)
    {
        case std::ios_base::beg:
            pos = pos_type(fio.seek(usrFile, offset, SEEK_SET));
            break;

        case std::ios_base::cur:
            offset -= off_type(egptr()-gptr());
            pos = pos_type(fio.seek(usrFile, offset, SEEK_CUR));
            break;

        case std::ios_base::end:
            pos = pos_type(fio.seek(usrFile, offset, SEEK_END));
            break;

        default:
            pos = traits_type::eof();
    }
    if(pos >= 0)
        setg(0, 0, 0);
    return pos;
}

FileStreamBuf::pos_type FileStreamBuf::seekpos(pos_type pos, std::ios_base::openmode mode)
{
    if(pos != pos_type(off_type(pos)))
        return traits_type::eof();
    return seekoff(off_type(pos), std::ios_base::beg, mode);
}


static void *open_wrap(const char *filename, ALuint mode)
{
    if(mode != 0)
        return NULL;

    return fopen(filename, "rb");
}

static void close_wrap(void *user_data)
{
    FILE *f = (FILE*)user_data;
    fclose(f);
}

ALsizei read_wrap(void *user_data, ALubyte *buf, ALuint bytes)
{
    FILE *f = (FILE*)user_data;
    return fread(buf, 1, bytes, f);
}

ALsizei write_wrap(void *user_data, const ALubyte *buf, ALuint bytes)
{
    FILE *f = (FILE*)user_data;
    return fwrite(buf, 1, bytes, f);
}

alureInt64 seek_wrap(void *user_data, alureInt64 offset, int whence)
{
    FILE *f = (FILE*)user_data;
#ifdef HAVE_FSEEKO
    if(offset != (off_t)offset || fseeko(f, offset, whence) != 0)
        return -1;
    return ftello(f);
#else
    if(offset != (long)offset || fseek(f, offset, whence) != 0)
        return -1;
    return ftell(f);
#endif
}

UserFuncs Funcs = {
    open_wrap,
    close_wrap,
    read_wrap,
    write_wrap,
    seek_wrap
};

extern "C" {

/* Function: alureSetIOCallbacks
 *
 * Provides callbacks for alternative methods to handle file I/O. Passing NULL
 * for all callbacks is a valid way to revert to normal I/O, otherwise they
 * must all be specified. Changing the callbacks will not affect open files
 * (they will continue using the callbacks that were set at the time they were
 * opened).
 *
 * Parameters:
 * open - This callback is called to open the named file. The given mode is the
 *        access rights the open file should have. Currently, this will always
 *        be 0 for read-only (applications should check this to make sure, as
 *        future versions may pass other values for other modes). Upon success,
 *        a non-NULL handle must be returned which will be used as a unique
 *        identifier for the file.
 * close - This callback is called to close an opened file handle. The handle
 *         will no longer be used after this function.
 * read - This callback is called when data needs to be read from the given
 *        handle. Up to the given number of bytes should be copied into 'buf'
 *        and the number of bytes actually copied should be returned. Returning
 *        0 means the end of the file has been reached (so non-blocking I/O
 *        methods should ensure at least 1 byte gets read), and negative
 *        indicates an error.
 * write - This callback is called when data needs to be written to the given
 *         handle. Up to the given number of bytes should be copied from 'buf'
 *         and the number of bytes actually copied should be returned. A return
 *         value of 0 means no more data can be written (so non-blocking I/O
 *         methods should ensure at least 1 byte gets written), and negative
 *         indicates an error.
 * seek - This callback is called to reposition the offset of the file handle.
 *        The given offset is interpreted according to 'whence', which may be
 *        SEEK_SET (absolute position from the start of the file), SEEK_CUR
 *        (relative position from the current offset), or SEEK_END (absolute
 *        position from the end of the file), as defined by standard C. The new
 *        offset from the beginning of the file should be returned. If the file
 *        cannot seek, such as when using a FIFO, -1 should be returned.
 *
 * Returns:
 * AL_FALSE on error.
 *
 * *Version Added*: 1.1
 */
ALURE_API ALboolean ALURE_APIENTRY alureSetIOCallbacks(
      void* (*open)(const char *filename, ALuint mode),
      void (*close)(void *handle),
      ALsizei (*read)(void *handle, ALubyte *buf, ALuint bytes),
      ALsizei (*write)(void *handle, const ALubyte *buf, ALuint bytes),
      alureInt64 (*seek)(void *handle, alureInt64 offset, int whence))
{
    if(open && close && read && write && seek)
    {
        Funcs.open = open;
        Funcs.close = close;
        Funcs.read = read;
        Funcs.write = write;
        Funcs.seek = seek;
        return AL_TRUE;
    }

    if(!open && !close && !read && !write && !seek)
    {
        Funcs.open = open_wrap;
        Funcs.close = close_wrap;
        Funcs.read = read_wrap;
        Funcs.write = write_wrap;
        Funcs.seek = seek_wrap;
        return AL_TRUE;
    }

    SetError("Missing callback functions");
    return AL_FALSE;
}

} // extern "C"
