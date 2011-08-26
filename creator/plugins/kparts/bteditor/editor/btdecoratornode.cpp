#include "btdecoratornode.h"
#include "projectparser.h"

#include <QtXml>

btDecoratorNode::btDecoratorNode()
{
    setNodeType(btNodeType::DecoratorNodeType);
}

btDecoratorNode::~btDecoratorNode()
{
}

bool btDecoratorNode::run()
{
	return false;
}

void  btDecoratorNode::toDataXml(QXmlStreamWriter* xmlWriter)
{
	xmlWriter->writeStartElement("decorator");
    
    const QMetaObject * mo = this->metaObject();
    
    for(int i = 0; i < mo->propertyCount(); i++)
    {
        QMetaProperty moProperty = mo->property(i);
        QString propertyName = moProperty.name();
        
        if(propertyName == "objectName")
        {
            continue;
        }
        
        if(propertyName == "name")
        {
			xmlWriter->writeAttribute("name", this->property(moProperty.name()).toString());
        }
        else if(propertyName == "description")
        {
			xmlWriter->writeAttribute("description", this->property(moProperty.name()).toString());
        }
        else if(propertyName == "className")
        {
			xmlWriter->writeAttribute("nodetype", this->property(moProperty.name()).toString());
        }
    }
    
    for(int i = 0; i < this->dynamicPropertyNames().count(); i++)
    {
        QString propertyName(this->dynamicPropertyNames().at(i));
		xmlWriter->writeStartElement("property");
		
		xmlWriter->writeAttribute("name", propertyName);
		xmlWriter->writeAttribute("value", this->property(propertyName.toUtf8()).toString());
		
		xmlWriter->writeEndElement();    
	}
    
	xmlWriter->writeEndElement(); //decorator
}

#include "btdecoratornode.moc"
