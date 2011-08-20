#ifndef bteditor_H
#define bteditor_H

#include <QtGui/QMainWindow>
#include <QMenu>
#include "ui_bteditor.h"
#include "treeselectordialog.h"
#include <kparts/mainwindow.h>

class btNode;
class btNodeTypesModel;
class btBrain;
class btTreeModel;
class btEditorNode;
class TreeSelectorDialog;
class btPropertyWidget;
class btNodeEditWidget;
class NewTreeWizard;

class bteditor : public KParts::MainWindow, private Ui::BtEditor
{
Q_OBJECT
public:
    bteditor(QWidget *parent = 0);
    virtual ~bteditor();
    void setupActions();
    
    void showBehaviorTree(btTreeModel* showThis);
    void showPropertiesFor(btEditorNode* showFor);
    
public Q_SLOTS:
    void createNewBehaviorTree();
    void newBehaviorTreeAdded(btTreeModel* newTree);
    void newBehaviorTreeCreated(QString name);
    void showBehaviorTreeListCicked();
    void setBehaviorTree(int index);
    void replaceBrain();
    void editorSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected);
    void nodeTypeDeleted(int row);
    void updateView(const QModelIndex& one, const QModelIndex& two);
    
    void showFor(btEditorNode* node);
    
private:
    btBrain *m_brain;
    btNodeTypesModel *nodeTypes;
    btTreeModel *m_currentBehaviorTree;
    TreeSelectorDialog *treeSelectDialog;
    btNodeEditWidget *editWidget;
    btPropertyWidget *propertyWidget;
    NewTreeWizard *wizard;
    QMenu   *treeContextMenu;
    QMenu   *btEditorContextMenu;
    QString fileName;
    
    btPropertyWidget* oldPropertyWidget;

private slots:
    void on_actionNew_triggered();
    void on_actionNew_Tree_triggered();
    void on_btEditor_customContextMenuRequested(QPoint pos);
    void on_actionSave_triggered();
    void on_availableNodes_customContextMenuRequested(QPoint pos);
    void on_availableNodes_activated(QModelIndex index);
    void menuNewNodeTriggered();
    void menuDeleteNodeTriggered();
    void bteditDeleteNodeTriggered();
    void on_actionEdit_Node_triggered();
    void on_actionSave_As_triggered ();
    void on_actionOpen_triggered ();
};

#endif // bteditor_H
