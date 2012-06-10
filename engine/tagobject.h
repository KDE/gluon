#ifndef GLUON_ENGINE_TAGOBJECT_H
#define GLUON_ENGINE_TAGOBJECT_H

#include <core/gluonobject.h>
#include <engine/gameobject.h>
#include "gluon_engine_export.h"
#include "game.h"

#include <QHash>
#include <QSet>

namespace GluonEngine
{
    /**
     * This class is used for managing tags held in the GameProject.
     * Tags are used for searching and categorizing objects.
     */
    class GLUON_ENGINE_EXPORT TagObject : public GluonCore::GluonObject
    {
        Q_OBJECT
        GLUON_OBJECT( GluonEngine::TagObject )

        QHash<QString, QSet<QString> > tags;
        QString path;
        QStringList getObjectsFromScene( GluonEngine::GameObject * scene );

    public:
	Q_INVOKABLE TagObject();
        Q_INVOKABLE TagObject( GluonEngine::TagObject * );
        Q_INVOKABLE TagObject( QString );
	~TagObject();

        /**
         * Simply add a new tag to an object
         */
	Q_INVOKABLE void addTag(GluonEngine::GameObject*, QString );
        Q_INVOKABLE void addTags(QString objectname, QString tags);

        /**
         * Add multiple tags to an object, through a list
         */
        Q_INVOKABLE void addTags(GluonEngine::GameObject*, QList<QString> );

        /**
         * Remove the tags associated with an object
         */
        Q_INVOKABLE void removeTag( GluonEngine::GameObject* );
        void clearTags( QString objectname );
        /**
         * Get all the tags associated with an object
         */
        Q_INVOKABLE QList<QString> getTags( GluonEngine::GameObject* );
        Q_INVOKABLE QString getTags( QString objectname );
        /**
         * Get the parent(base) object name
         */
        Q_INVOKABLE QString getBaseName( QString objectname );
        /**
         * Get all the objects associated with a tag
         */
        Q_INVOKABLE QList<QString> getObjects( QString tag );
        /**
         * Pass a scene with it, to get cloned objects too
         */
        Q_INVOKABLE QList<QString> getObjects( GluonEngine::GameObject* scene, QString tag );
        /**
         * To set the file that the tags are read from
         */
        Q_INVOKABLE void setPath( QUrl path );
        /**
         * Serialize the tags and objects. If path is not specified,
         * the default assets/tags/ is used
         */
        Q_INVOKABLE bool writeToFile();
        Q_INVOKABLE bool writeToFile( QString path );
        /**
         * Read tags from a file
         */
        Q_INVOKABLE bool readFromFile();
        Q_INVOKABLE bool readFromFile( QString path );
        /**
         * For testing purposes, print all the tags+objects
         */
        Q_INVOKABLE void printTags();
    };
}

Q_DECLARE_METATYPE( GluonEngine::TagObject* )

#endif
