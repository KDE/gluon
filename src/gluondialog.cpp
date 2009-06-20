#include "gluondialog.h"

GluonDialog::GluonDialog()
{

    contentsWidget = new QListWidget;
    contentsWidget->setViewMode(QListView::IconMode);
    contentsWidget->setIconSize(QSize(64,64));
//    contentsWidget->setMovement(QListView::Static);
    contentsWidget->setMaximumWidth(120);
    contentsWidget->setSpacing(12);

     pagesWidget = new QStackedWidget;
     pagesWidget->addWidget(new KGLConfig);
     pagesWidget->addWidget(new KALConfig);
     pagesWidget->addWidget(new KCLConfig);


     createIcons();
    QPushButton *closeButton = new QPushButton(tr("Close"));

         contentsWidget->setCurrentRow(0);

     QHBoxLayout *horizontalLayout = new QHBoxLayout;
     horizontalLayout->addWidget(contentsWidget);
     horizontalLayout->addWidget(pagesWidget, 1);

     QHBoxLayout *buttonsLayout = new QHBoxLayout;

     buttonsLayout->addWidget(closeButton);

     QVBoxLayout *mainLayout = new QVBoxLayout;
     mainLayout->addLayout(horizontalLayout);

     mainLayout->addSpacing(12);
     mainLayout->addLayout(buttonsLayout);
     setLayout(mainLayout);

     setWindowTitle(tr("Config Dialog"));
}

void GluonDialog::createIcons()
{

     QListWidgetItem *configButton = new QListWidgetItem(contentsWidget);
     configButton->setIcon(QIcon(":kgl.png"));
     configButton->setText(tr("Configuration"));
     configButton->setTextAlignment(Qt::AlignHCenter);
     configButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

     QListWidgetItem *updateButton = new QListWidgetItem(contentsWidget);
     updateButton->setIcon(QIcon(":kal.png"));
     updateButton->setText(tr("Update"));
     updateButton->setTextAlignment(Qt::AlignHCenter);
     updateButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

     QListWidgetItem *queryButton = new QListWidgetItem(contentsWidget);
     queryButton->setIcon(QIcon(":kcl.png"));
     queryButton->setText(tr("Query"));
     queryButton->setTextAlignment(Qt::AlignHCenter);
     queryButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

     connect(contentsWidget,
             SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)),
             this, SLOT(changePage(QListWidgetItem *, QListWidgetItem*)));
}
 void GluonDialog::changePage(QListWidgetItem *current, QListWidgetItem *previous)
 {
     if (!current)
         current = previous;

     pagesWidget->setCurrentIndex(contentsWidget->row(current));
 }
