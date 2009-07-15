#include "kglfx.h"

KGLFx::KGLFx()

{

m_program = new KGLProgram;

}




//===========LIGHT ==========================
KGLLightFx::KGLLightFx()
    :KGLFx()
{
      program()->addShader(new KGLVertexShader(":shaders/light.vert"));
      program()->addShader(new KGLFragmentShader(":shaders/light.frag"));



      program()->link();
}

//==========BLUR =========================
   KGLBlurFx::KGLBlurFx()
        :KGLFx()
   {
      program()->addShader(new KGLVertexShader(":shaders/blur.vert"));
      program()->addShader(new KGLFragmentShader(":shaders/blur.frag"));
      program()->link();
   }

   //========= PIXELATE ====================

   KGLPixelateFx::KGLPixelateFx()
                    :KGLFx()
   {

      program()->addShader(new KGLVertexShader(":shaders/pixelate.vert"));
      program()->addShader(new KGLFragmentShader(":shaders/pixelate.frag"));
      program()->link();


   }
