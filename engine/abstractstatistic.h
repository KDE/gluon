/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Felix Rohrbach <fxrh@gmx.de>
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

#ifndef GLUON_ENGINE_ABSTRACTSTATISTIC_H
#define GLUON_ENGINE_ABSTRACTSTATISTIC_H

#include <engine/gluon_engine_export.h>

#include <core/gluonobject.h>
#include <core/referencecounter.h>

namespace GluonEngine
{
    /**
     * Use this class to create various types of statistic subclasses.
     * This base class cares about the connections to the database
     * and the component. There are two places to save data: value, which
     * holds a qlonlong, and array, which can save a list of qlonglongs.
     * Call commit() to save these two values to the database.
     */
    class GLUON_ENGINE_EXPORT AbstractStatistic : public GluonCore::GluonObject, public GluonCore::ReferenceCounter
    {
            Q_OBJECT
            GLUON_OBJECT( GluonEngine::AbstractStatistic )
        public:
            Q_INVOKABLE AbstractStatistic( QObject* parent = 0 );
            virtual ~AbstractStatistic();

            /**
            * If this method returns true, it should be save to assume
            * that you can save data in the database.
            */
            bool isDatabaseOpen() const;

            /**
            * Should be called before using the database or after there was a
            * change of the user name or the game name. It opens the database
            * if necessary. It is no problem to call this function more than
            * one time.
            */
            virtual void initialize();

            /**
            * Called from time to time (e.g. scene change) and at the end.
            * You should use it to save your data (i.e. call commit()), if
            * there is anything to save. In this class, it does nothing.
            */
            virtual void cleanup();

            /**
            * Reimplemented from GluonCore::GluonObject::setName()
            */
            virtual void setName( const QString& newName );

            /**
             * This is the score which is saved in the database.
             */
            qlonglong value() const;

            /**
             * Note: This does not save the score in the database,
             * you have to call commit() for this.
             */
            void setValue( qlonglong value );

        public Q_SLOTS:
            /**
            * Force initialize() to open a new database connection.
            */
            void invalidate();

        protected:
            /** Returns the current array */
            QList<qlonglong> array() const;

            /**
             * Sets the current array to list.
             * Note: you must call commit() before it is saved to
             * the database.
             */
            void setArray( const QList<qlonglong>& list );

            /** Append value to the array */
            void arrayAppend( qlonglong value );

            /** Remove the value at position index from the array */
            void removeAt( int index );

            /**
             * Write the value and the array to the database.
             */
            void commit();

        private:
            class AbstractStatisticPrivate;
            AbstractStatisticPrivate* d;
    };
}

Q_DECLARE_METATYPE( GluonEngine::AbstractStatistic* )

#endif //GLUON_ENGINE_ABSTRACTSTATISTIC_H
