#ifndef KGLEFFECT_H
#define KGLEFFECT_H

#include  "kglprogram.h"
class KGLFx
{
public:
    KGLFx();
    void bind(){if ( program()->isValid())program()->bind();}
    void unbind(){program()->unbind();}
    bool enable()
    {
        if ((program()->isShaderSupported()) && (program()->isValid()) && (program()!=NULL))
            return true;
        else return false;
    }
    KGLProgram* program(){return m_program;}
    void setArg(const char* name, int value)
    {
        program()->bind();
        program()->setUniform(name, value);
        program()->unbind();
    }
    void setArg(const char* name,float value)
    {
        program()->bind();
        program()->setUniform(name, value);
        program()->unbind();
    }


private:
    KGLProgram * m_program;
};
//===================LIGHT============================================
class KGLLightFx: public KGLFx
{
public:
    KGLLightFx();
void setLight(float l){setArg("alpha",l);}


};
//====================BLUR===============================================
class KGLBlurFx : public KGLFx
{
public:
    KGLBlurFx();
    void setBlur(float b)
    {
        m_blur = b;
        setArg("blurfactor", b);
    }
private:
    float  m_blur;
};


//===================PIXELATE====================================================================
//uniform float Angle; // range 2pi / 100000.0 to 1.0 (rounded down), exponential
//uniform float AngleMin; // range -3.2 to 3.2
//uniform float AngleWidth; // range 0.0 to 6.4
//uniform float Radius; // range -10000.0 to 1.0
//uniform float RadiusMin; // range 0.0 to 2.0
//uniform float RadiusWidth; // range 0.0 to 2.0
//uniform vec2 Center; // range: -1.0 to 3.0

class KGLPixelateFx : public KGLFx
{
public:
    KGLPixelateFx();
    void setAngle(const float& a){setArg("Angle",a);}
    void setAngleMin(const float &a){setArg("AngleMin",a);}
    void setAngleWidth(const float &a){setArg("AngleWidth",a);}
    void setRadius(const float &r){setArg("Radius",r);}
    void setRadiusMin(const float &r){setArg("RadiusMin",r);}
    void setRadiusWidth(const float &r){setArg("RadiusWidth",r);}

private:
    float  m_blur;
};







#endif // KGLEFFECT_H
