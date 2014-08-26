/*
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2014 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#include "log.h"

#include <QtCore/QStack>
#include <QtCore/QtGlobal>

#include <iostream>

#define TIME_FORMAT "HH:mm:ss"
#define CATEGORY_WIDTH 8
#define LEVEL_WIDTH 7
#define CONTEXT_WIDTH 40
#define SEPARATOR " | "

using namespace GluonCore;

LogBuilder::LogBuilder( LogCategory category, LogLevel level, const QByteArray& context )
{
    if( !context.isEmpty() )
    {
        Log::instance()->setCurrentContext( context );
        m_hasContext = true;
    }

    m_data.category = category;
    m_data.level = level;
    m_data.time = QTime::currentTime();

    m_stream.setString( &(m_data.message) );
}

LogBuilder::~LogBuilder()
{
    m_data.context = Log::instance()->currentContext();
    m_data.message = m_stream.readAll();
    Log::instance()->outputMessage( m_data );

    if( m_hasContext )
        Log::instance()->clearCurrentContext();
}

QTextStream& LogBuilder::stream()
{
    return m_stream;
}

GLUON_DEFINE_SINGLETON( Log );

class Log::Private
{
public:
    const char* categoryToString( LogCategory cat );
    const char* levelToString( LogLevel level );
    QByteArray prettyContext( const QByteArray& context );

    QStack< QByteArray > contexts;
    QHash< LogCategory, LogLevel > logLevels;
};

QByteArray Log::currentContext() const
{
    return d->contexts.top();
}

bool Log::shouldLog( LogCategory category, LogLevel level ) const
{
    return d->logLevels.contains( category ) && level <= d->logLevels.value( category );
}

void Log::setLogLevel( LogCategory category, LogLevel level )
{
    d->logLevels.insert( category, level );
}

void Log::setCurrentContext( const QByteArray& context )
{
    d->contexts.push( context );
}

void Log::clearCurrentContext()
{
    d->contexts.pop();
}

void Log::outputMessage( const LogData& message )
{
    QTextStream stream{ stdout };

    stream << message.time.toString( TIME_FORMAT ) << SEPARATOR;
    stream << qSetFieldWidth( CATEGORY_WIDTH ) << d->categoryToString( message.category );
    stream << qSetFieldWidth( 0 ) << SEPARATOR;
    stream << qSetFieldWidth( CONTEXT_WIDTH ) << d->prettyContext( message.context );
    stream << qSetFieldWidth( LEVEL_WIDTH ) << d->levelToString( message.level );
    stream << qSetFieldWidth( 0 ) << ": ";
    stream << message.message << endl;

    emit newMessage( message );
}

Log::Log( QObject* parent ) : Singleton< GluonCore::Log >( parent ), d( new Private )
{
    d->logLevels.insert( UnknownCategory, LogDebug );
    d->logLevels.insert( GluonCoreCategory, LogDebug );
    d->logLevels.insert( GluonAudioCategory, LogDebug );
    d->logLevels.insert( GluonInputCategory, LogDebug );
    d->logLevels.insert( GluonGraphicsCategory, LogDebug );
    d->logLevels.insert( GluonSmartsCategory, LogDebug );
    d->logLevels.insert( GluonEngineCategory, LogDebug );
    d->logLevels.insert( GluonPlayerCategory, LogDebug );
    d->logLevels.insert( GluonCreatorCategory, LogDebug );
    d->logLevels.insert( QtCategory, LogDebug );
}

Log::~Log()
{
    delete d;
}

const char* Log::Private::categoryToString( LogCategory cat )
{
    switch( cat )
    {
        case GluonCoreCategory:
            return "Core";
        case GluonAudioCategory:
            return "Audio";
        case GluonGraphicsCategory:
            return "Graphics";
        case GluonInputCategory:
            return "Input";
        case GluonSmartsCategory:
            return "Smarts";
        case GluonEngineCategory:
            return "Engine";
        case GluonPlayerCategory:
            return "Player";
        case GluonCreatorCategory:
            return "Creator";
        case QtCategory:
            return "Qt";
        default:
            return "Unknown";
    }
}

const char* Log::Private::levelToString( LogLevel level )
{
    switch( level )
    {
        case LogCritical:
            return "[CRIT]";
        case LogError:
            return "[ERRO]";
        case LogWarning:
            return "[WARN]";
        case LogInfo:
            return "[INFO]";
        case LogNotice:
            return "[NOTI]";
        case LogDebug:
            return "[DEBG]";
        default:
            return "[UNKN]";
    }
}

QByteArray Log::Private::prettyContext( const QByteArray& context )
{
    if( context.size() > CONTEXT_WIDTH )
        return context.right( CONTEXT_WIDTH - 3 ).rightJustified( CONTEXT_WIDTH, '.' );

    return context;
}

void GluonCore::gluonMessageHandler( QtMsgType type, const QMessageLogContext& context, const QString& message )
{
    QString fn = context.function;
    fn = fn.right( fn.size() - fn.lastIndexOf(':') - 1 );
    fn = fn.left( fn.indexOf('(') );
    fn = fn.contains(' ') ? fn.right( fn.size() - fn.lastIndexOf(' ') - 1 ) : fn;

    QByteArray ctx = QString("%1:%2 %3()").arg( context.file ).arg( context.line ).arg( fn ).toUtf8();
    switch( type ) {
        case QtDebugMsg:
            LOG( QtCategory, LogDebug, ctx ) << message;
            break;
        case QtWarningMsg:
            LOG( QtCategory, LogWarning, ctx ) << message;
            break;
        case QtCriticalMsg:
            LOG( QtCategory, LogCritical, ctx ) << message;
            break;
        case QtFatalMsg:
            LOG( QtCategory, LogCritical, ctx ) << message;
            abort();
            break;
    }
}
