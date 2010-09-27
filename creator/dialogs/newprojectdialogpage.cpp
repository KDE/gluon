/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (C) 2010 Keith Rusler <xzekecomax@gmail.com>
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
#include <QtCore/QScopedPointer>

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
        NewProjectDialogPagePrivate(NewProjectDialogPage* qq)
            : name(0),
            location(0),
            q(qq)
        {
        }
    public:
        KLineEdit* name;
        KUrlRequester* location;
    private:
        NewProjectDialogPage* q;
};

NewProjectDialogPage::NewProjectDialogPage()
    : KPageWidgetItem(new QWidget, i18n("New Project")),
    d(new NewProjectDialogPagePrivate(this))
{
    setIcon(KIcon("document-new"));

    QVBoxLayout* layout = new QVBoxLayout(widget());
    QGroupBox* box = new QGroupBox(i18n("General Information"), widget());

    widget()->setLayout(layout);
    layout->addWidget(box);

    QFormLayout* boxLayout = new QFormLayout(box);
    box->setLayout(boxLayout);

    d->name = new KLineEdit(box);
    boxLayout->addRow(i18n("Project Name"), d->name);

    d->location = new KUrlRequester(box);
    d->location->setMode(KFile::Directory);
    boxLayout->addRow(i18n("Project Location"), d->location);
}

NewProjectDialogPage::~NewProjectDialogPage()
{
    delete d;
}

QString NewProjectDialogPage::createProject() const
{
    if (d->name->text().isEmpty() || d->location->url().isEmpty()) {
        KMessageBox::error(0, i18n("You need to enter a name and location to continue"));
        return QString();
    }

    QScopedPointer<GluonEngine::GameProject> project(new GluonEngine::GameProject(GluonEngine::Game::instance()));
    if (project.isNull()) {
        return QString();
    }

    project->setName(d->name->text());

    GluonEngine::Scene* root = new GluonEngine::Scene(project.data());
    root->setName(i18n("New Scene"));
    root->savableDirty = true;

    project->addChild(root);
    project->setEntryPoint(root);

    GluonEngine::GameObject* camera = new GluonEngine::GameObject(root);
    camera->setName(i18n("Camera"));
    camera->setPosition(0.0f, 0.0f, 50.0f);
    root->sceneContents()->addChild(camera);

    GluonCore::GluonObject* cameraController =
        GluonCore::GluonObjectFactory::instance()->instantiateObjectByName("GluonEngine::CameraControllerComponent");
    cameraController->setName("CameraController");
    camera->addComponent(qobject_cast<GluonEngine::Component*>(camera));

    GluonEngine::GameObject* sprite = new GluonEngine::GameObject(root);
    sprite->setName(i18n("Sprite"));
    root->sceneContents()->addChild(sprite);

    GluonCore::GluonObject* spriteComponent =
        GluonCore::GluonObjectFactory::instance()->instantiateObjectByName("GluonEngine::SpriteRendererComponent");
    spriteComponent->setName("SpriteRenderer");
    sprite->addComponent(qobject_cast<GluonEngine::Component*>(spriteComponent));

    KUrl location = d->location->url();
    QString projectFileName = project->fullyQualifiedFileName();
    location.addPath(projectFileName.left(projectFileName.indexOf('.')) + ".gluon");
    project->setFilename(location);

    QDir::setCurrent(d->location->url().toLocalFile());
    project->saveToFile();

    return location.toLocalFile();
}

bool NewProjectDialogPage::isModified() const
{
    return (!d->name->text().isEmpty() || !d->location->url().isEmpty());
}
