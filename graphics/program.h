/*
 * This file is part of the Gluon library.
 * Copyright 2008 Riva Laks <rivolaks@hot.ee>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef GLUON_GRAPHICS_PROGRAM_H
#define GLUON_GRAPHICS_PROGRAM_H

#include "gluon_graphics_export.h"

class QString;
class QVariant;
template<class T> class QList;
template<class K, class V> class QHash;

#include "shader.h"

#include <QVector2D>
#include <QVector3D>
#include <QVector4D>

//Q_DECLARE_METATYPE(float);

/**
 * \defgroup
 */
//@{

/**
 * @short Program class
 *
 * Program is a GPU-executed program that is ready to be used for manipulating
 *  geometry and colors.
 * Program can encapsulate vertex and fragment shaders or just one of them. If
 *  only either vertex or fragment shader is used, then traditional
 *  fixed-function pipeline is used for the other stage.
 *
 * @section creating Creating Program objects
 * The easiest way to create usable Program object is to pass filenames of the
 *  vertex- and fragment shader to the Program constructor. This automatically
 *  creates temporary Shader objects and then combines them into a Program:
 * @code
 * Program* prog = new Program("myshader.vert", "myshader.frag");
 * if (!prog->isValid()) {
 *     // Error: program failed to load
 * }
 * @endcode
 *
 * It is also possible to add more than one fragment or vertex shader (e.g. you
 *  can have some common functions in one shader and the main() function in
 *  other) or specify only vertex or only fragment shader. In this case you
 *  will have to first create the Shader objects yourself and then add them to
 *  a program:
 * @code
 * // Create Shader objects
 * VertexShader vertexShader("myshader.vert");
 * FragmentShader fragmentShader("myshader.frag");
 * // common.frag could contain common functions shared by different shaders
 * FragmentShader commonShader("common.frag");
 * // Make sure all shaders were successfully loaded
 * if (!vertexShader.isValid() || !fragmentShader.isValid() || !commonShader.isValid()) {
 *     // handle the error here
 *     return;
 * }
 *
 * // Create Program object
 * Program* prog = new Program();
 * // Add shader objects to program
 * prog->addShader(&vertexShader);
 * prog->addShader(&fragmentShader);
 * prog->addShader(&commonShader);
 * // Finally link them together
 * prog->link();
 * // And make sure everything succeeded
 * if (!prog->isValid()) {
 *     // handle the error
 * }
 * @endcode
 *
 * @section binding Binding
 * To use the program, you need to first bind() it, then render your geometry
 *  and finally unbind() it. Note that it's more convenient to use the Mesh
 *  class which takes care of the binding and unbinding automatically.
 * @code
 * prog->bind();
 * // Everything rendered now will use the bound program
 * renderObjects();
 * // Finally unbind the program
 * prog->unbind();
 * @endcode
 *
 * @section uniforms Uniform variables
 * For communication between GPU Program and your main application, uniform
 *  variables can be used. They can be written from your main program and read
 *  in shader code. Note that modifying values of uniform variables may be
 *  expensive, thus you should do it only when really necessary.
 * @code
 * // The program has to be bound before setUniform() can be used
 * prog->bind();
 * // Set variable "objectScale" to 2.0f
 * prog->setUniform("objectScale", 2.0f);
 * // Unbind the program
 * prog->unbind();
 * @endcode
 *
 * The corresponding section in the shader code would look like this:
 * @code
 * uniform float objectScale;
 * // objectScale can now be used as any other variable
 * @endcode
 *
 * @see Shader, Mesh
 **/
namespace GluonGraphics
{
    class Shader;
class GLUON_GRAPHICS_EXPORT  Program
{
    public:
        /**
         * Creates empty Program.
         * You will need to add some shaders and link the program before you can
         * use it.
         **/
         Program();
        /**
         * Creates Program, adds given list of shaders and links the program.
         * If linking succeeded, the program is ready to be used.
         **/
         Program(const QList<Shader*>& shaders);
        /**
         * Loads vertex and fragment shaders from given files, adds them and links
         * the program.
         * If everything succeeded, then the program is ready to be used.
         **/
        Program(const QString& vertexshaderfile, const QString& fragmentshaderfile);
       /**
        * Deletes this library and frees all resources.
        **/
        virtual ~Program();

       /**
        * Adds given shader to this library.
        **/
        void addShader(Shader* shader);
       /**
        * Adds all shaders in the given list to this library.
        **/
        void addShaders(const QList<Shader*>& shaders);

       /**
        * Tries to link the shader.
        * If it succeeds, then the program is ready to be used.
        * If there are errors, they should be visible in the @ref linkLog.
        * @return whether linking succeeded.
        **/
        virtual bool link();

       /**
        * Returns true if this library can be used for rendering, false otherwise.
        *
        * Invalid programs can be result of syntax errors in the shader code.
        *  Program which hasn't been linked yet is also invalid.
        *
        * @see link(), linkLog()
        **/
        bool isValid() const
        {
            return mValid;
        }
       /**
        * @return Link log of the program or null if there was none or the program
        *  hasn't been linked yet.
        * Note that @ref Program keeps ownership of the returned string, so you
        * mustn't delete it.
        * TODO: maybe return QString?
        **/
        char* linkLog() const
        {
            return mLinkLog;
        }

       /**
        * Binds the program so that it will be used for anything that is rendered
        * after the bind() call.
        *
        * @see unbind()
        **/
        virtual void bind() const;
       /**
        * Unbind the program. Anything rendered after unbind() call will be
        *  rendered using the fixed-function pipeline.
        * Note that if you want to change the currently used program, you needn't
        *  call unbind() before bind()ing the next program.
        *
        * @see bind()
        **/
        virtual void unbind() const;

        int uniformLocation(const QString& name);
        int uniformLocation(const char* name);

        int uniformLocation(const QString& name) const;

        int attributeLocation(const QString& name);
        int attributeLocation(const char* name);

        void invalidateLocations();

       /**
        * Sets the uniform with the given name to the given value and returns
        *  true.
        * If there is no uniform with such name then false is returned.
        *
        * Note that the program has to be bound before this method can be used.
        *
        * @see bind()
        **/
        bool setUniform(const char* name, float value);
       /**
        * @overload
        **/
        bool setUniform(const char* name, QVector2D value);
       /**
        * @overload
        **/
        bool setUniform(const char* name, QVector3D value);
       /**
        * @overload
        **/
        bool setUniform(const char* name, QVector4D value);
       /**
        * @overload
        **/
        bool setUniform(const char* name, int value);

       /**
        * @return OpenGL id (aka handle) of this library.
        **/
        GLuint glId() const
        {
            return mGLId;
        }

        /**
        * Declare a uniform parameter to be used when the program is bound.
        * This will call setUniform(name, value) once bind() has been called.
        */
        //void declareUniform(const char* name, int value);

        //void declareUniform(const char* name, float value);


    protected:
        void init();

    protected:
        GLuint mGLId;
        bool mValid;
        char* mLinkLog;
        QHash<QString, int>* mUniformLocations;
        QHash<QString, int>* mAttributeLocations;

        QHash<QString, QVariant>* mUniformParameters;
private:
    bool mIsBound;
};
}//namespace
//@}
#endif //PROGRAM_H
