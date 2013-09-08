{ GluonCore::GluonObject("Material")

    vertexShader string("
uniform highp mat4 modelMatrix;
uniform highp mat4 viewMatrix;
uniform highp mat4 projectionMatrix;

attribute highp vec4 vertex;
attribute highp vec2 uv0;

varying highp vec2 out_uv0;

void main()
{
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vertex;
    out_uv0 = uv0;
}
")

    fragmentShader string("
uniform sampler2D texture0;
uniform mediump vec4 materialColor;
varying highp vec2 out_uv0;

void main()
{
    mediump vec4 texColor = texture2D(texture0, out_uv0);
    mediump vec4 color = materialColor * texColor;
    gl_FragColor = vec4(color.r, color.g, color.b, texColor.a);
}
")

    texture0 int(0)
    materialColor rgba(255;255;255;255)
}
