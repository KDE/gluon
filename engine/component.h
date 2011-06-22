/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (C) 2010 Dan Leinir Turthra Jensen <admin@leinir.dk>
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

#ifndef GLUON_ENGINE_COMPONENT_H
#define GLUON_ENGINE_COMPONENT_H

#include "gluon_engine_export.h"

#include <core/gluonobject.h>

#include <QtPlugin>

/**
 * \defgroup Component Component
 */

namespace GluonEngine
{
    class GameObject;
    class ComponentPrivate;

    /**
     * \brief Adds functionality to GameObjects, is the final level in the GameObject hierarchy
     *
     * Component is a class which defines the required functionality for
     * implementing components for use with Gluon. A component is the place
     * where the vast majority of logic found in GluonEngine games exist. The six
     * most important functions for users are the virtual initialize(), start(),
     * update(), draw(), stop() and cleanup() functions. This class is the final
     * step in the GameObject hierarchy.
     *
     * Since a component is attached to exactly one GameObject, the position in
     * the world and anything else related to the GameObject can be found by
     * accessing gameObject() (for example finding other Components and such)
     *
     * Implementation checklist:
     * - Inherit from GluonEngine::Component
     * - Add the necessary macros as described in the GluonCore::GluonObject
     *   documentation
     * - Implement using QSharedData since GameObjects can be duplicated
     *   and the Components attached to it get duplicated along with it
     *   http://doc.trolltech.com/qshareddata.html
     * - Expose any properties to be visible in the editor through Q_PROPERTY
     */
    class GLUON_ENGINE_EXPORT Component : public GluonCore::GluonObject
    {
            Q_OBJECT
            /**
             * The description of the Component instance. An arbitrary value
             * used to tell other members of the game development team what the
             * Component is used for.
             */
            Q_PROPERTY( QString description READ description WRITE setDescription )
            /**
             * Whether or not the Component is enabled for use by the
             * GameObject it is contained within.
             */
            Q_PROPERTY( bool enabled READ enabled WRITE setEnabled )
            // gameObject is deliberately not a Q_PROPERTY - it is not supposed to be exposed in the editor other than through drag-and-drop

        public:
            Q_INVOKABLE Component( QObject* parent = 0 );
            virtual ~Component();

            /**
            * Return the category of the component. Meta-data used for filtering
            * and sorting components
            */
            virtual QString category() const;

            /**
            * If you wish to be able to use your objects as properties, make sure
            * to implement this function to return a QVariant which is of the type
            * of your class.
            */
            virtual QVariant toVariant( GluonObject* wrapThis );

            /**
             * The initialize function is called whenever an initialized object
             * is needed. This includes scene changes.
             */
            virtual void initialize() {}
            /**
             * The start function is run once after each scene change,
             * immediately before the first update
             * @see Game::setCurrentScene, update
             */
            virtual void start() {};
            /**
             * The update function is run each time the game logic needs to be
             * updated. Implement this function in inherited classed to allow
             * for updates along with the rest of the GameObject hierarchy.
             * Note that this is only for updating the game logic - any drawing
             * functionality should be put into the draw function.
             * @param elapsedMilliseconds The amount of time in milliseconds which has passed since the last update
             * @see Game::runGame, draw
             */
            virtual void update( int elapsedMilliseconds );
            /**
             * The draw function is run every time the engine requests a redraw
             * of the screen. Avoid putting any game logic in this function.
             * The optional timeLapse depends on gameloop being used. By
             * default Gluon uses a gameloop which runs update a fixed number
             * of times per second, while draw is called as often as it can be.
             * The timeLapse parameter then tells you how many milliseconds
             * have passed since the last time update was run. This allows you
             * to extrapolate draw positions of items and thus create a
             * potentially smoother gaming experience.
             * @param timeLapse The number of milliseconds passed since the last update
             * @see Game::runGame, update
             */
            virtual void draw( int timeLapse = 0 );

            /**
             * The stop function is run once when the gameloop is stopped.
             * Use it for removing temporary data between runs. Reimplement
             * this function if you have something that needs cleaning up
             * between runs.
             */
            virtual void stop() {};

            /**
             * The cleanup function is called whenever an object is no longer
             * needed. This happens mostly during scene changes.
             */
            virtual void cleanup() {}

            /**
             * The description of the Component instance. An arbitrary value
             * used to tell other members of the game development team what the
             * Component is used for.
             * @return The description of the Component instance
             * @see setDescription
             */
            QString description() const;
            /**
             * Set the description of the Component
             * @param newDescription The new description
             */
            void setDescription( const QString& newDescription );

            /**
             * Whether or not the Component is enabled for use by the
             * GameObject it is contained within.
             * @return True if the Component is enabled, false if not
             * @see setEnabled
             */
            bool enabled() const;
            /**
             * Set the enabled parameter of the Component instance
             * @param newEnabled The new value for the parameter
             * @see enabled
             */
            void setEnabled( bool newEnabled );

            /**
             * Returns a pointer to the GameObject instance this instance of
             * the Component is attached to. Use this for example to get the
             * position or rotation relevant to the Component, or any other
             * functionality found on GameObject (such as finding other
             * Components)
             * @return A pointer to the GameObject instance this Component is attached to
             * @see setGameObject, GameObject
             */
            GameObject* gameObject();
            /**
             * Move this Component to another GameObject. Please note that this
             * will remove the Component from its current GameObject!
             * @param newGameObject The GameObject instance to move this Component onto
             * @see gameObject, GameObject
             */
            void setGameObject( GameObject* newGameObject );

            /**
             * Function used on instantiation to fix the parent/child relationship.
             * Used specifically by GDLHandler in the parseGDL() function. If you do
             * not work on GDLHandler, it is unlikely you will need this function.
             * @see GDLHandler::parseGDL
             */
            void sanitize();

            /**
             * Adapted function which special cases access to properties with the
             * type GluonEngine::Asset* - used by GDLHandler.
             *
             * @param   propertyName    The name of the property you wish to get in GDL property string form
             * @param   indentChars     The characters used for indenting the string
             * @return  The GDL representation of the property
             */
            virtual QString stringFromProperty( const QString& propertyName, const QString& indentChars ) const;

        private:
            ComponentPrivate* const d;
    };
}

Q_DECLARE_INTERFACE( GluonEngine::Component, "com.gluon.Component/1.0" )
Q_DECLARE_METATYPE( GluonEngine::Component* )

#endif  // GLUON_COMPONENT_H
