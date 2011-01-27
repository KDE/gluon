#include "threadDocument.h"
#include "graphDocument.h"
#include <QMutex>
#include <KDebug>
#include <KLocale>
#include <QWaitCondition>

ThreadDocument::ThreadDocument( QWaitCondition& docCondition, QMutex& mutex, QObject* parent ):
    QThread( parent ),
    _docCondition( docCondition ), _mutex( mutex )
{
    _graphDocument = 0;
    // _loading = false;
    // _name = i18n("Untitled0");
}

ThreadDocument::~ThreadDocument()
{
}


void ThreadDocument::releaseDocument()
{
    if( _graphDocument )
        _graphDocument->deleteLater();
    _graphDocument = 0;
}

void ThreadDocument::createEmptyDocument()
{
    releaseDocument();
    _graphDocument = new GraphDocument( i18n( "Untitled" ), 800, 600 );
    _docCondition.wakeAll();
    kDebug() << "Waking All";
}

void ThreadDocument::loadDocument( const QString& name )
{
    createEmptyDocument();
    if( name.isEmpty() )
    {
        _graphDocument->addGraph( i18n( "Untitled0" ) );
    }
    else
    {
        _graphDocument->loadFromInternalFormat( name );
    }
    _docCondition.wakeAll();
}

void ThreadDocument::setGraphDocument( GraphDocument* doc )
{
    releaseDocument();
    _graphDocument = doc;
    doc->moveToThread( this );
    _docCondition.wakeAll();
}

void ThreadDocument::run()
{
    loadDocument();
    exec();
}

