{ GluonCore::GluonObject("Material")
    languageVersion string("1.20")

    vertexShader string("
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

attribute vec3 vertex;
attribute vec4 color;
attribute vec2 uv0;

varying vec2 out_uv0;

void main()
{
    gl_Position = vec4(vertex, 1.0) * ((modelMatrix * viewMatrix) * projectionMatrix);
    out_uv0 = uv0;
}
")

    fragmentShader string("
uniform sampler2D texture0;
uniform vec4 materialColor;

varying vec2 out_uv0;

void main()
{
    vec4 texColor = texture2D(texture0, out_uv0);
    if(texColor.a < 0.1)
        discard;
    vec4 color = materialColor * texColor;
    gl_FragColor = vec4(texColor.r * materialColor.r, texColor.g * materialColor.g, texColor.b * materialColor.b, texColor.a);
}
")

    texture0 int(0)
    materialColor rgba(255;255;255;255)
}