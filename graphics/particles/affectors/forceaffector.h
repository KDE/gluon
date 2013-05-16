/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Arjen Hiemstra <ahiemstra@heimr.nl>
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


#ifndef GLUONGRAPHICS_FORCEAFFECTOR_H
#define GLUONGRAPHICS_FORCEAFFECTOR_H

#include "../particleaffector.h"

class QVector3D;
namespace GluonGraphics
{
    class ForceAffector : public GluonGraphics::ParticleAffector
    {
        Q_OBJECT
        GLUON_OBJECT( ForceAffector )

        Q_PROPERTY( QVector3D force READ force WRITE setForce )
        Q_PROPERTY( float randomness READ randomness WRITE setRandomness )
        Q_PROPERTY( TransformSpace transformSpace READ transformSpace WRITE setTransformSpace )
        Q_PROPERTY( bool continuous READ isContinuous WRITE setContinuous )

        public:
            enum TransformSpace
            {
                Local,
                World
            };

            ForceAffector(QObject* parent = 0);
            virtual ~ForceAffector();

            virtual void affectParticle(Particle* particle, int time);

            QVector3D force() const;
            void setForce( const QVector3D& force );

            float randomness() const;
            void setRandomness( float random );

            TransformSpace transformSpace() const;
            void setTransformSpace( TransformSpace space );

            bool isContinuous() const;
            void setContinuous( bool continuous );

        private:
            class Private;
            const QScopedPointer< Private > d;
    };
}

#endif // GLUONGRAPHICS_FORCEAFFECTOR_H
