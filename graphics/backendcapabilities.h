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

#ifndef GLUONGRAPHICS_BACKENDCAPABILITIES_H
#define GLUONGRAPHICS_BACKENDCAPABILITIES_H

namespace GluonGraphics
{
    /**
     * \brief Class to retrieve information about the rendering backend.
     *
     * This class contains static methods that retrieve information about
     * the capabilities of the rendering backend.
     *
     */
    class BackendCapabilities
    {
        public:
            enum BackendType
            {
                BT_OPENGL,
                BT_OPENGLES,
            };

            /**
            * Query the backend type.
            *
            * This will return the type of the backend and can be used for
            * runtime introspection.
            *
            * \return The backend type.
            */
            static BackendType type();

            /**
            * The main backend version.
            *
            * This method will query the backend for it's version number. This
            * will then be converted to an integer to allow easy comparison.
            * The scheme used is hundreds are major version, tens are the minor
            * version and ones are the patch version.
            *
            * Note that the major version can extend beyond 9 where minor/patch
            * versions cannot.
            *
            * \return The backend version.
            */
            static int version();

            /**
            * The version of the shader language supported by the backend.
            *
            * This method will query the backend for the supported shader
            * language version. The scheme is the same as used by version().
            * It will return -1 if no shaders are supported.
            *
            * \return The shader language version.
            */
            static int shaderVersion();

        private:
            static int backendVersion;
            static int backendShaderVersion;
    };

}

#endif // GLUONGRAPHICS_BACKENDCAPABILITIES_H
