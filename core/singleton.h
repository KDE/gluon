/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2009-2011 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (c) 2011 Laszlo Papp <lpapp@kde.org>
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

#ifndef GLUON_CORE_SINGLETON
#define GLUON_CORE_SINGLETON

#include <QtCore/QObject>
#include <QtCore/QMutex>
#include <QtCore/QCoreApplication>

#if defined __GNUC__ && __GNUC__ >= 4 && __GNUC_MINOR__ >= 4
#define __MEMBARRIER __sync_synchronize();
#elif defined _MSC_VER && defined _WIN64
#define __MEMBARRIER MemoryBarrier();
#else
#define __MEMBARRIER
#endif

/**
 * Thread safe, lazy initialised, self deleting singleton template.
 *
 * This Singleton template provides a base class for singletons that
 * is lazily initialised, which means the singleton will only be
 * instantiated during the first call to ::instance(), it is thread
 * safe and deletes itself through the QObject hierarchy.
 *
 * <h2>Usage</h2>
 *
 * Due to the nature of this singleton, it requires slightly more
 * work to use this template. Firstly, you will need to inherit
 * Singleton to make use of this template. However, you need to
 * specify the type for the template. After that, you need to
 * include both the Q_OBJECT macro and the GLUON_SINGLETON(Type)
 * macro in the top of your class declaration. The GLUON_SINGLETON
 * declares the constructor and prevents the singleton from being
 * copied.
 *
 * In your definition, you should use the macro
 * GLUON_DEFINE_SINGLETON(Type). This will define the required static
 * variables for your class. Lastly, you need to define the
 * constructor, which is the same as the default QObject constructor.
 * Be sure to pass the parameter to the singleton superclass,
 * otherwise you will get a compile error.
 *
 * The following is an example of all of this:
 *
 * <blockquote>
 * #include <core/singleton.h>
 * class Example : public GluonCore::Singleton< Example > //Inherit template
 * {
 *      Q_OBJECT
 *      GLUON_SINGLETON( Example ) //Declare constructor and disable copying
 *      public:
 *          void exampleMethod();
 *
 * };
 *
 * GLUON_DEFINE_SINGLETON( Example ) //Define the static variables
 *
 * Example::Example( QObject* parent ) //Constructor definition
 *     : GluonCore::Singleton< Example >( parent )
 * {
 * }
 *
 * void Example::exampleMethod()
 * {
 * }
 * </blockquote>
 *
 */
namespace GluonCore
{
    template <typename T>
    class Singleton : public QObject
    {
        public:
            /**
             * Retrieve the instance.
             *
             * \return The only existing instance of this class.
             */
            static T* instance()
            {
                if( !sm_guard )
                {
                    QMutex* mutex = mutexInstance();
                    mutex->lock();
                    if( !sm_instance )
                    {
                        sm_instance = new T( QCoreApplication::instance() );
                    }
                    mutex->unlock();
                    __MEMBARRIER
                    sm_guard = true;
                }
                return sm_instance;
            }

        protected:
            /**
             * Constructor.
             *
             * Makes it possible to use the QObject hierarchy for
             * deletion of this object.
             */
            explicit Singleton( QObject* parent = 0 ) : QObject( parent ) { }

            /**
             * Destructor.
             *
             * Cleans up the mutex so we do not accidentally leak it.
             */
            virtual ~Singleton()
            {
#if QT_VERSION >= 0x050000
                delete sm_mutex.load();
                sm_mutex.store( 0 );
#else
                delete sm_mutex;
                sm_mutex = 0;
#endif
            }

        private:

            static QMutex* mutexInstance()
            {
#if QT_VERSION >= 0x050000
                if( sm_mutex.load() )
#else
                if( !sm_mutex )
#endif
                {
                    QMutex* mutex = new QMutex();
                    if( !sm_mutex.testAndSetOrdered( 0, mutex ) ) /* some other thread beat us to it */
                        delete mutex;
                }
#if QT_VERSION >= 0x050000
                return sm_mutex.load();
#else
                return sm_mutex;
#endif
            }

            static T* sm_instance;
            static bool sm_guard;
            static QBasicAtomicPointer<QMutex> sm_mutex;

            Q_DISABLE_COPY( Singleton )
    };
}


#ifdef Q_CC_MSVC
#define GLUON_DEFINE_SINGLETON(Type)\
    template<> Type* GluonCore::Singleton<Type>::sm_instance = 0;\
    template<> QBasicAtomicPointer<QMutex> GluonCore::Singleton<Type>::sm_mutex = Q_BASIC_ATOMIC_INITIALIZER(0);\
    template<> bool GluonCore::Singleton<Type>::sm_guard = false;
#else
#define GLUON_DEFINE_SINGLETON(Type)\
    template<> Q_DECL_EXPORT Type* GluonCore::Singleton<Type>::sm_instance = 0;\
    template<> Q_DECL_EXPORT QBasicAtomicPointer<QMutex> GluonCore::Singleton<Type>::sm_mutex = Q_BASIC_ATOMIC_INITIALIZER(0);\
    template<> Q_DECL_EXPORT bool GluonCore::Singleton<Type>::sm_guard = false;
#endif

#define GLUON_SINGLETON(Type) \
    private:\
    friend class GluonCore::Singleton<Type>;\
    Type( QObject* parent );\
    Q_DISABLE_COPY(Type)

#endif // GLUON_CORE_SINGLETON
