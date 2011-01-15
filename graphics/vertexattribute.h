
#ifndef VERTEXATTRIBUTE_H
#define VERTEXATTRIBUTE_H

#include <QVector>

namespace GluonGraphics
{

    /**
     * \brief A vertex attribute to be used in a vertex buffer
     *
     * A vertex attribute contains information about the vertices
     * composing a mesh.
     */
    class VertexAttribute
    {
        public:
            VertexAttribute();

            /**
             * Creates a vertex attribute.
             *
             * \param name The name of the attribute.
             * \param size The number of fields for a single vertex. E.g. 3 for vertex
             * position (x, y, z), 4 for colors (r, g, b, a), etc.
             **/
            VertexAttribute( const QString& name, int size );
            VertexAttribute( const VertexAttribute& other );
            ~VertexAttribute();

            /**
             * Appends a number to the array.
             *
             * \param data The data to append.
             *
             * \see operator<<
             **/
            void append( float data );

            /**
             * Sets the attribute location given by the material.
             *
             * \param loc The location to set.
             *
             * \see location
             **/
            void setLocation( int loc );

            /**
             * Sets the offset of this attribute in the vertex buffer.
             *
             * \param offset The new offset.
             *
             * \see offset
             **/
            void setOffset( int offset );

            /**
             * Returns the raw data stored.
             **/
            const float *data() const;

            /**
             * Returns the name of the attribute.
             **/
            QString name() const;

            /**
             * Returns the number of entries stored.
             **/
            int itemCount() const;

            /**
             * Returns the number of fields for a single vertex. E.g. 3 for vertex
             * position (x, y, z), 4 for colors (r, g, b, a), etc.
             **/
            int itemSize() const;

            /**
             * Returns the size in bytes of the raw data stored.
             **/
            int size() const;

            /**
             * Returns the attribute location in the material.
             *
             * \see setLocation
             **/
            int location() const;

            /**
             * Returns the offset of the attribute in the vertex buffer.
             *
             * \see setOffset
             **/
            int offset() const;

            VertexAttribute& operator=( const VertexAttribute& other );

            /**
             * Appends a number to the array.
             *
             * \param data The data to append.
             *
             * \see append
             **/
            VertexAttribute& operator<<( float data );

        private:
            class VertexAttributePrivate;
            VertexAttributePrivate* const d;
    };
};

#endif

