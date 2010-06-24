/******************************************************************************
 * This file is part of the Gluon Development Platform
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

#include "scriptingcomponent.h"
#include "scriptingcomponentprivate.h"

REGISTER_OBJECTTYPE(GluonEngine, ScriptingComponent)

using namespace GluonEngine;

ScriptingComponent::ScriptingComponent(QObject* parent)
    : Component(parent)
    , d(new ScriptingComponentPrivate)
{
}

ScriptingComponent::ScriptingComponent(const ScriptingComponent& other)
    : d(other.d)
{
}

ScriptingComponent::~ScriptingComponent()
{
    delete(d);
}

QString
ScriptingComponent::category() const
{
    return QString("Other");
}

void ScriptingComponent::initialize()
{
    GluonEngine::Component::initialize();
}

void ScriptingComponent::start()
{
    GluonEngine::Component::start();
}

void ScriptingComponent::update(int elapsedMilliseconds)
{
    GluonEngine::Component::update(elapsedMilliseconds);
}

void ScriptingComponent::draw(int timeLapse)
{
    GluonEngine::Component::draw();
}

void ScriptingComponent::stop()
{
    GluonEngine::Component::stop();
}

void ScriptingComponent::cleanup()
{
    GluonEngine::Component::cleanup();
}

#include "scriptingcomponent.moc"
