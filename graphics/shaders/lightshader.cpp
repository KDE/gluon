#include "lightshader.h"
#include <QFile>
#include <QDebug>
namespace GluonGraphics
{
    LightShader::LightShader(QObject *parent)
            : QGLShaderProgram(parent)
    {

        mAlpha = 0;
        vertexShader = new QGLShader(QGLShader::Vertex);
        fragmentShader = new QGLShader(QGLShader::Fragment);

        vertexShader->compileSourceFile(":/GLSL/generic.vert");
        fragmentShader->compileSourceFile(":/GLSL/light.frag");

        addShader(vertexShader);
        addShader(fragmentShader);

        link();

        qDebug() << log();

    }

    void LightShader::setAlpha(const float& value)
    {
        mAlpha = value;
        bind();
        setUniformValue("alpha", GLfloat(value));
        release();
    }

}
