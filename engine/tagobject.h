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
	~TagObject();
	
	void addTag(GluonCore::GluonObject*, QString);
        QList<QString> getTags(GluonCore::GluonObject*);
        QList<QString> getObjects(QString);
    };
}

Q_DECLARE_METATYPE( GluonEngine::TagObject* )

#endif
