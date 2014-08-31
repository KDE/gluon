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

#ifndef GLUONCORE_LOG_H
#define GLUONCORE_LOG_H

#include <QtCore/QTextStream>
#include <QtCore/QTime>

#include "singleton.h"
#include "privatepointer.h"
#include "gluoncore_export.h"

class QMessageLogContext;
namespace GluonCore
{
    /**
     * The log level, which indicates the importance of the message.
     */
    enum LogLevel
    {
        LogCritical, ///< Critical messages, something has gone really wrong. Usually cause the program to exit.
        LogError, ///< Error messages, something has gone wrong but execution can continue.
        LogWarning, ///< Warning messages, not everything is as it should be but execution can continue.
        LogInfo, ///< Informational messages, reporting the status of certain components.
        LogNotice, ///< Notice messages, more detailed status reporting and warnings that can mostly be ignored.
        LogDebug ///< Debug messages, used for tracking program flow and events.
    };

    /**
     * The category a message belongs to.
     *
     * \todo It probably makes sense to change category to a QByteArray so we have more flexibility.
     */
    enum LogCategory
    {
        UnknownCategory, ///< Default category, source can be anything.
        GluonCoreCategory, ///< Messages originating from Gluon Core.
        GluonAudioCategory, ///< Messages originating from Gluon Audio.
        GluonGraphicsCategory, ///< Messages originating from Gluon Graphics.
        GluonInputCategory, ///< Messages originating from Gluon Input.
        GluonSmartsCategory, ///< Messages originating from Gluon Smarts.
        GluonEngineCategory, ///< Messages originating from Gluon Engine.
        GluonPlayerCategory, ///< Messages originating from Gluon Player.
        GluonCreatorCategory, ///< Messages originating from Gluon Creator.
        QtCategory ///< Messages originating from Qt.
    };

    /**
     * All data we collect for a log message.
     */
    struct GLUONCORE_EXPORT LogData
    {
        QTime time;
        QString message;
        QByteArray context;
        LogCategory category;
        LogLevel level;
    };

    /**
     * Helper class for building a log message to output.
     *
     * While it is possible to construct this manually, we recommend using the LOG()
     * and related macros instead, as they greatly simplify the process.
     */
    class GLUONCORE_EXPORT LogBuilder
    {
        public:
            LogBuilder( LogCategory category, LogLevel level, const QByteArray& context = QByteArray() );
            ~LogBuilder();

            QTextStream& stream();

        private:
            QTextStream m_stream;
            LogData m_data;
            bool m_hasContext = false;
    };

    /**
     * A class for writing structured log files.
     *
     * This class, together with LogData and LogBuilder, implements a structured,
     * categorized logging system. Log primarily implements policies regarding what
     * to log and where to log to. LogBuilder constructs a LogData object that is sent
     * to Log on destruction. Log then outputs the data of that LogData object to
     * whatever output was selected.
     *
     * There is no way to use the Log class to directly send a message. Instead, create
     * an instance of LogBuilder to add a message. LogBuilder will send the message on
     * destruction, so it is best to create it on the stack.
     *
     * ## LogLevel and LogCategory
     *
     * Each message has a level and category. These are used to determine whether a
     * message should be logged at all. During compile time, a maximum log level can
     * be set using the `GLUON_MAX_LOG_LEVEL` define. This will define a global maximum
     * logging level, anything above that level will be ignored.The value of this define
     * defaults to LogDebug for debug builds and LogWarning for release builds.
     *
     * In addition, each category can have a different maximum logging level set at runtime.
     * If a message is under the maximum log level but over a category's runtime defined
     * maximum log level it is also ignored. Finally, if it passes the check the category
     * and log level will be used to print a log message.
     *
     * ## Logging Context
     *
     * Each message additionally has a context. This is a string used to provide
     * context to a message, that is, indicate where the message originated from. The Log
     * class maintains a stack of contexts. Each time setCurrentContext is called, this
     * will add a new context to the stack, whereas clearCurrentContext will remove the top
     * context from the stack. The macros DEBUG(), NOTICE(), INFO(), WARNING(), ERROR() and
     * CRITICAL() will all provide a default context of file, line and function name. The
     * macros suffixed with _NC will provide an empty context, which means it will use
     * whatever context is current. This can be used to provide a different context for
     * messages not originating from a certain file, like compilation errors from a script
     * file pointing to the script file rather than the C++ source file.
     *
     * \warning Code supplied to the LOG() related macros may be ignored or even completely
     * removed depending on the maximum compile and runtime log level. Therefore, you should
     * never rely on logging code to perform important function like initialization.
     */
    class GLUONCORE_EXPORT Log : public Singleton< Log >
    {
        Q_OBJECT
        GLUON_SINGLETON( Log )

        public:
            /**
             * Should we log a message when outputting to a certain category and log level?
             *
             * \param category The category to log to.
             * \param level The log level.
             *
             * \return True if the message should be logged, false if not.
             */
            bool shouldLog( LogCategory category, LogLevel level ) const;

            /**
             * \return The current logging context.
             */
            QByteArray currentContext() const;

            /**
             * Set the maximum log level output for a certain category.
             *
             * \param category The category to set the maximum log level for.
             * \param level The maximum log level to output.
             */
            void setLogLevel( LogCategory category, LogLevel level );

            /**
             * Set the current logging context.
             *
             * \param context The current context.
             */
            void setCurrentContext( const QByteArray& context );

            /**
             * Clear the current logging context.
             */
            void clearCurrentContext();

        Q_SIGNALS:
            /**
             * Emitted whenever a new log message is output.
             *
             * \param message The message that was just output.
             */
            void newMessage( const LogData& message );

        private:
            friend class LogBuilder;
            /**
             * Output a message.
             *
             * \note This does not do any filtering.
             *
             * \param message The message to output.
             */
            void outputMessage( const LogData& message );

            ~Log();
            class Private;
            Private* const d;
    };

    /**
     * A custom Qt message handler function.
     *
     * This will output Qt's messages to the log when installed using
     * qInstallMessageHandler().
     */
    void GLUONCORE_EXPORT gluonMessageHandler( QtMsgType type, const QMessageLogContext& context, const QString& message );
}

//Define a compile-time maximum log level that can be overridden by the
//build system.
#ifndef GLUON_MAX_LOG_LEVEL
#define GLUON_MAX_LOG_LEVEL GluonCore::LogDebug
#endif

//Define the default log category that can be overridden by the build system.s
#ifndef GLUON_DEFAULT_LOG_CATEGORY
#define GLUON_DEFAULT_LOG_CATEGORY GluonCore::UnknownCategory
#endif

//Define a set of macros to simplify the actual logging process.

/**
 * Create a LogBuilder object and return its stream.
 *
 * The main logging macro that does log level checking and creates the log when
 * everything is as it should be.
 *
 * \param category The category to log.
 * \param level The log level.
 * \param context The context for this log message.
*/
#define LOG(category, level, context)\
    if( level > GLUON_MAX_LOG_LEVEL ) ;\
    else if( !GluonCore::Log::instance()->shouldLog( category, level ) ) ;\
    else GluonCore::LogBuilder(category, level, context).stream()

//Define a default logging context macro.
#define DEFAULT_CONTEXT QString("%1:%2 %3()").arg(__FILE__).arg(__LINE__).arg(__func__).toUtf8()

/**
 * A series of macros to output at a certain log level, using the default category and context.
 */
#define CRITICAL() LOG( GLUON_DEFAULT_LOG_CATEGORY, GluonCore::LogCritical, DEFAULT_CONTEXT )
#define ERROR() LOG( GLUON_DEFAULT_LOG_CATEGORY, GluonCore::LogError, DEFAULT_CONTEXT )
#define WARNING() LOG( GLUON_DEFAULT_LOG_CATEGORY, GluonCore::LogWarning, DEFAULT_CONTEXT )
#define INFO() LOG( GLUON_DEFAULT_LOG_CATEGORY, GluonCore::LogInfo, DEFAULT_CONTEXT )
#define NOTICE() LOG( GLUON_DEFAULT_LOG_CATEGORY, GluonCore::LogNotice, DEFAULT_CONTEXT )
#define DEBUG() LOG( GLUON_DEFAULT_LOG_CATEGORY, GluonCore::LogDebug, DEFAULT_CONTEXT )

/**
 * A series of macros to output at a certain log level, using the default category and an empty context.
 *
 * Use these in combination with Log::setCurrentContext() to provide custom contexts, like Asset files.
 */
#define CRITICAL_NC() LOG( GLUON_DEFAULT_LOG_CATEGORY, GluonCore::LogCritical, QByteArray() )
#define ERROR_NC() LOG( GLUON_DEFAULT_LOG_CATEGORY, GluonCore::LogError, QByteArray() )
#define WARNING_NC() LOG( GLUON_DEFAULT_LOG_CATEGORY, GluonCore::LogWarning, QByteArray() )
#define INFO_NC() LOG( GLUON_DEFAULT_LOG_CATEGORY, GluonCore::LogInfo, QByteArray() )
#define NOTICE_NC() LOG( GLUON_DEFAULT_LOG_CATEGORY, GluonCore::LogNotice, QByteArray() )
#define DEBUG_NC() LOG( GLUON_DEFAULT_LOG_CATEGORY, GluonCore::LogDebug, QByteArray() )

#endif // GLUONCORE_LOG_H
