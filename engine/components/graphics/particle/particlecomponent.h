/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Laszlo Papp <djszapi@archlinux.us>
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

#ifndef GLUON_ENGINE_PARTICLE_H
#define GLUON_ENGINE_PARTICLE_H

#include <engine/gluon_engine_export.h>
#include <engine/component.h>

class QSizeF;
namespace GluonGraphics
{
    class MaterialInstance;
}

namespace GluonEngine
{
    class Asset;

    class GLUON_COMPONENT_PARTICLERENDERER_EXPORT ParticleRendererComponent : public Component
    {
            Q_OBJECT
            GLUON_OBJECT( GluonEngine::ParticleRendererComponent )
            Q_INTERFACES( GluonEngine::Component )


            // RENDERING PROPERTIES
            Q_PROPERTY( bool castShadows READ castShadows WRITE setCastShadows )

            Q_PROPERTY( bool receiveShadows READ receiveShadows WRITE setReceiveShadows )

            Q_PROPERTY( QSizeF size READ size WRITE setSize )

            // Reference to a list of Materials that will be displayed in the position of each individual particle.
            Q_PROPERTY( GluonGraphics::MaterialInstance* material READ material WRITE setMaterial )

            // The amount of stretching that is applied to the Particles based on
            // Camera movement.
            Q_PROPERTY( int cameraVelocityScale READ cameraVelocityScale WRITE setCameraVelocityScale )

            // Determines how the particles are rendered.
            Q_PROPERTY( StretchParticles stretchParticles READ stretchParticles WRITE setStretchParticles )

            // If Stretch Particles is set to Stretched, this value determines
            // how long the particles are in their direction of motion.
            Q_PROPERTY( int lengthScale READ lengthScale WRITE setLengthScale )

            // If Stretch Particles is set to Stretched, this value determines
            // the rate at which particles will be stretched, based on their
            // movement speed.
            Q_PROPERTY( int velocityScale READ velocityScale WRITE setVelocityScale )

            // Number of frames located across the X axis.
            Q_PROPERTY( int uvAnimationXTile READ uvAnimationXTile WRITE setUVAnimationXTile )

            // Number of frames located across the Y axis.
            Q_PROPERTY( int uvAnimationYTile READ uvAnimationYTile WRITE setUVAnimationYTile )

            // How many times to loop the animation sequence.
            Q_PROPERTY( int uvAnimationCycles READ uvAnimationCycles WRITE setUVAnimationCycles )




            // ANIMATOR PROPERTIES

            // If enabled, particles cycle their color over their lifetime.
            Q_PROPERTY( bool doesAnimateColor READ doesAnimateColor WRITE setDoesAnimateColor )

            // The 5 colors particles go through. All particles cycle over this
            // - if some have a shorter life span than others, they will animate
            // faster.
            Q_PROPERTY( QList<QColor> colorAnimation READ colorAnimation WRITE setColorAnimation )

            // An optional world-space axis the particles rotate around. Use
            // this to make advanced spell effects or give caustic bubbles some
            // life.
            Q_PROPERTY( int worldRotationAxis READ worldRotationAxis WRITE setWorldRotationAxis )

            // An optional local-space axis the particles rotate around. Use
            // this to make advanced spell effects or give caustic bubbles some
            // life.
            Q_PROPERTY( int localRotationAxis READ localRotationAxis WRITE setLocalRotationAxis )

            //  Use this to make particles grow in size over their lifetime. As
            //  randomized forces will spread your particles out, it is often
            //  nice to make them grow in size so they don't fall apart. Use
            //  this to make smoke rise upwards, to simulate wind, etc.
            Q_PROPERTY( int sizeGrow READ sizeGRow WRITE setSizeGrow )

            // A random force added to particles every frame. Use this to make
            // smoke become more alive.
            Q_PROPERTY( int rndForce READ rndForce WRITE setRndForce )

            // The force being applied every frame to the particles, measure
            // relative to the world.
            Q_PROPERTY( int force READ force WRITE setForce )

            // How much particles are slowed every frame. A value of 1 gives no
            // damping, while less makes them slow down.
            Q_PROPERTY( int damping READ damping WRITE setDamping )

            // If enabled, the GameObject attached to the Particle Animator will be destroyed when all particles disappear.
            Q_PROPERTY( bool autoDesctruct READ autoDescruct WRITE setAutoDestruct )



            // ELLIPSOID/MESH EMITTER PROPERTIES

            // If enabled, the emitter will emit particles.
            Q_PROPERTY( bool emit READ emit WRITE setEmit )

            // The minimum size each particle can be at the time when it is
            // spawned.
            Q_PROPERTY( int minSize READ minSize WRITE setMinSize )

            // The maximum size each particle can be at the time when it is
            // spawned.
            Q_PROPERTY( int maxSize READ maxSize WRITE setMaxSize )

            // The minimum lifetime of each particle, measured in seconds.
            Q_PROPERTY( int minEnergy READ minEnergy WRITE setMinEnergy )

            // The maximum lifetime of each particle, measured in seconds.
            Q_PROPERTY( int maxEnergy READ maxEnergy WRITE setMaxEnergy )

            // The minimum number of particles that will be spawned every
            // second.
            Q_PROPERTY( int minEmission READ minEmission WRITE setMinEmission )

            // The maximum number of particles that will be spawned every
            // second.
            Q_PROPERTY( int maxEmission READ minEmission WRITE setMaxEmission )

            // The starting speed of particles in world space, along X, Y, and
            // Z.
            Q_PROPERTY( int worldVelocity READ worldVelocity WRITE setWorldVelocity )

            // The starting speed of particles along X, Y, and Z, measured in
            // the object's orientation.
            Q_PROPERTY( int localVelocity READ localVelocity WRITE setLocalVelocity )

            // A random speed along X, Y, and Z that is added to the velocity.
            Q_PROPERTY( int rndVelocity READ rndVelocity WRITE setRndVelocity )

            // The amount of the emitter's speed that the particles inherit.
            Q_PROPERTY( int emitterVelocityScale READ emitterVelocityScale WRITE setEmitterVelocityScale )

            // The starting speed of particles along X, Y, and Z, across the
            // Emitter's surface.
            Q_PROPERTY( int tangentVelocity READ tangentVelocity WRITE setTangentVelocity )

            // If enabled, the particles don't move when the emitter moves. If
            // false, when you move the emitter, the particles follow it around.
            Q_PROPERTY( bool simulateInWorldSpace READ simulateInWorldSpace WRITE setSimulateInWorldSpace )

            // If enabled, the particle numbers specified by min & max emission
            // is spawned all at once. If disabled, the particles are generated
            // in a long stream.
            Q_PROPERTY( bool oneShot READ oneShot WRITE setOneShot )

            //-----------------------------------------------------------------------------------
            // ELLIPSOID

            // Scale of the sphere along X, Y, and Z that the particles are
            // spawned inside.
            Q_PROPERTY( int ellipsoid READ ellipsoid WRITE setEllipsoid )

            // Determines an empty area in the center of the sphere - use this
            // to make particles appear on the edge of the sphere.
            Q_PROPERTY( int minEmitterRange READ minEmitterRange WRITE setMinEmitterRange )

            //------------------------------------------------------------------------------------
            // MESH

            // If enabled, particles are spawned all over the mesh's surface. If
            // disabled, particles are only spawned from the mesh's vertrices.
            Q_PROPERTY( bool interpolateTriangles READ interpolateTriangles )



        public:
            enum StretchParticles {
                // The particles are rendered as if facing the camera.
                Billboard,
                // The particles are facing the direction they are moving.
                Stretched,
                // The particles are sorted by depth. Use this when using a
                // blending material.
                SortedBillboard,
                // All particles are aligned flat along the X/Z axes.
                VerticalBillboard,
                // All particles are aligned flat along the X/Y axes.
                HorizontalBillboard,
            };

            Q_INVOKABLE ParticleRendererComponent( QObject* parent = 0 );
            ~ParticleRendererComponent();

            QString category() const;

            void initialize();
            void start();
            void update ( int elapsedMilliseconds );
            void draw( int timeLapse = 0 );
            void cleanup();


            // Render getter
            GluonGraphics::MaterialInstance* material();
            bool castShadows();
            bool receiveShadows();
            QSizeF size();
            GluonGraphics::MaterialInstance* material();
            int cameraVelocityScale();
            StretchParticles stretchParticles();
            int lengthScale();
            int velocityScale();
            int uvAnimationXTile();
            int uvAnimationYTile();
            int uvAnimationCycles();


            // Animator getter
            bool doesAnimateColor() const;
            QList<QColor> colorAnimation() const;
            int worldRotationAxis() const;
            int localRotationAxis() const;
            int sizeGrow() const;
            int rndForce() const;
            int force() const;
            int damping() const;
            bool autoDesctruct() const;



            // Ellipsoid emitter getter



            // Mesh emitter getter

        public slots:


            // Render setter
            void setCastShadows( bool castShadows );
            void setReceiveShadows( bool receiveShadows );
            void setSize( const QSizeF& size );
            void setMaterial( GluonGraphics::MaterialInstance* material );
            void setMaterial( const QString& path );
            void setCameraVelocity( int cameraVelocity );
            void setStretchParticles( StretchParticles stretchParticles );
            void setLengthScale( int lengthScale );
            void setVelocityScale( int velocityScale );
            void setUVAnimationXTile( int uvAnimationXTile );
            void setUVAnimationYTile( int uvAnimationYTile );
            void setUVAnimationCycle( int uvAnimationCycles );


            // Animator setter
            void setDoesAnimateColor(bool doesAnimateColor) const;
            void colorAnimation(QList<QColor> colorAnimation) const;
            void worldRotationAxis(int worldRotationAxis) const;
            void localRotationAxis(int localRotationAxis) const;
            void sizeGrow(int sizeGrow) const;
            void rndForce(int rndForce) const;
            void force(int force) const;
            void damping(int damping) const;
            void autoDesctruct(bool autoDestruct) const;


            // Elipsoid emitter setter



            // Mesh emitter setter


        private:
            class Private;
            Private* const d;
    };

}

Q_DECLARE_METATYPE( GluonEngine::ParticleComponent )
Q_DECLARE_METATYPE( GluonEngine::ParticleComponent* )

#endif // GLUON_ENGINE_PARTICLE_H
