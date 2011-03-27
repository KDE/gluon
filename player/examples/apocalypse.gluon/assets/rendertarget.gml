{ GluonCore::GluonObject(Material)
    vertexShader string(<<<
        uniform mat4 modelMatrix;
        uniform mat4 viewMatrix;
        uniform mat4 projectionMatrix;

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
        uniform mediump vec4 materialColor;
        varying mediump vec2 out_uv0;

        void main()
        {
            gl_FragColor = materialColor * texture2D(texture0, out_uv0);
        }
    <<<)
}