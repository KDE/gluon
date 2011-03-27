{ GluonCore::GluonObject(Material)
    
    vertexShader string(<<<
uniform highp mat4 modelMatrix;
uniform highp mat4 viewMatrix;
uniform highp mat4 projectionMatrix;

attribute highp vec3 vertex;
attribute mediump vec4 color;
attribute highp vec2 uv0;

varying mediump vec4 out_color;
varying highp vec2 out_uv0;

void main()
{
    gl_Position = vec4(vertex, 1.0) * ((modelMatrix * viewMatrix) * projectionMatrix);
    out_color = color;
    out_uv0 = uv0;
}
<<<)

    fragmentShader string(<<<
uniform sampler2D texture0;
uniform mediump vec4 materialColor;

varying mediump vec4 out_color;
varying highp vec2 out_uv0;

void main()
{
    mediump vec4 texColor = texture2D(texture0, out_uv0);
    mediump vec4 color = out_color * materialColor * texColor;
    gl_FragColor = vec4(color.r, color.g, color.b, texColor.a * materialColor.a);
}
<<<)

    texture0 int(0)
    materialColor color(255;255;255;255)
}