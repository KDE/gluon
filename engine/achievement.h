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

#ifndef GLUON_ENGINE_ACHIEVEMENT_H
#define GLUON_ENGINE_ACHIEVEMENT_H

#include <engine/gluon_engine_export.h>

#include <core/gluonobject.h>
#include <core/referencecounter.h>

namespace GluonEngine
{
    class AbstractStatistic;
    class TextureAsset;

    /**
     * The Achievement class is connected to one statistic. If the statistic reaches a
     * certain score, achieved() returns true.
     */
    class GLUON_ENGINE_EXPORT Achievement : public GluonCore::GluonObject, public GluonCore::ReferenceCounter
    {
            Q_OBJECT
            GLUON_OBJECT( GluonEngine::Achievement )

            /**
             * The statistic the achievement is connected to
             */
            Q_PROPERTY( GluonEngine::AbstractStatistic* statistic READ statistic WRITE setStatistic )

            /**
             * The score you need to get the achievement
             */
            Q_PROPERTY( qlonglong minimumScore READ minimumScore WRITE setMinimumScore )

            /**
             * An icon that represents the achievemnt.
             */
            Q_PROPERTY( GluonEngine::TextureAsset* icon READ icon WRITE setIcon );
        public:
            Q_INVOKABLE Achievement( QObject* parent = 0 );
            virtual ~Achievement();

            AbstractStatistic* statistic() const;
            void setStatistic( AbstractStatistic* statistic );

            qlonglong minimumScore() const;
            void setMinimumScore( qlonglong score );

            TextureAsset* icon();
            void setIcon( TextureAsset* icon );

            /** What current store does the user have? */
            qlonglong currentScore();

            /** Has the statistic achieved the goal? */
            bool achieved() const;

        private:
            class AchievementPrivate;
            AchievementPrivate* d;
    };
}

Q_DECLARE_METATYPE( GluonEngine::Achievement* )

#endif //GLUON_ENGINE_ACHIEVEMENT_H
