#ifndef GLUON_ENGINE_TAGOBJECT_H
#define GLUON_ENGINE_TAGOBJECT_H

#include <core/gluonobject.h>
#include "gluon_engine_export.h"

#include <QHash>
#include <QSet>

namespace GluonEngine
{
    class GLUON_ENGINE_EXPORT TagObject : public GluonCore::GluonObject
    {
        Q_OBJECT
        GLUON_OBJECT( GluonEngine::TagObject )

        QHash<QString, QSet<QString> > tags;

    public:
	TagObject();
        TagObject( const GluonEngine::TagObject & );
        TagObject( QString );
	~TagObject();
	
	void addTag(GluonCore::GluonObject*, QString );
        void removeTag( GluonCore::GluonObject* );
        QList<QString> getTags(GluonCore::GluonObject*);
        QList<QString> getObjects(QString);

        bool writeToFile();
        bool writeToFile( QString );
        bool readFromFile();
        bool readFromFile( QString );

        /*
         * For testing purposes
         */
        void printTags();
    };
}

Q_DECLARE_METATYPE( GluonEngine::TagObject* )

#endif
