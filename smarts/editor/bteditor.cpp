/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2009 Dan Leinir Turthra Jensen <admin@leinir.dk>
 * Copyright (c) 2009 Kim Jung Nissen <jungnissen@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "bteditor.h"

#include "btbrain.h"
#include "bttreemodel.h"
#include "btnodetypesmodel.h"
#include "bteditornode.h"
#include "modeltest.h"
#include "treeselectordialog.h"
#include "projectparser.h"
#include "btpropertywidget.h"
#include "btnodeeditwidget.h"
#include "btnodemodel.h"
#include "btnodetypesmodelnode.h"
#include "btnode.h"
#include "btnodetype.h"
#include "bteditornodetype.h"
#include "btnewtreewizard.h"

#include <QtGui/QMessageBox>
#include <QtGui/QFileDialog>
#include <QtGui/QMenu>

bteditor::bteditor(QWidget *parent)
    : KParts::MainWindow()
    , m_currentBehaviorTree(NULL)
    , oldPropertyWidget(NULL)
{
    Q_UNUSED(parent)

    setupUi(this);
    propertyWidget = new btPropertyWidget(this);
    propertyScrollArea->setWidget(propertyWidget);
    setupActions();

    fileName = "";

    m_brain = new btBrain(this);
    nodeTypes = new btNodeTypesModel(m_brain, this);

    replaceBrain();

    treeSelectDialog = new TreeSelectorDialog(this);
    editWidget = new btNodeEditWidget(this);
    wizard = new NewTreeWizard(this);
    availableNodes->setContextMenuPolicy(Qt::CustomContextMenu);
    btEditor->setContextMenuPolicy(Qt::CustomContextMenu);
    treeContextMenu = new QMenu(this);
    btEditorContextMenu = new QMenu(this);
    ///fixme move out
    QAction* menuNewNode = treeContextMenu->addAction(tr("New Node Type"));
    QAction* menuDeleteNode = treeContextMenu->addAction(tr("Delete Node Type"));

    QAction* bteditDeleteNode = btEditorContextMenu->addAction(tr("Delete Node"));

    connect(
        menuNewNode,SIGNAL(triggered(bool)),
        this,SLOT(menuNewNodeTriggered())
    );

    connect(
        menuDeleteNode,SIGNAL(triggered(bool)),
        this,SLOT(menuDeleteNodeTriggered())
    );

    connect(
        bteditDeleteNode,SIGNAL(triggered(bool)),
        this,SLOT(bteditDeleteNodeTriggered())
    );

    setXMLFile( "gluon_bteditor.rc" );
    m_brain->newBehaviorTree();
}

bteditor::~bteditor()
{}

void bteditor::setupActions()
{
    connect(
        actionNew_Tree, SIGNAL(triggered(bool)),
        this, SLOT(createNewBehaviorTree())
    );
    connect(
        actionQuit, SIGNAL(triggered(bool)),
        qApp, SLOT(quit())
    );
    connect(
        showBehaviorTreeList, SIGNAL(clicked(bool)),
        this, SLOT(showBehaviorTreeListCicked())
    );
}

void bteditor::showBehaviorTree(btTreeModel* showThis)
{
    disconnect(this, SLOT(editorSelectionChanged(QItemSelection,QItemSelection)));
    btEditor->setModel(showThis);
    btEditor->setSelectionModel(new QItemSelectionModel(showThis));
    connect(
        btEditor->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
        this, SLOT(editorSelectionChanged(QItemSelection,QItemSelection))
    );
    currentBTNameLabel->setText(showThis->name());

    if (m_currentBehaviorTree)
    {
        disconnect(m_currentBehaviorTree, SIGNAL(addRemoveBTNode()), propertyWidget, SLOT(dragDropUpdate()));
        disconnect(propertyWidget, SIGNAL(treeModelUpdate()), m_currentBehaviorTree, SLOT(updateTreeModel()));
        disconnect(m_currentBehaviorTree, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(updateView(QModelIndex,QModelIndex)));

    }
    m_currentBehaviorTree = showThis; // keep track of behaviortree
    connect(m_currentBehaviorTree, SIGNAL(addRemoveBTNode()), propertyWidget, SLOT(dragDropUpdate()));
    connect(propertyWidget, SIGNAL(treeModelUpdate()), m_currentBehaviorTree, SLOT(updateTreeModel()));
    connect(m_currentBehaviorTree, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(updateView(QModelIndex,QModelIndex)));

}

void bteditor::editorSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
{
    Q_UNUSED(selected)
    Q_UNUSED(deselected)
    btNode* selectedNode = static_cast<btNode*>(btEditor->selectionModel()->currentIndex().internalPointer());
    showPropertiesFor(qobject_cast<btEditorNode*>(selectedNode));
}

void bteditor::showPropertiesFor(btEditorNode* showFor)
{
    /*if(propertyWidget == NULL)
    {
        propertyWidget = new btPropertyWidget(this);
        propertyScrollArea->setWidget(propertyWidget);
        connect(m_currentBehaviorTree, SIGNAL(addRemoveBTNode()), propertyWidget, SLOT(dragDropUpdate()));
    }*/

    if (oldPropertyWidget)
    {
        delete oldPropertyWidget;
        oldPropertyWidget = NULL;
    }

    if (propertyWidget)
    {
        oldPropertyWidget = qobject_cast<btPropertyWidget*>(propertyScrollArea->takeWidget());
        disconnect(m_currentBehaviorTree, SIGNAL(addRemoveBTNode()), propertyWidget, SLOT(dragDropUpdate()));
    }

    if (propertyWidget->node())
    {
        disconnect(propertyWidget->node(), SIGNAL(updatePropertyWidget(btEditorNode*)), this, SLOT(showFor(btEditorNode*)));
    }


    propertyWidget = new btPropertyWidget(this);
    propertyScrollArea->setWidget(propertyWidget);
    connect(m_currentBehaviorTree, SIGNAL(addRemoveBTNode()), propertyWidget, SLOT(dragDropUpdate()));
    connect(showFor, SIGNAL(updatePropertyWidget(btEditorNode*)), this, SLOT(showFor(btEditorNode*)));
    propertyWidget->setNode(showFor);
}

void bteditor::createNewBehaviorTree()
{
    wizard->show();
}

void bteditor::newBehaviorTreeCreated(QString name) {
    m_brain->newBehaviorTree(name);
    nodeTypes->insertRows(0,0,availableNodes->selectionModel()->currentIndex());
}

void bteditor::showBehaviorTreeListCicked()
{
    treeSelectDialog->updateModel(m_brain->behaviorTrees);
    treeSelectDialog->show();
}

void bteditor::newBehaviorTreeAdded(btTreeModel* newTree)
{
    showBehaviorTree(newTree);
    treeSelectDialog->setWindowIcon(QIcon(":/images/reference.png"));
    treeSelectDialog->updateModel(newTree);
}



void bteditor::on_actionOpen_triggered()
{
    fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                            "",
                                            tr("Behavior Trees (*.glbt *.xml)"));

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    QByteArray byteArray = file.readAll();
    QString fileContents(byteArray.data());
    file.close();


    delete m_brain;
    delete nodeTypes;
    m_currentBehaviorTree = NULL;

    m_brain = projectParser::instance()->parseProject(fileContents);
    m_brain->setParent(this);
    ///fixme does this get deleted when bteditor is deleted?
    nodeTypes = new btNodeTypesModel(m_brain, this);
    replaceBrain();
    showBehaviorTree(m_brain->behaviorTrees[0]);

}

void bteditor::on_actionSave_As_triggered()
{
    ///fixme does not return if it actually saved
    fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                            "untitled.glbt",
                                            tr("Behavior Trees (*.glbt *.xml)"));


    if (!fileName.endsWith(QLatin1String(".xml"), Qt::CaseInsensitive))
        fileName += ".xml";

    QString fileContents = projectParser::instance()->serializeProject(m_brain);

    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QByteArray byteFileContents(fileContents.toUtf8());
    file.write(byteFileContents);
    file.close();
}

void bteditor::on_actionSave_triggered()
{
    if (fileName.isEmpty()) {
        on_actionSave_As_triggered();
    } else {
        QString fileContents = projectParser::instance()->serializeProject(m_brain);

        QFile file(fileName);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QByteArray byteFileContents(fileContents.toUtf8());
        file.write(byteFileContents);
        file.close();
    }
}


void bteditor::setBehaviorTree(int index)
{
    // missing sanity check
    showBehaviorTree(m_brain->behaviorTrees[index]);
}

void bteditor::replaceBrain() {
    connect(
        m_brain, SIGNAL(nodeTypeAdded(btEditorNodeType*)),
        nodeTypes, SLOT(newBehaviorTreeTypeAdded(btEditorNodeType*))
    );
    connect(
        m_brain, SIGNAL(behaviorTreeAdded(btTreeModel*)),
        this, SLOT(newBehaviorTreeAdded(btTreeModel*))
    );
    connect(
        m_brain,SIGNAL(nodeTypeDeleted(int)),
        this,SLOT(nodeTypeDeleted(int))
    );
    ///fixme add connection between nodeTypeDeleted and this
    availableNodes->setModel(nodeTypes);
    //new ModelTest(nodeTypes, this);
}



void bteditor::on_actionEdit_Node_triggered()
{
    //just for testing
    /*if(m_brain->nodeTypes.count() >= 3){
    btnodemodel* btm = new btnodemodel(m_brain->nodeTypes.at(2),this);
    btNodeEditWidget* editWidget = new btNodeEditWidget();
    editWidget->setModel(btm);
    editWidget->show();
    }*/
}



void bteditor::on_availableNodes_activated(QModelIndex index)
{
    //skal fixes for memstuff, tjekker ikke om det er en valid node
    btNodeTypesModelNode* selectedNode = static_cast<btNodeTypesModelNode*>(index.internalPointer());

    if (selectedNode->nodeType()->className() == "[selector]"
            || selectedNode->nodeType()->className() == "[sequence]"
            || selectedNode->nodeType()->className() == "[reference]"
            || selectedNode->nodeType()->className() == "[probselector]"
            || selectedNode->nodeType()->className() == "[parallel]")
    {
        return;
    }

    ///fixme ->parent()->parent() should be NULL not ->parent() change when crash
    if (selectedNode->parent() != 0) {
        btnodemodel* btm =  new btnodemodel(qobject_cast<btEditorNodeType*>(selectedNode->nodeType()));
        if (m_currentBehaviorTree)
            connect(btm, SIGNAL(updatePropertyWidget()), m_currentBehaviorTree, SIGNAL(addRemoveBTNode()));

        editWidget->disconnectSignals(m_currentBehaviorTree);
        editWidget->setModel(btm);
        editWidget->setSelectedNode(selectedNode);
        editWidget->connectSignals();
        editWidget->setWindowIcon(QIcon(":/images/sequence.png"));
        if (editWidget->isHidden()) {
            editWidget->show();
        } else {
            // bring to front, make active
            editWidget->activateWindow();
        }
    }
}

void bteditor::on_availableNodes_customContextMenuRequested(QPoint pos)
{
    if (availableNodes->indexAt(pos).isValid())
    {
        btNodeTypesModelNode* selectedNode = static_cast<btNodeTypesModelNode*>(availableNodes->selectionModel()->currentIndex().internalPointer());
        if (selectedNode->nodeType()->className() != "[selector]"
                && selectedNode->nodeType()->className() != "[sequence]"
                && selectedNode->nodeType()->className() != "[probselector]"
                && selectedNode->nodeType()->className() != "[parallel]")
        {
            treeContextMenu->exec(availableNodes->viewport()->mapToGlobal(pos));
        }
    }
}

void bteditor::menuDeleteNodeTriggered()
{
    btNodeTypesModelNode* selectedNode = static_cast<btNodeTypesModelNode*>(availableNodes->selectionModel()->currentIndex().internalPointer());
    ///fixme ->parent()->parent() should be NULL not ->parent() change when crash
    if (selectedNode->parent() != 0)
    {
        if (selectedNode->nodeType()->type() == btNodeType::ReferenceNodeType)
        {
            if (m_brain->behaviorTrees.count() > 1)
            {
                btEditorNodeType* refNode = m_brain->findNodeTypeByName(selectedNode->nodeType()->name());
                for (int i = 0; i < m_brain->behaviorTrees.count(); i++)
                {
                    if (refNode->name() == m_brain->behaviorTrees[i]->name())
                    {
                        if (m_brain->behaviorTrees[i] == m_currentBehaviorTree)
                        {
                            if (i == 0)
                            {
                                showBehaviorTree(m_brain->behaviorTrees[1]);
                            }
                            else
                            {
                                showBehaviorTree(m_brain->behaviorTrees[0]);
                            }

                        }

                        m_brain->deleteBehaviorTree(m_brain->behaviorTrees[i]);
                        break;
                    }
                }

                m_brain->removeNodeType(selectedNode->nodeType() ,selectedNode->row());
            }
        }
        else
        {
            m_brain->removeNodeType(selectedNode->nodeType() ,selectedNode->row());
        }
    }
}

void bteditor::menuNewNodeTriggered()
{
    btNodeTypesModelNode* selectedNode = static_cast<btNodeTypesModelNode*>(availableNodes->selectionModel()->currentIndex().internalPointer());
    if (selectedNode->nodeType()->childType() == btNodeType::ReferenceNodeType) {
        wizard->show();
    } else {
        ///fixme ->parent()->parent() should be NULL not ->parent() change when crash
        ///fixme memory, is it deleted in brain ?
        //m_brain->addNodeType();
        nodeTypes->insertRows(0,1,availableNodes->selectionModel()->currentIndex());
    }

}

void bteditor::nodeTypeDeleted(int row)
{
    ///fixme update and check for parent
    nodeTypes->removeRows(row,1,availableNodes->selectionModel()->currentIndex());
}


void bteditor::on_btEditor_customContextMenuRequested(QPoint pos)
{
    if (btEditor->indexAt(pos).isValid()) {
        btNode* selectedNode = static_cast<btNode*>(btEditor->indexAt(pos).internalPointer());
        if (selectedNode->parent()->parent() != 0) {
            btEditorContextMenu->exec(btEditor->viewport()->mapToGlobal(pos));
        }
    }
}

void bteditor::bteditDeleteNodeTriggered()
{
    btNode* selectedNode = static_cast<btNode*>(btEditor->selectionModel()->currentIndex().internalPointer());
    if (selectedNode->parent()->parent() != 0) {
        ///fixme check if memory is deallocated when removed from list ?
        m_currentBehaviorTree->removeRows(selectedNode->row(),1,btEditor->selectionModel()->currentIndex().parent());
    }
}

void bteditor::on_actionNew_triggered()
{
    int result = QMessageBox::question(this,
                                       tr("Save Project?"),
                                       tr("Do you want to save the current project?"),QMessageBox::Save,QMessageBox::Discard,QMessageBox::Cancel);

    if (result == QMessageBox::Cancel) {
        return;
    }

    if (result == QMessageBox::Save) {
        emit on_actionSave_triggered();
    }

    delete m_brain;
    delete nodeTypes;
    m_currentBehaviorTree = NULL;

    m_brain = new btBrain(this);
    m_brain->setParent(this);

    ///fixme does this get deleted when bteditor is deleted?
    nodeTypes = new btNodeTypesModel(m_brain, this);
    replaceBrain();
    m_brain->newBehaviorTree();
}

void bteditor::on_actionNew_Tree_triggered()
{

}

void bteditor::updateView(const QModelIndex& one, const QModelIndex& two)
{
    Q_UNUSED(two)
    btEditor->scrollTo(one);
}

void bteditor::showFor(btEditorNode* node)
{
    showPropertiesFor(node);
}

#include "bteditor.moc"





