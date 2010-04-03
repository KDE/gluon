/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2009 Dan Leinir Turthra Jensen <admin@leinir.dk>
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
#ifndef GLUON_CORE_GLUONOBJECT_H
#define GLUON_CORE_GLUONOBJECT_H

#include <QtCore/QObject>
#include <QtCore/QSharedData>
#include <QtCore/QList>
#include <QtCore/QUrl>
#include <QtCore/QStringList>
#include <QtCore/QVariant>

#include "gluonobjectfactory.h"
#include "gluon_core_export.h"


Q_DECLARE_METATYPE(QList<QUrl>)

#define GLUON_OBJECT(CLASSNAME)\
    public:\
    virtual GluonCore::GluonObject *instantiate();\
    virtual QVariant toVariant(GluonCore::GluonObject *wrapThis);\
    private:

namespace GluonCore
{
    class GameProject;
    class GluonObjectPrivate;

    class GLUON_CORE_EXPORT GluonObject : public QObject
    {
            Q_OBJECT
            Q_PROPERTY(QString name READ name WRITE setName)
            // There is deliberately no gameProject property
            GLUON_OBJECT(GluonCore::GluonObject);

        public:
            GluonObject(QObject * parent = 0);
            explicit GluonObject(const QString& name, QObject *parent = 0);
            GluonObject(const GluonObject& rt);
            virtual ~GluonObject();

            void debug(QString debugText) const;
            
            /**
             * Copy this object and all of its children, resursively.
             *
             * @return A deep copy of the object and all its children
             */
            GluonObject * clone() const;

            virtual QString name() const;
            virtual void setName(const QString &newName);
            QString fullyQualifiedName() const;
            QString fullyQualifiedFileName() const;

            virtual const QStringList supportedMimeTypes() const;

            /**
             * Use this to access functions on the GameProject instance associated
             * with this GluonObject.
             *
             * @return The instance of GameProject this GluonObject is associated with.
             * Note that it is returned as GluonObject so you will need to use a qobject_cast to cast it.
             * @see GameProject GameProject::findItemByName
             */
            GluonObject * gameProject() const;
            /**
             * Do not use this function unless you are absolutely sure what you
             * are doing!
             *
             * @param newGameProject The GameProject instance this GluonObject can be found underneath
             */
            void setGameProject(GluonObject * newGameProject);

            /**
             * Do we need the parsing code in the GluonObject? Or can we separate this into a parser class?
             * We need to separate this into a parser class, imo. Can wait until post-alpha though. -ahiemstra
             */
            virtual QString toGDL(int indentLevel = 0) const;
            virtual QString childrenToGDL(int indentLevel = 0) const;
            virtual QString propertiesToGDL(int indentLevel = 0) const;

            virtual void setPropertyFromString(const QString &propertyName, const QString &propertyValue);
            virtual QString getStringFromProperty(const QString& propertyName, const QString& indentChars) const;

            virtual void sanitize();

            /**
            * QObject hierarchy helper functions.
            */
            virtual void addChild(GluonObject *child);
            virtual bool removeChild(GluonObject *child);
            virtual GluonObject * child(int index) const;
            virtual GluonObject * child(const QString& name) const;

        protected:
            static GluonObject * findItemByNameInObject(QStringList qualifiedName, GluonCore::GluonObject* object);

        private:
            void sanitizeReference(const QString& propName, const QString& propValue);

            QSharedDataPointer<GluonObjectPrivate> d;
    };
}

Q_DECLARE_METATYPE(GluonCore::GluonObject)
Q_DECLARE_METATYPE(GluonCore::GluonObject*)

#endif  // GLUON_CORE_GLUONOBJECT_H
