/*
    <one line to give the library's name and an idea of what it does.>
    Copyright (C) <year>  <name of author>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/


#include "models.h"
#include "componentmodel.h"
#include "projectmodel.h"
#include "scenemodel.h"

using namespace GluonCreator;

class Models::Private
{
public:
    Private()
        : componentModel(0)
        , projectModel(0)
        , sceneModel(0)
    {
    }
    
    
    ComponentModel* componentModel;
    ProjectModel* projectModel;
    SceneModel* sceneModel;
};

template<> GLUON_CREATOR_VISIBILITY Models* GluonCore::Singleton<Models>::m_instance = 0;

Models::Models()
    : d(new Private)
{
}


Models::Models(const GluonCreator::Models& )
    : Singleton< GluonCreator::Models >()
    , d(new Private)
{

}

Models::~Models()
{
    delete(d);
}

ComponentModel* GluonCreator::Models::componentModel()
{
    if(!d->componentModel)
        d->componentModel = new ComponentModel(this);
    return d->componentModel;
}

ProjectModel* GluonCreator::Models::projectModel()
{
    if(!d->projectModel)
        d->projectModel = new ProjectModel(this);
    return d->projectModel;
}

SceneModel* GluonCreator::Models::sceneModel()
{
    if(!d->sceneModel)
        d->sceneModel = new SceneModel(this);
    return d->sceneModel;
}
