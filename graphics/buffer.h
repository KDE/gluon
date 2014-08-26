/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2012 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#ifndef GLUONGRAPHICS_BUFFER_H
#define GLUONGRAPHICS_BUFFER_H

#include <QVariant>

namespace GluonGraphics
{
    /**
     * Abstract class for handling hardware buffers.
     *
     * The buffer class abstracts a hardware buffer, like an OpenGL Vertex Buffer Object. This
     * class only provides the interface that should be implemented by the backend. Buffers
     * should be created through the Backend class,
     */
    class Buffer
    {
        public:
            /**
             * A hint to the backend to what kind of usage this buffer will have.
             */
            enum UpdateMode
            {
                Static, ///< Buffer is used to upload static content that does not change often.
                Dynamic ///< Buffer is used to upload content that changes often, like dynamic meshes.
            };

            /**
             * The type of buffer to create.
             *
             * Use isValid() after a call to initialize() to check whether the backend provided a
             * usable buffer. In addition, the method isBufferTypeSupported() can be used to query
             * the backend to see if a certain type of buffer is available.
             */
            enum BufferType
            {
                Vertex, ///< Buffer is used to store vertex data, like positions and UV coordinates.
                Index, ///< Buffer is used to store face indexes.
                PixelUpload, ///< Buffer is used to upload pixel data to the GPU.
                PixelDownload, ///< Buffer is used to download pixel data from the GPU.
                Uniform ///< Buffer is used to store a set of uniform values.
            };

            Buffer() { }
            virtual ~Buffer() { }

            /**
             * Initialize the buffer.
             *
             * This will create the actual, in memory buffer object.
             *
             * If the given type of buffer is not available, this will do nothing.
             *
             * \param type The type of buffer to create.
             * \param mode The update mode of the buffer.
             */
            virtual void initialize( BufferType type, UpdateMode mode ) = 0;
            /**
             * Destroy the buffer.
             *
             * This will destroy the in-memory buffer object and release all resources associated
             * with that buffer.
             *
             * If the buffer is not valid, this will do nothing.
             */
            virtual void destroy() = 0;
            /**
             * Pre-allocate a size for the buffer.
             *
             * This will allocate size bytes for this buffer. The data in the buffer will be random
             * and it should not be used before writing actual data to the buffer. However, this will
             * prevent multiple resizes of the buffer when writing data.
             *
             * If the buffer is not valid, this will do nothing.
             *
             * \param size The size to pre-allocate.
             */
            virtual void setSize( int size ) = 0;
            /**
             * Set the buffer from offset with data until size is reached.
             *
             * This will copy the data from data into the buffer, starting from offset
             * and copying at most size bytes.
             *
             * If the buffer is not valid, this will do nothing.
             *
             * \param data An array of data to copy into the buffer.
             * \param size The amount of data to copy.
             * \param offset The position within the buffer where the copying should start.
             */
            virtual void setData( void* data, int size, int offset = 0 ) = 0;
            /**
             * Bind the buffer so it can be used.
             *
             * Depending on the backend, this will bind the buffer to the appropriate slot so other
             * things can use the data.
             *
             * If the buffer is not valid, this will do nothing.
             *
             * \note bind() may be called multiple times. The implementation should keep track of how
             * often bind() was called and only perform release() when the last bind is released.
             */
            virtual void bind() = 0;
            /**
             * Release the buffer.
             *
             * Depending on the backend, this will release the buffer from the appropriate slot.
             *
             * If the buffer is not valid, this will do nothing.
             */
            virtual void release() = 0;
    };

}

#endif // GLUONGRAPHICS_BUFFER_H
