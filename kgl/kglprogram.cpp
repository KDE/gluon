/*
 * This file is part of the Gluon library.
 * Copyright 2008 Rivo Laks <rivolaks@hot.ee>
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

#include "kglprogram.h"

#include "kglshader.h"

#include <QList>
#include <QString>
#include <QHash>
#include <QVariant>
#include <QMetaType>
#include <KDebug>


KGLProgram::KGLProgram()
{
    init();
}

KGLProgram::KGLProgram(const QList<KGLShader*>& shaders)
{
    init();
    addShaders(shaders);
    link();
}

KGLProgram::KGLProgram(const QString& vertexshaderfile, const QString& fragmentshaderfile)
{
    init();
    // Load both shaders, even if one is invalid. This way developer can see
    //  any errors/warnings for both shaders at once.
    KGLVertexShader vs(vertexshaderfile);
    KGLFragmentShader fs(fragmentshaderfile);
    if (!vs.isValid() || !fs.isValid()) {
        return;
    }
    addShader(&vs);
    addShader(&fs);
    link();
}

KGLProgram::~KGLProgram()
{
    glDeleteProgram(glId());
    delete[] mLinkLog;
    delete mUniformLocations;
    delete mAttributeLocations;
    delete mUniformParameters;
    mUniformParameters = 0;
}

void KGLProgram::init()
{
    // Create program object
    mGLId = glCreateProgram();
    mValid = false;
    mLinkLog = 0;
    mUniformLocations = mAttributeLocations = 0;
    mUniformParameters = new QHash<QString, QVariant>;
}

void KGLProgram::addShader(KGLShader* shader)
{
    if (!shader->isValid()) {
        kDebug()<< "Program::addShader(): Cannot add invalid shader";
        return;
    }
    // Attach the shader to the program
    glAttachShader(glId(), shader->glId());
}

void KGLProgram::addShaders(const QList<KGLShader*>& shaders)
{
    foreach (KGLShader* s, shaders) {
        addShader(s);
    }
}

bool KGLProgram::link()
{
    // Link the program
    glLinkProgram(glId());
    // Make sure it linked correctly
    int linked;
    glGetProgramiv(glId(), GL_LINK_STATUS, &linked);
    mValid = linked;
    // Get info log
    GLsizei logsize, logarraysize;
    glGetProgramiv(glId(), GL_INFO_LOG_LENGTH, &logarraysize);
    mLinkLog = new char[logarraysize];
    glGetProgramInfoLog(glId(), logarraysize, &logsize, mLinkLog);
    if (!mValid) {
        kDebug()<< "Program::link(): Couldn't link program. Log follows:" << endl << mLinkLog;
    } else {
        mUniformLocations = new QHash<QString, int>;
        mAttributeLocations = new QHash<QString, int>;
    }
    if (!logsize) {
        delete[] mLinkLog;
        mLinkLog = 0;
    }
    return mValid;
}

void KGLProgram::bind() const
{
  glUseProgram(glId());
  QHash<QString, QVariant>::iterator itr = mUniformParameters->begin();
  for(; itr != mUniformParameters->end(); ++itr)
  {
    int location = uniformLocation(itr.key());
    if (location >= 0)
    {
      switch(itr.value().type())
      {
        case QMetaType::Int:
        {
          glUniform1i(location, itr.value().toInt());
          break;
        }
        case QMetaType::Float:
        {
          glUniform1f(location, itr.value().value<float>());
          break;
        }
        default:
          break;
      }
    }
  }
}

void KGLProgram::unbind() const
{
glUseProgram(0);
}

int KGLProgram::uniformLocation(const QString& name)
{
    return uniformLocation(name.toLatin1().data());
}

int KGLProgram::uniformLocation(const char* name)
{
    if (!mValid) {
        return -1;
    }
    if (!mUniformLocations->contains(name)) {
        int location = glGetUniformLocation(glId(), name);
        mUniformLocations->insert(name, location);
    }
    return mUniformLocations->value(name);
}

int KGLProgram::uniformLocation(const QString& name) const
{
  if (!mValid) {
    return -1;
  }
  const char* name_cstr = name.toLatin1().data();
  if (!mUniformLocations->contains(name_cstr)) {
    int location = glGetUniformLocation(glId(), name_cstr);
    mUniformLocations->insert(name_cstr, location);
  }
  return mUniformLocations->value(name_cstr);
}

int KGLProgram::attributeLocation(const QString& name)
{
    return attributeLocation(name.toLatin1().data());
}

int KGLProgram::attributeLocation(const char* name)
{
    if (!mValid) {
        return -1;
    }
    if (!mAttributeLocations->contains(name)) {
        int location = glGetAttribLocation(glId(), name);
        mAttributeLocations->insert(name, location);
    }
    return mAttributeLocations->value(name);
}

void KGLProgram::invalidateLocations()
{
    mUniformLocations->clear();
    mAttributeLocations->clear();
}

bool KGLProgram::setUniform(const char* name, float value)
{
    int location = uniformLocation(name);
    if (location >= 0) {
        glUniform1f(location, value);
    }
    return (location >= 0);
}

bool KGLProgram::setUniform(const char* name, Eigen::Vector2f value)
{
    int location = uniformLocation(name);
    if (location >= 0) {
        glUniform2fv(location, 1, value.data());
    }
    return (location >= 0);
}

bool KGLProgram::setUniform(const char* name, Eigen::Vector3f value)
{
    int location = uniformLocation(name);
    if (location >= 0) {
        glUniform3fv(location, 1, value.data());
    }
    return (location >= 0);
}

bool KGLProgram::setUniform(const char* name, Eigen::Vector4f value)
{
    int location = uniformLocation(name);
    if (location >= 0) {
        glUniform4fv(location, 1, value.data());
    }
    return (location >= 0);
}

bool KGLProgram::setUniform(const char* name, int value)
{
    int location = uniformLocation(name);
    if (location >= 0) {
        glUniform1i(location, value);
    }
    return (location >= 0);
}

void KGLProgram::declareUniform(const char* name, int value)
{
  mUniformParameters->insert(name, QVariant(value));
}

void KGLProgram::declareUniform(const char* name, float value)
{
  mUniformParameters->insert(name, QVariant(value));
}

