{ GluonCore::GluonObject(Material)
    vertexShader string(<<<
uniform highp mat4 modelMatrix;
uniform highp mat4 viewMatrix;
uniform highp mat4 projectionMatrix;

attribute highp vec3 vertex;
attribute mediump vec2 uv0;

varying highp vec2 out_uv0;

void main()
{
	gl_Position = vec4(vertex, 1.0) * ((modelMatrix * viewMatrix) * projectionMatrix);
	out_uv0 = uv0;
}
    <<<)

    fragmentShader string(<<<
uniform sampler2D texture0;

varying mediump vec2 out_uv0;

void main()
{
	gl_FragColor = texture2D(texture0, out_uv0);
}
    <<<)

    texture0 int(0)
}