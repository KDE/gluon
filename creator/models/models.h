/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Dan Leinir Turthra Jensen <admin@leinir.dk>
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

#ifndef GLUONCREATOR_MODELS_H
#define GLUONCREATOR_MODELS_H

#include "gluoncreator_macros.h"

#include <core/singleton.h>

namespace GluonCreator
{
    class ComponentModel;
    class ProjectModel;
    class SceneModel;
    class GLUONCREATOR_EXPORT Models : public GluonCore::Singleton<Models>
    {
            Q_OBJECT
            GLUON_SINGLETON( Models )
        public:
            SceneModel* sceneModel();
            ProjectModel* projectModel();
            ComponentModel* componentModel();

        private:
            ~Models();

            class Private;
            Private* const d;
    };
}

#endif // GLUONCREATOR_MODELS_H
