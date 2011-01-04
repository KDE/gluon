/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2008 Olivier Gueudelot <gueudelotolive@gmail.com>
 * Copyright (C) 2008 Charles Huet <packadal@gmail.com>
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

#ifndef GLUONGRAPHICS_ENGINE_H
#define GLUONGRAPHICS_ENGINE_H

#include "gluon_graphics_export.h"
#include <core/singleton.h>

namespace GluonGraphics
{
    class Camera;
    class Mesh;
    class Material;
    class Item;
    class Texture;
    class Viewport;

    /**
     * \brief Main entrypoint for working with Gluon Graphics.
     *
     * This class provides the main entry point for working with
     * classes from Gluon Graphics. It provides factory methods
     * for the most used objects in Gluon Graphics as well as providing
     * a registry of objects.
     *
     * This registry is used to render the current scene. For that, a
     * single render operation is provided. This render operation renders
     * the registered objects to a Framebuffer Object, which is then rendered
     * to a fullscreen quad by means of a post-processing shader.
     *
     * Note that this class is thread-safe.
     *
     */
    class GLUON_GRAPHICS_EXPORT Engine : public GluonCore::Singleton<Engine>
    {
            Q_OBJECT
        public:
            /**
             * Initialize the defaults.
             *
             * This will create a "default" material, mesh and texture to
             * be used as default.
             *
             * It should be called during the OpenGL initialization phase.
             */
            void initialize();

            /**
             * Create an Item.
             *
             * The item will be put into the internal registry of items and
             * should be removed by calling destroyItem().
             *
             * \param mesh The name of the mesh to attach to the new item.
             * If this mesh does not exist yet it will be created.
             *
             * \return The item just created.
             */
            Item* createItem( const QString& mesh );

            /**
             * Add an item.
             *
             * This will add the item to the internal registry.
             *
             * \param item The item to add.
             */
            void addItem( Item* item );

            /**
             * Destroy an item.
             *
             * This will remove the item from the internal registry and then
             * delete it.
             *
             * \param item The item to destroy.
             */
            void destroyItem( Item* item );

            /**
             * Create a Material.
             *
             * \param name The name of the material to create.
             *
             * \return A new material with name as name or an existing
             * material if name is equal to an existing material.
             */
            Material* createMaterial( const QString& name );

            /**
             * Destroy a material.
             *
             * The material will be removed and then deleted.
             * Note that if the material is not registered the call
             * is silently ignored.
             *
             * \param name The name of the material to destroy.
             */
            void destroyMaterial( const QString& name );

            /**
             * Check whether a material is registered.
             *
             * \param name The name of the material to check for.
             *
             * \return True if the material is registered, false if not.
             */
            bool hasMaterial( const QString& name );

            /**
             * Retrieve a registered material.
             *
             * \param name The name of the material to retrieve.
             *
             * \return The material requested or 0 if not found.
             */
            Material* material( const QString& name );

            /**
             * Add a material to the registry.
             *
             * \param name The name used to identify the material.
             * \param material The material to add.
             *
             * \return True if successful, false if not. False is also
             * returned when a material with the same name is already
             * registered.
             *
             */
            bool addMaterial( const QString& name, Material* material );

            /**
             * Remove a material from the registry.
             *
             * The material will be removed but not deleted.
             *
             * \param name The name of the material to remove.
             */
            void removeMaterial( const QString& name );

            /**
             * Create a Mesh.
             *
             * \param name The name of the mesh to create.
             *
             * \return A new mesh with name as name or an existing
             * mesh if name is equal to an existing mesh.
             */
            Mesh* createMesh( const QString& name );

            /**
             * Destroy a mesh.
             *
             * The mesh will be removed and then deleted.
             * Note that if the mesh is not registered the call
             * is silently ignored.
             *
             * \param name The name of the mesh to destroy.
             */
            void destroyMesh( const QString& name );

            /**
             * Check whether a mesh is registered.
             *
             * \param name The name of the mesh to check for.
             *
             * \return True if the mesh is registered, false if not.
             */
            bool hasMesh( const QString& name );

            /**
             * Retrieve a registered mesh.
             *
             * \param name The name of the mesh to retrieve.
             *
             * \return The mesh requested or 0 if not found.
             */
            Mesh* mesh( const QString& name );

            /**
             * Add a mesh to the registry.
             *
             * \param name The name used to identify the mesh.
             * \param mesh The mesh to add.
             *
             * \return True if successful, false if not. False is also
             * returned when a mesh with the same name is already registered.
             *
             */
            bool addMesh( const QString& name, Mesh* mesh );

            /**
             * Remove a mesh from the registry.
             *
             * The mesh will be removed but not deleted.
             *
             * \param name The name of the mesh to remove.
             */
            void removeMesh( const QString& name );

            /**
             * Create a Texture.
             *
             * \see GluonGraphics::Texture
             *
             * \param name The name of the texture to create.
             *
             * \return A new texture with name as name or an existing
             * texture if name is equal to an existing texture.
             */
            Texture* createTexture( const QString& name );

            /**
             * Destroy a texture.
             *
             * The texture will be removed and then deleted.
             * Note that if the texture is not registered the call
             * is silently ignored.
             *
             * \param name The name of the texture to destroy.
             */
            void destroyTexture( const QString& name );

            /**
             * Check whether a texture is registered.
             *
             * \param name The name of the texture to check for.
             *
             * \return True if the texture is registered, false if not.
             */
            bool hasTexture( const QString& name );

            /**
             * Retrieve a registered texture.
             *
             * \param name The name of the texture to retrieve.
             *
             * \return The texture requested or 0 if not found.
             */
            Texture* texture( const QString& name );

            /**
             * Add a texture to the registry.
             *
             * \param name The name used to identify the texture.
             * \param texture The texture to add.
             *
             * \return True if successful, false if not. False is also
             * returned when a texture with the same name is already
             * registered.
             *
             */
            bool addTexture( const QString& name, Texture* texture );

            /**
             * Remove a texture from the registry.
             *
             * The texture will be removed but not deleted.
             *
             * \param name The name of the texture to remove.
             */
            void removeTexture( const QString& name );

            /**
             * Retrieve the current active camera.
             *
             * \return The active camera, or 0 if no camera
             * has been set as active yet.
             */
            Camera* activeCamera();

            Viewport* currentViewport();

        public Q_SLOTS:
            /**
             * Render the current scene.
             *
             * This will render the currently visible scene.
             */
            void render();

            /**
             * Set the internal framebuffer size.
             *
             * This will rebuild the framebuffer used by this
             * class to a framebuffer with the specified size.
             * This should be called whenever the display widget
             * resizes, to keep the rendering correct.
             *
             * Note that when the current scene is being rendered
             * the framebuffer will be locked and this method will
             * wait until rendering has been completed.
             *
             * \param width The new width of the framebuffer.
             * \param height The new height of the framebuffer.
             */
            void setFramebufferSize( int width, int height );

            /**
             * Set the currently active camera.
             *
             * This camera will be used for rendering the scene.
             *
             * \param camera The camera to set as active camera.
             */
            void setActiveCamera( Camera* camera );

            void setViewport( Viewport* viewport );

        Q_SIGNALS:
            /**
             * Emitted whenever the active camera changes.
             */
            void activeCameraChanged( Camera* );

        private:
            friend class GluonCore::Singleton<Engine>;

            Engine();
            ~Engine();
            Q_DISABLE_COPY( Engine );

            class EnginePrivate;
            EnginePrivate* const d;
    };
} //namespace

#endif // GLUONGRAPHICS_ENGINE_H
