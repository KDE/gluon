{ GluonCore::GluonObject(AnimatedSpriteMaterial)
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

    fragmentShader string("
        uniform sampler2D texture0;
        uniform mediump vec4 materialColor;

        uniform highp vec4 frame;

        varying mediump vec4 out_color;
        varying mediump vec2 out_uv0;

        void main()
        {
            highp vec2 uv = vec2(frame.x + (out_uv0.x * frame.z), frame.y + (out_uv0.y * frame.w));
            mediump vec4 texColor = texture2D(texture0, uv);
            mediump vec4 color = out_color * materialColor * texColor;
            gl_FragColor = vec4(color.rgb, texColor.a * materialColor.a);
        }
    ")

}