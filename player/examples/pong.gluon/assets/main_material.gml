{ GluonCore::GluonObject(Material)
    languageVersion string(1.20)

    vertexShader string(<<<#version 120

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

attribute vec3 vertex;
attribute vec4 color;
attribute vec2 uv0;

varying vec4 out_color;
varying vec2 out_uv0;

void main()
{
    gl_Position = vec4(vertex, 1.0) * ((modelMatrix * viewMatrix) * projectionMatrix);
    out_color = color;
    out_uv0 = uv0;
}
<<<)

    fragmentShader string(<<<#version 120

uniform sampler2D texture0;
uniform vec4 materialColor;

varying vec4 out_color;
varying vec2 out_uv0;

void main()
{
    vec4 texColor = texture2D(texture0, out_uv0);
    vec4 color = out_color * materialColor * texColor;
    color = vec4(color.r, color.g, color.b, texColor.a * materialColor.a);
    if(color.a <= 0.0)
        discard;
    gl_FragColor = color;
}
<<<)

    texture0 int(0)
    materialColor color(255;255;255;255)
}