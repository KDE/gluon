/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2009 Dan Leinir Turthra Jensen <admin@leinir.dk>
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

#ifndef GLUON_CORE_METAINFO_H
#define GLUON_CORE_METAINFO_H

#include "gluon_core_export.h"

#include <QtCore/QObject>

namespace GluonCore
{
    class GluonObject;
    class GLUON_CORE_EXPORT MetaInfo : public QObject
    {
            Q_OBJECT
        public:
            MetaInfo( GluonObject* parent );
            MetaInfo( const MetaInfo& other );
            virtual ~MetaInfo();

            /**
             * Set a range for the named property, from a minimum and maximum range, both inclusive
             * @param property The name of the property to set a range for
             * @param min The minimum allowed value for the property
             * @param max The maximum allowed value for the property
             */
            Q_INVOKABLE void setPropertyRange( const QString& property, qreal min, qreal max );

            /**
             * Whether a range has been set for the named property
             * @param property The name of the property to check
             * @return Whether a range has been set for the property
             */
            Q_INVOKABLE bool hasPropertyRange( const QString& property ) const;

            /**
             * The minimum value allowed for the property.
             * Note: If the property does not have a range set, this will return 0
             * @param property The name of the property to fetch the minimum value for
             * @return The minimum allowed value for the property
             */
            Q_INVOKABLE qreal propertyRangeMin( const QString& property ) const;

            /**
            * The maximum value allowed for the property.
            * Note: If the property does not have a range set, this will return 0
            * @param property The name of the property to fetch the maximum value for
            * @return The maximum allowed value for the property
            */
            Q_INVOKABLE qreal propertyRangeMax( const QString& property ) const;

            /**
             * Remove the range for the property
             * @param property The property to remove the range values for
             */
            Q_INVOKABLE void removePropertyRange( const QString& property );

            /**
             * Cap the passed value to the range for the given property, if it is set. If
             * no range exists, the value is returned without change.
             * @param property The property to apply the range for
             * @param newValue The value which should be capped
             * @return The capped value
             * @see applyRangeAndStep() applyStep()
             */
            Q_INVOKABLE qreal applyRange( const QString& property, qreal newValue ) const;

            /**
             * Set the number of steps the property's range should be separated into.
             * @param property The property to set steps for
             * @param step The number of steps steps
             */
            Q_INVOKABLE void setPropertySteps( const QString& property, quint32 steps );

            /**
             * Whether a step has been set for the named property
             * @param property The name of the property to check
             * @return Whether a step value is defined
             */
            Q_INVOKABLE bool hasPropertySteps( const QString& property ) const;

            /**
             * The number of steps the property is separated into
             * If no value is set, this function will return 0
             * @param property The property in question
             * @return The number of steps for the named property
             */
            Q_INVOKABLE quint32 propertySteps( const QString& property ) const;

            /**
             * Remove the step value set for the named property
             * @param property The property to remove the steps for
             */
            Q_INVOKABLE void removePropertySteps( const QString& property );

            /**
             * Round off the given value to the nearest step for the named property
             * If no value has been set, the value will be returned with no change
             * @param property The property to apply steps for
             * @param newValue The value to adjust
             * @return The adjusted value
             * @see applyRangeAndStep() applyRange()
             */
            Q_INVOKABLE qreal applySteps( const QString& property, qreal newValue ) const;

            /**
             * Cap the new value to the range for the given property, and round it off
             * to the nearest step. The rules for applying both are as given in the
             * functions for applying range and step separately
             * @param property The property to apply range and step for
             * @param newValue The value to cap and step
             * @return The adjusted value
             * @see applyRange() applyStep()
             */
            Q_INVOKABLE qreal applyRangeAndStep( const QString& property, qreal newValue ) const;

            /**
             * Return the default extension to be used for this object type, when it is
             * saved to a file. This is primarily used by GluonEngine::Savable to determine
             * the extension to use when saving files to disk.
             *
             * \return The default extension or an empty string if none has  been set.
             */
            QString defaultExtension() const;

            /**
             * Set the default extension for this object type.
             *
             * \see defaultExtension()
             *
             * \param extension The default extension to use.
             */
            void setDefaultExtension( const QString& extension );

        private:
            class MetaInfoPrivate;
            MetaInfoPrivate* d;
    };
}

#endif // GLUON_CORE_METAINFO_H
