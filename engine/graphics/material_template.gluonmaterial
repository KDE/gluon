{ GluonCore::GluonObject("Material")
    #Vertex shader source
    vertexShader string("
        uniform mat4 modelMatrix;
        uniform mat4 viewMatrix;
        uniform mat4 projectionMatrix;

        attribute highp vec3 vertex;
        attribute mediump vec4 color;
        attribute mediump vec2 uv0;

        varying mediump vec4 out_color;
        varying highp vec2 out_uv0;

        void main()
        {
            gl_Position = vec4(vertex, 1.0) * ((modelMatrix * viewMatrix) * projectionMatrix);
            out_color = color;
            out_uv0 = uv0;
        }
    ")

    #Fragment shader source
    fragmentShader string("
        uniform sampler2D texture0;
        uniform mediump vec4 materialColor;

        varying mediump vec4 out_color;
        varying mediump vec2 out_uv0;

        void main()
        {
            mediump vec4 texColor = texture2D(texture0, out_uv0);
            mediump vec4 color = out_color * materialColor * texColor;
            color = vec4(color.r, color.g, color.b, texColor.a * materialColor.a);
            gl_FragColor = color;
        }
    ")

    #Uniform property descriptions
    #Note that the uniform "modelViewProj" from the vertex shader
    #is implied.

    #Uniform 1 from the Fragment shader
    texture0 int(0)
    #Uniform 2 from the Fragment shader
    materialColor rgba(255;255;255;255)
}