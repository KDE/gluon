#ifndef _BTDECORATORNODE_H_
#define _BTDECORATORNODE_H_

#include "bteditornodetype.h"

class QXmlStreamWriter;

class btDecoratorNode : public btEditorNodeType
{
	Q_OBJECT
	
public:
	btDecoratorNode();	
	~btDecoratorNode();
	
	bool run();
    
    void toDataXml(QXmlStreamWriter* xmlWriter);
};

#endif
