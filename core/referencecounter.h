/*****************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#ifndef GLUON_CORE_REFERENCECOUNTER_H
#define GLUON_CORE_REFERENCECOUNTER_H

#include "gluoncore_export.h"

#include <QtCore/QAtomicInt>

namespace GluonCore
{
    /**
     * \brief A simple explicit reference counting class.
     *
     * This class provides simple reference counting. It
     * does not use any specific pointer type to manage
     * reference counting, instead relying upon the user
     * of this class to increase and decrease the references
     * where necessary. It is mostly intended for situations
     * where you want to check whether it is safe to delete
     * something but do not want the burden of using non-
     * standard pointer classes.
     *
     * This class does not do any deletion when count() == 0 or
     * other "magic". It is purely intended for keeping track of
     * uses of an instance of an object.
     */
    class GLUONCORE_EXPORT ReferenceCounter
    {
        public:
            ReferenceCounter();

            /**
             * Increase the number of references by one.
             */
            void ref();
            /**
             * Decrease the number of references by one.
             */
            void deref();
            /**
             * Retrieve the number of references.
             */
            int count() const;

        private:
            QAtomicInt m_ref;
    };
}

#endif // GLUON_CORE_REFERENCECOUNTER_H
