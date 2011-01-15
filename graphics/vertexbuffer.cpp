
#include "vertexbuffer.h"

#include "materialinstance.h"
#include "vertexattribute.h"
#include "glheaders.h"

using namespace GluonGraphics;

class VertexBuffer::VertexBufferPrivate
{
    public:
        VertexBufferPrivate()
            : buffer( 0 )
            , indexBuffer( 0 )
        {
        }

        GLuint buffer;
        GLuint indexBuffer;
        QList<VertexAttribute> attributes;
        QVector<uint> indices;
};

VertexBuffer::VertexBuffer( QObject* parent )
            : QObject( parent )
            , d( new VertexBufferPrivate() )
{

}

VertexBuffer::~VertexBuffer()
{
    delete d;
}

void VertexBuffer::addAttribute( const VertexAttribute& attribute )
{
    d->attributes << attribute;
}

void VertexBuffer::setIndices( const QVector<uint>& indices )
{
    d->indices = indices;
}

bool VertexBuffer::isInitialized() const
{
    return d->buffer != 0;
}

void VertexBuffer::initialize()
{
    if( d->attributes.isEmpty() )
    {
        return;
    }

    glGenBuffers( 1, &d->buffer );
    glBindBuffer( GL_ARRAY_BUFFER, d->buffer );
    int size = 0;
    foreach( const VertexAttribute& attribute, d->attributes )
    {
        size += attribute.size();
    }

    glBufferData( GL_ARRAY_BUFFER, size, 0, GL_STATIC_DRAW );

    int offset = 0;
    for( int i = 0; i < d->attributes.size(); ++i )
    {
        VertexAttribute& attribute = d->attributes[i];
        attribute.setOffset( offset );
        glBufferSubData( GL_ARRAY_BUFFER, offset, attribute.size(), attribute.data() );
        offset += attribute.size();
    }

    glBindBuffer( GL_ARRAY_BUFFER, 0 );

    glGenBuffers( 1, &d->indexBuffer );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, d->indexBuffer );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, d->indices.size() * sizeof( float ), 0, GL_STATIC_DRAW );
    glBufferSubData( GL_ELEMENT_ARRAY_BUFFER, 0, d->indices.size() * sizeof( float ), d->indices.data() );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
}

void VertexBuffer::render( uint mode, GluonGraphics::MaterialInstance* material )
{
    if( d->buffer == 0 )
    {
        return;
    }

    glBindBuffer( GL_ARRAY_BUFFER, d->buffer );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, d->indexBuffer );

    for( int i = 0; i < d->attributes.size(); ++i )
    {
        VertexAttribute& attribute = d->attributes[i];
        if( attribute.location() == -1 )
            attribute.setLocation( material->attributeLocation( attribute.name() ) );

        glVertexAttribPointer( attribute.location(), attribute.itemSize(),
                               GL_FLOAT, 0, 0, ( void* )( attribute.offset() ) );
        glEnableVertexAttribArray( attribute.location() );
    }

    glDrawElements( mode, d->indices.count(), GL_UNSIGNED_INT, 0);

    foreach( const VertexAttribute& attribute, d->attributes )
    {
        glDisableVertexAttribArray( attribute.location() );
    }

    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
}

#include "vertexbuffer.moc"
