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

#include "material.h"

REGISTER_OBJECTTYPE(GluonGraphics, Material)

using namespace GluonGraphics;

class Material::MaterialPrivate
{
    public:
        
};

Material::Material(QObject* parent)
    : GluonObject(parent),
      d(new MaterialPrivate)
{

}

Material::~Material()
{
    delete d;
}

Technique* Material::technique(const QString& name) const
{

}

Technique* Material::defaultTechnique() const
{

}

void Material::addTechnique(Technique* technique)
{

}

void Material::removeTechnique(const QString& name)
{

}

void Material::setDefaultTechnique(const QString& name)
{

}

#include "material.moc"