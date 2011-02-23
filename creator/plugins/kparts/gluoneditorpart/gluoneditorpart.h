/*
*****************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (c) 2011 Laszlo Papp <djszapi@archlinux.us>
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

#ifndef GLUONVIEWERPART_H
#define GLUONVIEWERPART_H

#include <KDE/KParts/ReadWritePart>

namespace GluonGraphics
{
    class Viewport;
}

using namespace GluonGraphics;

namespace GluonCreator
{
    class GluonEditorPart : public KParts::ReadWritePart
    {
            Q_OBJECT
        public:
            GluonEditorPart( QWidget* parentWidget, QObject* parent, const QVariantList& args );
            virtual ~GluonEditorPart();

            bool saveFile() {return true;};

        public slots:
            void startGame();

            void setSolid();
            void setWireframe();
            void setPoints();

            void newViewport( Viewport* viewport );
            void redraw();

        protected:
            virtual bool openFile();

        private:
            class GluonEditorPartPrivate;
            GluonEditorPartPrivate* const d;
    };
}

#endif // GLUONVIEWERPART_H
