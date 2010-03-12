#ifndef LIGHTSHADER_H
#define LIGHTSHADER_H

#include <QGLShaderProgram>
#include <QObject>
#include "../gluon_graphics_export.h"

namespace GluonGraphics
{
    class GLUON_GRAPHICS_EXPORT LightShader : public QGLShaderProgram
    {

    public:
        LightShader(QObject *parent = 0);
        void setAlpha(const float& value);
        const float& alpha()
        {
            return mAlpha;
        }

    private:
        QGLShader * vertexShader;
        QGLShader * fragmentShader;
        float mAlpha;
    };
}
#endif // LIGHTSHADER_H
