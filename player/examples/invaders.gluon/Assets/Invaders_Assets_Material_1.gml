{ GluonCore::GluonObject(Material)
    languageVersion string(1.20)

    vertexShader string(<<<#version 120

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

attribute vec3 vertex;
attribute vec2 uv0;

varying vec2 out_uv0;

void main()
{
    gl_Position = vec4(vertex, 1.0) * ((modelMatrix * viewMatrix) * projectionMatrix);
    out_uv0 = uv0;
}
    <<<)

    fragmentShader string(<<<#version 120

uniform sampler2D texture0;
uniform vec4 materialColor;

varying vec2 out_uv0;

void main()
{
    gl_FragColor = materialColor * texture2D(texture0, out_uv0);
}
    <<<)

    texture0 int(0)
    materialColor color(255;255;255;255)
}