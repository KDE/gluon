#include "kclinfowidget.h"
#include <QVBoxLayout>
#include <KTitleWidget>
#include <KIcon>
KCLInfoWidget::KCLInfoWidget(QWidget * parent)
        :QWidget(parent)
{

 QVBoxLayout * layout = new QVBoxLayout;
   KTitleWidget * title = new KTitleWidget;

   m_information = new QWidget;
   m_preview = new QWidget;

   KTabWidget *tab = new KTabWidget;
tab->addTab(m_preview,KIcon("run-build-configure.png"),"preview");
   tab->addTab(m_information,KIcon("run-build-file.png"),"information");

title->setPixmap(KIcon("kgl.png"));
title->setText("KCL ");
   layout->addWidget(title);
layout->addWidget(tab);



setLayout(layout);

}
