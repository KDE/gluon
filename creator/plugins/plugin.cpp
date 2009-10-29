/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "plugin.h"

using namespace Gluon::Creator;

class Gluon::Creator::Plugin::PluginPrivate : public QSharedData
{
    public:
        QString name;
        QString description;
        PluginCapabilities capabilities;
};

Gluon::Creator::Plugin::Plugin(QObject* parent)
    : QObject(parent),
    d(new PluginPrivate)
{

}

Gluon::Creator::Plugin::~Plugin()
{
}


QString Gluon::Creator::Plugin::name()
{
    return d->name;
}

QString Gluon::Creator::Plugin::description()
{
    return d->description;
}

Gluon::Creator::Plugin::PluginCapabilities Gluon::Creator::Plugin::capabilities()
{
    return d->capabilities;
}

void Gluon::Creator::Plugin::setCapabilities(const Gluon::Creator::Plugin::PluginCapabilities& capabilities)
{
    d->capabilities = capabilities;
}

void Gluon::Creator::Plugin::setDescription(const QString& description)
{
    d->description = description;
}

void Gluon::Creator::Plugin::setName(const QString& name)
{
    d->name = name;
}
