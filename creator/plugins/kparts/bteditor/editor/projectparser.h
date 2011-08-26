#ifndef _PROJECTPARSER_H_
#define _PROJECTPARSER_H_

#include <QObject>
#include <QHash>

class QDomNode;
class btBrain;
class btTreeModel;
class btEditorNode;
class btEditorNodeType;

class projectParser : public QObject
{
    Q_OBJECT

public:
    static projectParser * instance();

    //parsing the xmldata, which is a QString which is contents of the xml file
    btBrain* parseProject(QString xmlData);
    //returning the btBrain serialized to a xml formatted QString
    const QString serializeProject(btBrain * brain);

private:
    projectParser();

    int m_indentCount;
    QHash<int, btTreeModel*> behaviorTreesList;

    void parseNodeTypes(QDomNode xNode, btBrain * brain);
    void parseBehaviorTrees(QDomNode xNode, btEditorNode * node ,btBrain * brain);
};

#endif
