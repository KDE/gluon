/******************************************************************************
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

#ifndef GLUON_CREATOR_CODEWIDGETKPART_H
#define GLUON_CREATOR_CODEWIDGETKPART_H

#include <kparts/part.h>
#include <kparts/factory.h>

#include "nodeeditor/interface/NodeEditor.h"

namespace GluonCreator
{

    class CodeWidgetKpart : public KParts::ReadWritePart
    {
            Q_OBJECT
            /**
            * \brief KPart interface for Code Editor
             * Creates main interface MainWindow for KPart.
             * \todo Give explainations of choices/design.
             */
        public:
            CodeWidgetKpart( QWidget* parentWidget, QObject* parent, const QVariantList& );
            NodeEditor* MainWidget()
            {
                return main;
            };
            virtual ~CodeWidgetKpart();
            bool openFile()
            {
                return true;
            };
            bool saveFile()
            {
                return true;
            };

        private:
            NodeEditor* main;
    };

}

#endif // GLUON_CREATOR_CODEWIDGETKPART_H
