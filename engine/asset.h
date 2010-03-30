/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Arjen Hiemstra <>
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

#ifndef GLUON_ENGINE_ASSET_H
#define GLUON_ENGINE_ASSET_H

#include "core/gluonobject.h"

#include "gluon_engine_export.h"

#include <QtCore/QUrl>
#include <QtCore/QSharedData>
#include <QtPlugin>

class QMimeData;

namespace GluonEngine
{
    class AssetPrivate;

    class GLUON_ENGINE_EXPORT Asset : public GluonCore::GluonObject
    {
            Q_OBJECT
            GLUON_OBJECT(GluonEngine::Asset);
            Q_PROPERTY(QUrl file READ file WRITE setFile)

        public:
            Asset(QObject *parent = 0);
            ~Asset();

            virtual void setName(const QString &newName);

            virtual void setFile(const QUrl &newFile);
            virtual QUrl file() const;

            virtual const QMimeData* data() const;

            /**
             * The specialization of toGDL on the Asset class does not recurse.
             * This allows Assets to handle their own children in a flexible
             * manner, without polluting the GDL with that information.
             */
            virtual QString childrenToGDL(int indentLevel = 0) const;

            virtual bool isLoaded() const;

        public slots:
            virtual void load();

        Q_SIGNALS:
            void dataChanged();

        protected:
            QMimeData* mimeData() const;
            void setLoaded(bool loaded);

        private:
            AssetPrivate *d;
    };
}

Q_DECLARE_INTERFACE(GluonEngine::Asset, "com.gluon.Asset/1.0")
Q_DECLARE_METATYPE(GluonEngine::Asset)
Q_DECLARE_METATYPE(GluonEngine::Asset*)

#endif  // GLUON_ASSET_H
