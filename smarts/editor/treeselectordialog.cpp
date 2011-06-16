#include "treeselectordialog.h"

TreeSelectorDialog::TreeSelectorDialog(bteditor* bte)
{
    this->bte = bte;
    // layout
    this->setWindowTitle(tr("Select Tree"));
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
    this->setLayout(mainLayout);

    setupActions();

    list = new QStringList();
    model = new QStringListModel(this);
    model->setStringList(*list);
    treelist->setModel(model);
}

TreeSelectorDialog::~TreeSelectorDialog(){
    list->clear();
    delete list;
}

void TreeSelectorDialog::setupActions(){
    connect(
        ok_button, SIGNAL(clicked(bool)),
        this, SLOT(chooseTree())
        );
    connect(
        cancel_button, SIGNAL(clicked(bool)),
        this, SLOT(reject())
        );
}

void TreeSelectorDialog::updateModel(QList<btTreeModel *> behaviortrees){
    if(!behaviortrees.isEmpty()){
        list->clear();
        foreach(btTreeModel* bttm,behaviortrees){
            list->append(bttm->name());
        }
        model->setStringList(*list);
    }else{
        QMessageBox::about(this, this->windowTitle(),tr("No trees to show"));
    }
}

void TreeSelectorDialog::updateModel(btTreeModel * behaviortree){
    list->append(behaviortree->name());
    model->setStringList(*list);
}

void TreeSelectorDialog::chooseTree(){
    if(treelist->currentIndex().isValid()){
        emit this->bte->setBehaviorTree(treelist->currentIndex().row());
    }else{
        QMessageBox::about(this, this->windowTitle(),tr("No trees selected"));
    }
    emit TreeSelectorDialog::accept();

}

#include "treeselectordialog.moc"
