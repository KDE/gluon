/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Sacha Schutz <istdasklar@free.fr>
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

#include "textrenderercomponent.h"
#include <graphics/textitem.h>
#include <QMessageBox>
#include <gameobject.h>
#include <graphics/meshes/polygonmesh.h>
REGISTER_OBJECTTYPE(GluonEngine, TextRendererComponent)

using namespace GluonEngine;

class TextRendererComponent::TextRendererComponentPrivate
{
    public:
        TextRendererComponentPrivate()
        {
            textItem = 0;
            text = "empty";
        }

        QString text;
        QFont font;
        QColor color;
        GluonGraphics::TextItem * textItem;
};


TextRendererComponent::TextRendererComponent(QObject * parent)
    : Component(parent),
    d(new TextRendererComponentPrivate)
{
}

TextRendererComponent::~TextRendererComponent()
{
    delete d;
}

QString
TextRendererComponent::text() const
{
    return d->text;
}

void
TextRendererComponent::setText(const QString &text)
{
    d->text = text;
    if (d->textItem)
        d->textItem->setText(text);
}

QFont
TextRendererComponent::font() const
{
    return d->font;
}

void
TextRendererComponent::setFont(const QFont& font)
{
    d->font = font;
    if (d->textItem)
        d->textItem->setFont(font);
}

QColor
TextRendererComponent::color() const
{
    return d->color;
}

void
TextRendererComponent::setColor(const QColor& color)
{
    d->color = color;
    if (d->textItem)
        d->textItem->setColor(color);
}

void
TextRendererComponent::initialize()
{
    d->textItem = new GluonGraphics::TextItem(d->text, d->font);
}

void
TextRendererComponent::start()
{
    d->textItem->setColor(d->color);
}

void
TextRendererComponent::draw(int timeLapse)
{
    if (d->textItem)
        d->textItem->setMatrix(gameObject()->transform());
}

void 
TextRendererComponent::cleanup()
{
    delete d->textItem;
    d->textItem = 0;
}

Q_EXPORT_PLUGIN2(gluon_component_textrenderer, GluonEngine::TextRendererComponent);

#include "textrenderercomponent.moc"
