#ifndef _BTBRAIN_H_
#define _BTBRAIN_H_

#include <QObject>
#include <QList>
#include <QHash>
#include <QtXml/QDomDocument>
#include <QtXml/QDomNode>

#include "btlib_export.h"
#include "btperceptioninfo.h"

class btNode;
Q_DECLARE_METATYPE(QList<btPerceptionInfo*>);

class BT_LIB_EXPORT btBrain : public QObject
{
    Q_OBJECT
    
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString description READ description WRITE setDescription)
    Q_PROPERTY(QList<btPerceptionInfo*> perceptionInfos READ perceptionInfos WRITE setPerceptionInfos)
    
public:
    btBrain(QString data, QString file);
    ~btBrain();
    
    btNode* getBehaviorTree(int index);
    int behaviorTreesCount();
    
    QString name();
    void setName(QString name);
    QString description();
    void setDescription(QString description);
    /**
     * The perception information currently available in the game
     */
    QList<btPerceptionInfo*> perceptionInfos() const;
    void setPerceptionInfos(const QList<btPerceptionInfo*>& newPerceptionInfos);
    btPerceptionInfo* perceptionInfo(const QString& name) const;
	void addPerceptionInfo(btPerceptionInfo * newPercpetionInfo);
	QString getFile();
    
private:
    QHash<int, btNode*> m_behaviorTrees;
	QList<btPerceptionInfo*> m_perceptionInfos;
    
    QString m_name;
    QString m_description;    
    
    void parseNodeTypes(QDomNode xNode);
    void parseBehaviorTrees(QDomNode xNode, btNode* node);//, int nodeIndex);
	
	QString m_file;
};

#endif
