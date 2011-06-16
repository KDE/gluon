#ifndef _BTEDITORNODETYPE_H_
#define _BTEDITORNODETYPE_H_

#include <QObject>

#include "../common/btnodetype.h"

class QXmlStreamWriter;

class btEditorNodeType : public btNodeType
{
    Q_OBJECT
    Q_PROPERTY(btNodeType::nodeType childType READ childType WRITE setChildType)
public:


    btEditorNodeType(QObject * parent = NULL);
    
    void appendingChild(int index);
    void removingChild(int index);
    
    btEditorNodeType * copy();
    btNodeType::nodeType childType() const;
    void setChildType(btNodeType::nodeType);
    
    void toNodeTypeXml(QXmlStreamWriter* xmlWriter);
    virtual void toDataXml(QXmlStreamWriter* xmlWriter);
    
    void initProperties();
    
    void disconnectChangeProperty();
    void connectChangeProperty(btEditorNodeType* sender);
    
    void emitPropertyChangedSignal(QString propertyName, QVariant value);
    void emitPropertyDescriptionChangedSignal(QString propertyName, QString oldPropertyName , QString description);
    void emitNameChanged(QString name);
    void emitClassNameChanged(QString className);
    void emitDescriptionChanged(QString description);

Q_SIGNALS:
    void propertyChanged(QString propertyName, QVariant value);
    void propertyDescriptionChanged(QString propertyName, QString oldPropertyName , QString description);
    void nameChanged(QString name);
    void descriptionChanged(QString description);
    void classNameChanged(QString className);
    
public Q_SLOTS:
    void changeProbability(double value);
    void changeProperty(QString propertyName, QVariant value);
    void changePropertyDescription(QString propertyName, QString oldPropertyName , QString description);
    void changeName(QString name);
    void changeDescription(QString description);
    void changeClassName(QString className);
	void changeCondition(bool state);
    
    //used for moving decoratos up and down
    void removeActionTriggered();
    void moveUpAction();
    void moveDownAction();
    
private:
    btNodeType::nodeType m_type;
    btNodeType::nodeType m_childtype;
    btEditorNodeType* m_sender;
};

#endif
