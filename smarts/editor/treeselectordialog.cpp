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

#include "treeselectordialog.h"

TreeSelectorDialog::TreeSelectorDialog(bteditor* bteditor)
{
    bte = bteditor;
    // layout
    setWindowTitle(tr("Select Tree"));
    mainLayout = new QVBoxLayout(this);
    buttonLayout = new QHBoxLayout;
    treelist = new QListView();

    treelist->setSelectionMode(QListView::SingleSelection);
    treelist->setMovement(QListView::Static);

    cancel_button = new QPushButton(tr("Cancel"));
    ok_button = new QPushButton(tr("Ok"));
    buttonLayout->addStretch();
    buttonLayout->addWidget(ok_button);
    buttonLayout->addWidget(cancel_button);
    mainLayout->addWidget(treelist);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    setupActions();

    list = new QStringList();
    model = new QStringListModel(this);
    model->setStringList(*list);
    treelist->setModel(model);
}

TreeSelectorDialog::~TreeSelectorDialog() {
    list->clear();
    delete list;
}

void TreeSelectorDialog::setupActions() {
    connect(
        ok_button, SIGNAL(clicked(bool)),
        this, SLOT(chooseTree())
    );
    connect(
        cancel_button, SIGNAL(clicked(bool)),
        this, SLOT(reject())
    );
}

void TreeSelectorDialog::updateModel(QList<btTreeModel *> behaviortrees) {
    if (!behaviortrees.isEmpty()) {
        list->clear();
        foreach(btTreeModel* bttm,behaviortrees) {
            list->append(bttm->name());
        }
        model->setStringList(*list);
    } else {
        QMessageBox::about(this, windowTitle(), tr("No trees to show"));
    }
}

void TreeSelectorDialog::updateModel(btTreeModel * behaviortree) {
    list->append(behaviortree->name());
    model->setStringList(*list);
}

void TreeSelectorDialog::chooseTree() {
    if (treelist->currentIndex().isValid()) {
        emit bte->setBehaviorTree(treelist->currentIndex().row());
    } else {
        QMessageBox::about(this, windowTitle(), tr("No trees selected"));
    }
    emit TreeSelectorDialog::accept();

}

#include "treeselectordialog.moc"
