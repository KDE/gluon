#include "kclinfowidget.h"
#include <QVBoxLayout>
#include <KTitleWidget>
#include <KIcon>
#include <QTreeView>
KCLInfoWidget::KCLInfoWidget(QWidget * parent)
        :QWidget(parent)
{

 QVBoxLayout * layout = new QVBoxLayout;


   m_information = new QWidget;
   m_preview = new QWidget;
   KTabWidget *tab = new KTabWidget;
tab->addTab(m_preview,KIcon("run-build-configure.png"),"preview");
   tab->addTab(m_information,KIcon("run-build-file.png"),"information");

KCLDeviceModel * model = new KCLDeviceModel;
QVBoxLayout * subLayout = new QVBoxLayout;
QTreeView * treeView = new QTreeView;
treeView->setModel(model);
treeView->setIconSize(QSize(22,22));
subLayout->addWidget(treeView);
m_preview->setLayout(subLayout);
layout->addWidget(tab);



setLayout(layout);

}
