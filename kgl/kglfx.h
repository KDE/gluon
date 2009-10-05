/*
 * This file is part of the Gluon library.
 * Copyright 2009 Gluon team
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

#ifndef KGLEFFECT_H
#define KGLEFFECT_H

#include <QString>
#include "kgl_export.h"
#include "kglprogram.h"
#include "kglshader.h"

/**
 * \defgroup KGL KGL
 */
//@{

class KGLFx;

class KGL_EXPORT KGLFx : public KGLProgram
{

public:
    KGLFx(const QString& vertexShader, const QString& fragmentShader);
    KGLFx();
};

/* @short KGLLightFx class
 *
 * Add Lighter . setAlpha between 1 and 10
 **/
class KGLLightFx: public KGLFx
{
public :
        KGLLightFx();
void setAlpha(float alpha);
float alpha(){
    return m_alpha;
}
 private:
float m_alpha;
};

/* @short KGLLightFx class
 *
 * Add Posterize effect . SetLevel between 1 and 20.
 **/
class KGLPosterizeFx : public KGLFx
{
public :
        KGLPosterizeFx();
void setLevel(float level);
float level(){
    return m_level;
}
private:
float m_level;

};
/* @short KGLLightFx class
 *
 * Add Mosaic effect . SetLevel between 1 and 256.
 **/
class KGLMosaicFx : public KGLFx
{
  public :
          KGLMosaicFx();
  void setTileSize(float t);
  private:
  float m_tileSize;
};









//class KGLFx
//{
//    public:
//        KGLFx();
//        void bind()
//        {
//            if (program()->isValid())
//            {
//                program()->bind();
//            }
//        }
//
//        void unbind()
//        {
//            program()->unbind();
//        }
//
//        bool enable()
//        {
//            if ((program()->isValid()) && (program()!=NULL))
//            {
//                return true;
//            }
//            else
//            {
//                return false;
//            }
//        }
//
//        KGLProgram* program()
//        {
//            return m_program;
//        }
//
//        void setArg(const char* name, int value)
//        {
//            program()->bind();
//            program()->setUniform(name, value);
//            program()->unbind();
//        }
//
//        void setArg(const char* name,float value)
//        {
//            program()->bind();
//            program()->setUniform(name, value);
//            program()->unbind();
//        }
//
//    private:
//        KGLProgram * m_program;
//    };
//
////===================LIGHT============================================
//
//class KGLLightFx: public KGLFx
//{
//    public:
//        KGLLightFx();
//
//        void setLight(float l)
//        {
//            setArg("alpha",l);
//        }
//};
////
////====================BLUR===============================================
//
//class KGLBlurFx : public KGLFx
//{
//    public:
//        KGLBlurFx();
//
//        void setBlur(float b)
//        {
//            m_blur = b;
//            setArg("blurfactor", b);
//        }
//
//    private:
//        float  m_blur;
//};


//@}
#endif // KGLEFFECT_H
