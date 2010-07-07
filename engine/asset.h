/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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
    
    class GLUON_ENGINE_EXPORT AssetTemplate : public QObject
    {
        Q_OBJECT
        public:
            AssetTemplate(QString name, QString filename, QString pluginname, QObject *parent = 0)
                : QObject(parent)
                , name(name)
                , filename(filename)
                , pluginname(pluginname)
            { }
            ~AssetTemplate() {};
            

            /**
            * The name which the newly created asset object will be given
            */
            QString name;
            /**
            * The filename of the template, as found inside the template dir for
            * this asset (for example /usr/share/gluon/template/assetclassname/filename)
            */
            QString filename;
            /**
             * The name of the plugin (that is, the subdir inside which the template file is found)
             */
            QString pluginname;
    };

    class GLUON_ENGINE_EXPORT Asset : public GluonCore::GluonObject
    {
            Q_OBJECT
            GLUON_OBJECT(GluonEngine::Asset);
            Q_PROPERTY(QUrl file READ file WRITE setFile)

        public:
            Q_INVOKABLE Asset(QObject *parent = 0);
            ~Asset();

            virtual void setName(const QString &newName);

            virtual void setFile(const QUrl &newFile);
            virtual QUrl file() const;

            /**
             * The templates provided by the asset. The default
             * implementation returns no templates, as many assets will not
             * be able to provide templates.
             */
            virtual const QList<AssetTemplate*> templates();

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
