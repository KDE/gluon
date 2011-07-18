/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (C) 2010 Keith Rusler <xzekecomax@gmail.com>
 * Copyright (C) 2010 Laszlo Papp <lpapp@kde.org>
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

#include <core/gluon_global.h>
#include <engine/gameproject.h>
#include <engine/scene.h>
#include <engine/game.h>
#include <engine/gameobject.h>
#include <engine/component.h>

#include <KDE/KLocalizedString>
#include <KDE/KIcon>
#include <KDE/KLineEdit>
#include <KDE/KUrlRequester>
#include <KDE/KMessageBox>
#include <KDE/KSqueezedTextLabel>

#include <QtGui/QGroupBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QFormLayout>
#include <QtGui/QLabel>
#include <QtCore/QScopedPointer>

using namespace GluonCreator;

class NewProjectDialogPage::NewProjectDialogPagePrivate
{
    public:
        NewProjectDialogPagePrivate( NewProjectDialogPage* qq )
            : name( 0 )
            , location( 0 )
            , locationValidLabel( 0 )
            , q( qq )
        {
        }

    public:
        KLineEdit* name;
        KUrlRequester* location;
        KSqueezedTextLabel* locationValidLabel;

    private:
        NewProjectDialogPage* q;
};

NewProjectDialogPage::NewProjectDialogPage()
    : KPageWidgetItem( new QWidget, i18n( "New Project" ) ),
      d( new NewProjectDialogPagePrivate( this ) )
{
    setIcon( KIcon( "document-new" ) );

    QVBoxLayout* layout = new QVBoxLayout( widget() );
    QGroupBox* box = new QGroupBox( i18n( "General Information" ), widget() );

    widget()->setLayout( layout );
    layout->addWidget( box );

    QFormLayout* boxLayout = new QFormLayout( box );
    box->setLayout( boxLayout );

    d->name = new KLineEdit( box );
    d->name->setPlaceholderText( i18n( "Enter the name for a new game project" ) );
    boxLayout->addRow( i18n( "Project Name" ), d->name );

    d->location = new KUrlRequester( box );
    d->location->setMode( KFile::Directory );
    QFileInfo locInfo( QDir::currentPath() );
    if( locInfo.isWritable() )
        d->location->setUrl( KUrl( QDir::current().absolutePath() ) );
    else
        d->location->setUrl( KUrl( QDir::homePath() ) );
    boxLayout->addRow( i18n( "Project Location" ), d->location );

    d->locationValidLabel = new KSqueezedTextLabel( box );
    boxLayout->addRow( QString(), d->locationValidLabel );

    connect( d->name, SIGNAL( textEdited( const QString& ) ), SLOT( validateByProjectName() ) );
    connect( d->location->lineEdit(), SIGNAL( textEdited( const QString& ) ), SLOT( validateByProjectLocation() ) );

    validateData();
}

NewProjectDialogPage::~NewProjectDialogPage()
{
    delete d;
}

QString NewProjectDialogPage::createProject() const
{
    if( d->name->text().isEmpty() || d->location->url().isEmpty() )
    {
        KMessageBox::error( 0, i18n( "You need to enter a name and location to continue" ) );
        return QString();
    }

    QScopedPointer<GluonEngine::GameProject> project( new GluonEngine::GameProject( GluonEngine::Game::instance() ) );
    if( project.isNull() )
    {
        return QString();
    }

    project->setName( d->name->text() );

    GluonCore::GluonObject* scenesFolder = new GluonCore::GluonObject( "Scenes" );

    GluonEngine::Scene* root = new GluonEngine::Scene( project.data() );
    root->setGameProject( project.data() );
    root->setName( i18n( "New Scene" ) );
    root->savableDirty = true;

    scenesFolder->addChild( root );
    project->setEntryPoint( root );
    project->addChild( scenesFolder );

    GluonEngine::GameObject* camera = new GluonEngine::GameObject( root );
    camera->setName( i18n( "Camera" ) );
    camera->setPosition( 0.0f, 0.0f, 50.0f );
    root->sceneContents()->addChild( camera );

    GluonCore::GluonObject* cameraController =
        GluonCore::GluonObjectFactory::instance()->instantiateObjectByName( "GluonEngine::CameraControllerComponent" );
    cameraController->setName( "CameraController" );
    camera->addComponent( qobject_cast<GluonEngine::Component*>( cameraController ) );

    GluonEngine::GameObject* sprite = new GluonEngine::GameObject( root );
    sprite->setName( i18n( "Sprite" ) );
    sprite->setScale( 10.f, 10.f, 0.f );
    root->sceneContents()->addChild( sprite );

    GluonCore::GluonObject* spriteComponent =
        GluonCore::GluonObjectFactory::instance()->instantiateObjectByName( "GluonEngine::SpriteRendererComponent" );
    spriteComponent->setName( "SpriteRenderer" );
    sprite->addComponent( qobject_cast<GluonEngine::Component*>( spriteComponent ) );

    project->addChild( new GluonCore::GluonObject( "Assets" ) );
    project->addChild( new GluonCore::GluonObject( "Prefabs" ) );

    KUrl location = d->location->url();
    QString gameBundleDir = GluonEngine::Asset::fullyQualifiedFileName( project.data(), QFileInfo( GluonEngine::projectSuffix ).completeSuffix() ).toLocalFile();
    location.addPath( gameBundleDir );
    project->setDirname( location );
    location.addPath( GluonEngine::projectFilename );
    project->setFilename( location );

    KUrl currentLocation = d->location->url();
    currentLocation.addPath( gameBundleDir );
    QDir dir = QDir( d->location->text() );
    dir.mkpath( gameBundleDir );
    QDir::setCurrent( currentLocation.toLocalFile() );
    project->saveToFile();

    return location.toLocalFile();
}

void NewProjectDialogPage::setForeground( QLabel* label, KColorScheme::ForegroundRole role )
{
    QPalette p = label->palette();
    KColorScheme::adjustForeground( p, role, label->foregroundRole(), KColorScheme::Window );
    label->setPalette( p );
}


void NewProjectDialogPage::validateByProjectName()
{
    validateData();
}

void NewProjectDialogPage::validateByProjectLocation()
{
    validateData();
}

void NewProjectDialogPage::validateData()
{
    KUrl url = d->location->url();
    if( !url.isLocalFile() || url.isEmpty() )
    {
        d->locationValidLabel->setText( i18n( "Invalid location" ) );
        setForeground( d->locationValidLabel, KColorScheme::NegativeText );
        emit validationFinished( false );
        return;
    }

    QString appName = d->name->text();

    if( appName.isEmpty() )
    {
        d->locationValidLabel->setText( i18n( "Empty project name" ) );
        setForeground( d->locationValidLabel, KColorScheme::NegativeText );
        emit validationFinished( false );
        return;
    }

    if( appName == "." || appName == ".." )
    {
        d->locationValidLabel->setText( i18n( "Invalid project name" ) );
        setForeground( d->locationValidLabel, KColorScheme::NegativeText );
        emit validationFinished( false );
        return;
    }

    QDir tDir( url.toLocalFile( KUrl::RemoveTrailingSlash ) );
    while( !tDir.exists() && !tDir.isRoot() )
        tDir.setPath( pathUp( tDir.absolutePath() ) );

    if( tDir.exists() )
    {
        QFileInfo tFileInfo( tDir.absolutePath() );
        if( !tFileInfo.isWritable() || !tFileInfo.isExecutable() )
        {
            d->locationValidLabel->setText( i18n( "Unable to create subdirectories, "
                                                  "missing permissions on: %1", tDir.absolutePath() ) );
            setForeground( d->locationValidLabel, KColorScheme::NegativeText );
            emit validationFinished( false );
            return;
        }
    }

    d->locationValidLabel->setText( QString( " " ) );
    setForeground( d->locationValidLabel, KColorScheme::NormalText );
    emit validationFinished( true );

    // Check for non-empty target directory. Not an error, but need to display a warning.
    url.addPath( encodedAppName() );
    QFileInfo fi( url.toLocalFile( KUrl::RemoveTrailingSlash ) );
    if( fi.exists() && fi.isDir() )
    {
        if( !QDir( fi.absoluteFilePath() ).entryList( QDir::NoDotAndDotDot | QDir::AllEntries ).isEmpty() )
        {
            d->locationValidLabel->setText( i18n( "Path already exists and contains files" ) );
            setForeground( d->locationValidLabel, KColorScheme::NegativeText );
        }
    }
}

bool NewProjectDialogPage::isModified() const
{
    return ( !d->name->text().isEmpty() || !d->location->url().isEmpty() );
}

QByteArray NewProjectDialogPage::encodedAppName()
{
    // : < > * ? / \ | " are invalid on windows
    QByteArray tEncodedName = d->name->text().toUtf8();
    for( int i = 0; i < tEncodedName.size(); ++i )
    {
        QChar tChar( tEncodedName.at( i ) );
        if( tChar.isDigit() || tChar.isSpace() || tChar.isLetter() || tChar == '%' )
            continue;

        QByteArray tReplace = QUrl::toPercentEncoding( tChar );
        tEncodedName.replace( tEncodedName.at( i ) , tReplace );
        i =  i + tReplace.size() - 1;
    }
    return tEncodedName;
}

QString NewProjectDialogPage::pathUp( const QString& aPath )
{
    QString tPath = aPath;
    int tIndex = tPath.lastIndexOf( QDir::separator() );
    tPath = tPath.remove( tIndex, tPath.length() - tIndex );
    return tPath;
}

