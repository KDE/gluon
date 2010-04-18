/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include "newprojectdialogpage.h"

#include <QtGui/QWidget>
#include <QtGui/QGroupBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QFormLayout>
#include <QtGui/QLabel>

#include <KDE/KLocalizedString>
#include <KDE/KIcon>
#include <KDE/KLineEdit>
#include <KDE/KUrlRequester>
#include <KDE/KMessageBox>

#include <engine/gameproject.h>
#include <engine/scene.h>
#include <engine/game.h>
#include <engine/gameobject.h>
#include <engine/component.h>

using namespace GluonCreator;

class NewProjectDialogPage::NewProjectDialogPagePrivate
{
    public:
        KLineEdit *name;
        KUrlRequester* location;
};

GluonCreator::NewProjectDialogPage::NewProjectDialogPage()
    : KPageWidgetItem(new QWidget(), i18n("New Project")),
    d(new NewProjectDialogPagePrivate)
{
    setHeader(i18n("New Project"));
    setIcon(KIcon("document-new"));
    
    QVBoxLayout *layout = new QVBoxLayout(widget());
    QGroupBox* box = new QGroupBox(i18n("General"), widget());
    
    widget()->setLayout(layout);
    layout->addWidget(box);
    
    QFormLayout *boxLayout = new QFormLayout(box);
    box->setLayout(boxLayout);
    
    d->name = new KLineEdit(box);
    boxLayout->addRow(i18n("Project Name"), d->name);
    
    d->location = new KUrlRequester(box);
    d->location->setMode(KFile::Directory);
    boxLayout->addRow(i18n("Project Location"), d->location);
}

GluonCreator::NewProjectDialogPage::~NewProjectDialogPage()
{
    delete d;
}

QString GluonCreator::NewProjectDialogPage::fileName()
{
    if(d->name->text().isEmpty() || d->location->url().isEmpty())
    {
        KMessageBox::error(0, i18n("You need to enter a name and location to continue"));
        return QString();
    }
    
    GluonEngine::GameProject* project = new GluonEngine::GameProject(GluonEngine::Game::instance());
    project->setName(d->name->text());

    GluonEngine::Scene* root = new GluonEngine::Scene(project);
    root->setName(i18n("New Scene"));
    root->savableDirty = true;
    project->addChild(root);
    project->setEntryPoint(root);
    
    GluonEngine::GameObject* camera = new GluonEngine::GameObject(root);
    camera->setName(i18n("Camera"));
    camera->setPosition(0.f, 0.f, 50.f);
    root->sceneContents()->addChild(camera);
    camera->addComponent(qobject_cast<GluonEngine::Component*>(GluonCore::GluonObjectFactory::instance()->instantiateObjectByName("GluonEngine::CameraControllerComponent")));
    
    GluonEngine::GameObject* sprite = new GluonEngine::GameObject(root);
    sprite->setName(i18n("Sprite"));
    root->sceneContents()->addChild(sprite);
    sprite->addComponent(qobject_cast<GluonEngine::Component*>(GluonCore::GluonObjectFactory::instance()->instantiateObjectByName("GluonEngine::SpriteRendererComponent")));
    
    
    KUrl location = d->location->url();
    QString projectFilename = project->fullyQualifiedFileName();
    location.addPath(projectFilename.left(projectFilename.indexOf('.')) + ".gluon");
    project->setFilename(location);
    QDir::setCurrent(d->location->url().toLocalFile());
    project->saveToFile();
    
    delete project;
    
    return location.toLocalFile();
}





