#ifndef GLUON_ENGINE_SCENEGRAPHOBJECT_H
#define GLUON_ENGINE_SCENEGRAPHOBJECT_H

#include <QObject>
#include <QList>
#include <core/gluonobject.h>
#include "gluon_engine_export.h"

namespace GluonEngine
{
    class GLUON_ENGINE_EXPORT SceneGraphObject : public GluonCore::GluonObject
    {
        Q_OBJECT
        GLUON_OBJECT( GluonEngine::SceneGraphObject )
	
	SceneGraphObject *parent;
	QString group_name;
	GluonCore::GluonObject *member;
	QList<GluonObject*> children;
	QList<SceneGraphObject*> childrenGroup;
	long hash;
	
    public:
        SceneGraphObject();
	SceneGraphObject( SceneGraphObject*, QString, GluonCore::GluonObject*, QList<GluonObject*>, QList<SceneGraphObject*> );
        ~SceneGraphObject();
	
	void setParent( SceneGraphObject* );
	void setGroupName( QString );
	void addChildren( QList<GluonObject*> );
	void addChildrenGroup( QList<SceneGraphObject*> );
	void setHash( long );
	int childCount();
	int groupCount();
    };
}

Q_DECLARE_METATYPE( GluonEngine::SceneGraphObject* )
#endif