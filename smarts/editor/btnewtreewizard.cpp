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

#include "btnewtreewizard.h"

#include "bteditor.h"
#include "btnodeeditwidget.h"

#include <QtWidgets/QWizard>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

NewTreeWizard::NewTreeWizard(QWidget *parent)
        : QWizard(parent)
{
    addPage(new IntroPage);
    addPage(new NamePage);
    //addPage(new NodeTypePage);

    setWindowTitle(tr("New Behavior Tree Wizard"));
    bteditor* editor = static_cast<bteditor*>(parent);
    connect(
        this, SIGNAL(behaviorTreeCreated(QString)),
        editor, SLOT(newBehaviorTreeCreated(QString))
    );
}


void NewTreeWizard::accept()
{
    QString name = field("name").toString();
    emit behaviorTreeCreated(name);
    close();
}

IntroPage::IntroPage(QWidget *parent)
        : QWizardPage(parent)
{
    setTitle(tr("Introduction"));

    label = new QLabel(tr("This wizard will generate a new behavior tree "
                          "(more here later)"));
    label->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    setLayout(layout);
}

NamePage::NamePage(QWidget *parent)
        : QWizardPage(parent)
{
    setTitle(tr("Choose Name for Behavior Tree"));

    label = new QLabel(tr("This wizard will generate a new behavior tree "
                          "(more here later)"));
    label->setWordWrap(true);
    nameEdit = new QLineEdit;
    nameLabel = new QLabel(tr("Tree Name"));

    QVBoxLayout *layout = new QVBoxLayout;
    QHBoxLayout *nameLayout = new QHBoxLayout;
    nameLayout->addWidget(nameLabel);
    nameLayout->addWidget(nameEdit);

    registerField("name*", nameEdit);
    layout->addWidget(label);
    layout->addLayout(nameLayout);
    setLayout(layout);
}

NodeTypePage::NodeTypePage(QWidget *parent)
        : QWizardPage(parent)
{
    setTitle(tr("Add Node Types"));

    label = new QLabel(tr("Add new or existing node types to the project"
                          "(more here later)"));
    label->setWordWrap(true);
    nodeEditor = new btNodeEditWidget(this);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(nodeEditor);
    setLayout(layout);
}

 
