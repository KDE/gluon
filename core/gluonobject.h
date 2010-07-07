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
    virtual GluonCore::GluonObject* instantiate();\
    virtual GluonCore::GluonObject* fromVariant(const QVariant &wrappedObject);\
    virtual QVariant toVariant(GluonCore::GluonObject *wrapThis);\
    private:

namespace GluonCore
{
    class GameProject;
    class GluonObjectPrivate;
    class MetaInfo;

    class GLUON_CORE_EXPORT GluonObject : public QObject
    {
            Q_OBJECT
            Q_PROPERTY(QString name READ name WRITE setName)
            // There is deliberately no gameProject property
            GLUON_OBJECT(GluonCore::GluonObject);

        public:
            Q_INVOKABLE GluonObject(QObject * parent = 0);
            explicit GluonObject(const QString& name, QObject *parent = 0);
            GluonObject(const GluonObject& rt);
            virtual ~GluonObject();

            Q_INVOKABLE void debug(const QString& debugText) const;
            Q_SIGNAL void showDebug(const QString& debugText) const;

            /**
             * Copy this object and all of its children, resursively.
             * It will be a child of the same GluonObject that the current object is a child of.
             *
             * @return A deep copy of the object and all its children
             */
            Q_INVOKABLE GluonObject * clone() const;
            /**
             * Copy this object and all of its children, recursively, and insert the cloned object
             * as a child of the passed GluonObject
             *
             * @return A deep copy of the object and all its children
             */
            Q_INVOKABLE GluonObject * clone(GluonObject* parentObject) const;

            virtual QString name() const;
            virtual void setName(const QString &newName);
            /**
             * The fully qualified name of the object, from the root and upwards.
             * The object name separator is / which means that an object named
             * AnObject which is child of the top level object AnotherObject is:
             * AnotherObject/AnObject
             */
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
             * Get the Gluon meta info for this object
             * @return The meta information related to this object
             */
            Q_INVOKABLE MetaInfo* metaInfo();
            Q_INVOKABLE bool hasMetaInfo() const;

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
            Q_INVOKABLE GluonObject* findItemByName(QString qualifiedName);
            Q_INVOKABLE virtual GluonObject* root();
            virtual void addChild(GluonObject *child);
            virtual bool removeChild(GluonObject *child);
            virtual GluonObject * child(int index) const;
            virtual GluonObject * child(const QString& name) const;

        protected:
            static GluonObject * findItemByNameInObject(QStringList qualifiedName, GluonCore::GluonObject* object);
            /**
             * This function is called by the clone function before handing the cloned object
             * back to the caller. If you have something special which needs to be done to each
             * child after adding, re-implement this function and perform those actions.
             */
            virtual void postCloneSanitize() {};

        private:
            void sanitizeReference(const QString& propName, const QString& propValue);

            QSharedDataPointer<GluonObjectPrivate> d;
    };
}

Q_DECLARE_METATYPE(GluonCore::GluonObject)
Q_DECLARE_METATYPE(GluonCore::GluonObject*)

#endif  // GLUON_CORE_GLUONOBJECT_H
