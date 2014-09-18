/*
 * <one line to give the library's name and an idea of what it does.>
 * Copyright 2014  Dan Leinir Turthra Jensen <admin@leinir.dk>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License or (at your option) version 3 or any later version
 * accepted by the membership of KDE e.V. (or its successor approved
 * by the membership of KDE e.V.), which shall act as a proxy
 * defined in Section 14 of version 3 of the license.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "btnodeeditor.h"
#include "bttreemodel.h"
#include "bteditornode.h"
#include <btnode.h>

#include "nodeeditor/qnodeseditor.h"
#include <nodeeditor/qneblock.h>
#include <nodeeditor/qneconnection.h>
#include <QLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QBoxLayout>
#include <QDebug>

class btNodeEditor::Private {
public:
    Private(btNodeEditor* qq)
        : q(qq)
        , nodeEditor(0)
        , view(0)
        , scene(0)
        , nodeModel(0)
    {}
    btNodeEditor* q;
    QNodesEditor* nodeEditor;
    QGraphicsView *view;
    QGraphicsScene *scene;
    btTreeModel* nodeModel;
    QHash<QNEBlock*, btEditorNode*> nodes;

    void updateVisibleTree() {
        scene->clear();
        qDebug() << "Updating the visible tree with" << nodeModel;
        addTreeNode(0, qobject_cast<btEditorNode*>(nodeModel->rootNode()->child(0)));
    }

    void addTreeNode(QNEPort* origin, btEditorNode* node) {
        QNEBlock* nodeBlock = new QNEBlock();
        nodes.insert(nodeBlock, node);
        connect(nodeBlock, SIGNAL(positionChanged()), q, SLOT(nodePositionChanged()));
        if(node->name().isEmpty()) {
            nodeBlock->addPort("(unnamed)", QNEPort::LeftPosition, false, QNEPort::NamePort);
        }
        else {
            nodeBlock->addPort(node->name(), QNEPort::LeftPosition, false, QNEPort::NamePort);
        }
        nodeBlock->setPos(node->position());
        scene->addItem(nodeBlock);
        if(origin) {
            QNEPort* inputPort = nodeBlock->addPort(" ", QNEPort::TopPosition, false);
            QNEConnection* conn = new QNEConnection(0);
            scene->addItem(conn);
            conn->setPort1(origin);
            conn->setPos1(origin->scenePos());
            conn->setPos2(inputPort->scenePos());
            conn->setPort2(inputPort);
            conn->updatePath();
        }
        Q_FOREACH(btNode* child, node->children()) {
            btEditorNode* childNode = qobject_cast<btEditorNode*>(child);
            QNEPort* childPort = nodeBlock->addPort(" ", QNEPort::BottomPosition, true);
            addTreeNode(childPort, childNode);
        }
        qDebug() << "Added the node" << node;
    }
};

btNodeEditor::btNodeEditor(QWidget* parent)
    : QWidget(parent)
    , d(new Private(this))
{
    d->scene = new QGraphicsScene(this);
    d->view = new QGraphicsView(this);
    d->view->setScene(d->scene);
    d->view->setRenderHint(QPainter::Antialiasing, true);

    d->nodeEditor = new QNodesEditor(this);
    d->nodeEditor->install(d->scene);

    setLayout(new QVBoxLayout(this));
    layout()->addWidget(d->view);
}

btNodeEditor::~btNodeEditor()
{
    delete d;
}

void btNodeEditor::setModel(btTreeModel* showThis)
{
    d->nodeModel = showThis;
    d->updateVisibleTree();
}

btNode* btNodeEditor::selectedNode()
{
    return 0;
}

void btNodeEditor::nodePositionChanged()
{
    QNEBlock* block = qobject_cast<QNEBlock*>(sender());
    btEditorNode* node = d->nodes.value(block);
    if(node) {
        node->setPosition(block->pos());
    }
}

#include "btnodeeditor.moc"
