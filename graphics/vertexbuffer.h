
#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <QObject>

namespace GluonGraphics
{
    class VertexAttribute;
    class MaterialInstance;

    /**
     * \brief A wrapper class around a GL vertex buffer object (VBO).
     *
     * A VertexBuffer takes any number of VertexAttribute and uses them
     * to create and draw a GL vertex buffer.
     */
    class VertexBuffer : public QObject
    {
        Q_OBJECT
        public:
            VertexBuffer( QObject* parent = 0 );
            ~VertexBuffer();

            /**
             * Add a vertex attribute to the list of attributes that will
             * be used by initialize().
             *
             * \param attribute The attribute to be added.
             **/
            void addAttribute( const VertexAttribute& attribute );

            /**
             * Create an OpenGL buffer and store the previously added attributes.
             *
             * \see isInitialized
             */
            void initialize();

            /**
             * Render the local OpenGL buffer.
             *
             * \param mode The OpenGL mode to use, for example GL_TRIAGLES.
             * \param material The material to get attribute locations from.
             */
            void render( uint mode, GluonGraphics::MaterialInstance* material );

            /**
             * Returns true if initialize was called.
             *
             * \see initialize
             **/
            bool isInitialized() const;

        private:
            class VertexBufferPrivate;
            VertexBufferPrivate* const d;
    };
};

#endif
