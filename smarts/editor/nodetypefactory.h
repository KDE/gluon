#ifndef _NODETYPEFACYORY_H_
#define _NODETYPEFACYORY_H_

#include <QObject>

class btEditorNodeType;
#include "../common/btnodetype.h"

class nodeTypeFactory: public QObject
{
		Q_OBJECT
	
public:
	static nodeTypeFactory * instance();
	
	btEditorNodeType * newObject(QString typeCategory);
    btEditorNodeType * newObject(btNodeType::nodeType type);
private:
	nodeTypeFactory();
};

#endif
