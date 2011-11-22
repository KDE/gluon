/*
   This file is part of the KDE libraries
   Copyright (C) 2001 Waldo Bastian <bastian@kde.org>
   Copyright (C) 2004 Jarosław Staniek <staniek@kde.org>

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

#ifndef GLUON_PLAYER_GLUON_FILE_H
#define GLUON_PLAYER_GLUON_FILE_H

/**
 * \file gluon_player_file.h
 * \brief This file provides portable defines for file support.
 *
 * Use the Gluon_xxx defines instead of the normal C
 * functions and structures.
 * \since 3.3
 */

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <utime.h>
#include <gluon_player_export.h>

/* added not for Solaris and OpenSolaris platforms */

#if (defined _LFS64_LARGEFILE) && (defined _LARGEFILE64_SOURCE) && (!defined _GNU_SOURCE) && (!defined __sun)
/*
 * This section provides portable defines for large file support.
 * To use this you must compile your code with _LARGEFILE64_SOURCE
 * defined and use the Gluon_xxx defines instead of the normal
 * C functions and structures.
 *
 * Please note that not every platform supports 64 bit file structures,
 * in that case the normal 32 bit functions will be used.
 *
 * @see http://www.suse.de/~aj/linux_lfs.html
 * @see http://ftp.sas.com/standards/large.file/xopen/x_open.05Mar96.html
 *
 * Gluon makes use of the "Transitional Extensions" since we can not ensure
 * that all modules and libraries used by Gluon will be compiled with
 * 64-bit support.
 * (A.3.2.3 Mixed API and Compile Environments within a Single Process)
 */

#define Gluon_lstat         ::lstat64
#define Gluon_struct_stat   struct stat64
#define Gluon_rename        ::rename
/* TODO: define for win32 */

#else /* !_LFS64_LARGEFILE */

/*
 * This section defines portable defines for standard file support.
 */

/*
     Platform specific definitions for Solaris and OpenSolaris tested with gcc 4.3.2
*/
#if defined __sun__
#define Gluon_lstat         ::lstat
#define Gluon_struct_stat   struct stat
#define Gluon_rename        ::rename

#elif defined _WIN32 || defined _WIN64
//#define KDE_lstat       kdewin32_lstat
//#define Gluon_rename      kdewin32_rename
#else /* unix */
#define Gluon_lstat         ::lstat
#define Gluon_struct_stat   struct stat
#define Gluon_rename        ::rename
#endif

#endif

#include <QtCore/QFile>
class QString;
namespace GluonPlayer
{
    /** replacement for ::access() to handle filenames in a platform independent way */
    GLUON_PLAYER_EXPORT int access( const QString& path, int mode );
    /** replacement for ::rename() to handle pathnames in a platform independent way */
    GLUON_PLAYER_EXPORT int rename( const QString& in, const QString& out );
#ifndef Q_WS_WIN
    inline int access( const QString& path, int mode )
    {
        return ::access( QFile::encodeName( path ).constData(), mode );
    }
    inline int lstat( const QString& path, Gluon_struct_stat* buf )
    {
        return Gluon_lstat( QFile::encodeName( path ).constData(), buf );
    }
    inline int rename( const QString& in, const QString& out )
    {
        return Gluon_rename( QFile::encodeName( in ).constData(), QFile::encodeName( out ).constData() );
    }
#endif
    bool checkAccess( const QString& pathname, int mode )
    {
        int accessOK = access( pathname, mode );
        if( accessOK == 0 )
            return true;  // The file is accessible

        // In case of write the file would be created. Check, if the
        // user may write to the directory to create the file.
        if( ( mode & W_OK ) == 0 )
            return false;   // Check for write access is not part of mode => bail out

        if( !access( pathname, F_OK ) ) // if it already exists
            return false;

        //strip the filename (everything until '/' from the end
        QString dirName( pathname );
        int pos = dirName.lastIndexOf( QLatin1Char( '/' ) );
        if( pos == -1 )
            return false;   // No path in argument. This is evil, we won't allow this
        else if( pos == 0 )  // don't turn e.g. /root into an empty string
            pos = 1;

        dirName.truncate( pos ); // strip everything starting from the last '/'

        accessOK = access( dirName, W_OK );
        // Is the accessed diretory writeable ?
        if( accessOK == 0 )
            return true;  // Yes
        else
            return false; // No
    }
}

#endif /* GLUON_PLAYER_GLUON_FILE_H */
