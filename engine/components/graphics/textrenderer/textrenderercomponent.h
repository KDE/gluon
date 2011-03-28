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

#ifndef TEXTRENDERERCOMPONENT_H
#define TEXTRENDERERCOMPONENT_H

#include <engine/component.h>

#include <QtGui/QFont>
#include <QtGui/QColor>

namespace GluonEngine
{
    class GLUON_COMPONENT_TEXTRENDERER_EXPORT TextRendererComponent : public Component
    {
            Q_OBJECT
            GLUON_OBJECT( GluonEngine::TextRendererComponent )
            Q_PROPERTY( QString text READ text WRITE setText )
            Q_PROPERTY( QFont font READ font WRITE setFont )
            Q_PROPERTY( QColor color READ color WRITE setColor )
            Q_INTERFACES( GluonEngine::Component )

        public:
            Q_INVOKABLE TextRendererComponent( QObject* parent = 0 );
            ~TextRendererComponent();
            virtual QString category() const;

            virtual QString text() const;
            virtual QFont font() const;
            virtual QColor color() const;

            virtual void initialize();
            virtual void start();
            virtual void draw( int timeLapse );
            virtual void cleanup();

        public slots:
            virtual void setText( const QString& text );
            virtual void setFont( const QFont& font );
            virtual void setColor( const QColor& color );

        private:
            class TextRendererComponentPrivate;
            TextRendererComponentPrivate* const d;
    };
}

Q_DECLARE_METATYPE( GluonEngine::TextRendererComponent* )

#endif // TEXTRENDERERCOMPONENT_H
