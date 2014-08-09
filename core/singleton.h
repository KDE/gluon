/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2009-2014 Arjen Hiemstra <ahiemstra@heimr.nl>
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
 * \note QCoreApplication::instance() is used to parent the singleton object.
 * This means that if there is no QCoreApplication instance yet, the singleton
 * object will not be explicitly deleted and might leak. Thus, it is recommended
 * to only call instance() after a QCoreApplication has been constructed.
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
                T* tmp = sm_instance.loadAcquire();
                if( !tmp )
                {
                    QMutex* mutex = mutexInstance();
                    mutex->lock();

                    tmp = sm_instance.load();
                    if( !tmp )
                        tmp = new T( QCoreApplication::instance() );

                    sm_instance.storeRelease(tmp);
                    mutex->unlock();
                }

                return tmp;
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
                delete sm_mutex.load();
                sm_mutex.store( 0 );
            }

        private:
            friend class SingletonTest;

            static QMutex* mutexInstance()
            {
                QMutex* tmp = sm_mutex.loadAcquire();
                if( !tmp )
                {
                    tmp = new QMutex();
                    if( !sm_mutex.testAndSetOrdered( 0, tmp ) ) /* some other thread beat us to it */
                    {
                        delete tmp;
                        tmp = sm_mutex.load();
                    }
                }

                return sm_mutex.load();
            }

            static QBasicAtomicPointer<T> sm_instance;
            static QBasicAtomicPointer<QMutex> sm_mutex;

            Singleton( const Singleton& ) = delete;
            Singleton& operator=(const Singleton&) = delete;
    };
}


#ifdef Q_CC_MSVC
#define GLUON_DEFINE_SINGLETON(Type)\
namespace GluonCore\
{\
    template<> QBasicAtomicPointer<Type> GluonCore::Singleton<Type>::sm_instance = Q_BASIC_ATOMIC_INITIALIZER(0);\
    template<> QBasicAtomicPointer<QMutex> GluonCore::Singleton<Type>::sm_mutex = Q_BASIC_ATOMIC_INITIALIZER(0);\
}
#else
#define GLUON_DEFINE_SINGLETON(Type)\
namespace GluonCore\
{\
    template<> Q_DECL_EXPORT QBasicAtomicPointer<Type> GluonCore::Singleton<Type>::sm_instance = Q_BASIC_ATOMIC_INITIALIZER(0);\
    template<> Q_DECL_EXPORT QBasicAtomicPointer<QMutex> GluonCore::Singleton<Type>::sm_mutex = Q_BASIC_ATOMIC_INITIALIZER(0);\
}
#endif

#define GLUON_SINGLETON(Type) \
    private:\
    friend class GluonCore::Singleton<Type>;\
    Type( QObject* parent );\
    Type( const Type& ) = delete;\
    Type& operator=(const Type&) = delete;

#endif // GLUON_CORE_SINGLETON
