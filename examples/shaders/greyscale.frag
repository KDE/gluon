uniform sampler2D tex;

void main()
{
  vec4 outColor = texture2D(tex, gl_TexCoord[0].st);
  outColor = outColor * gl_Color;
  float value = (outColor.r + outColor.g + outColor.b)/3;
  gl_FragColor = vec4(value , value, value, outColor.a);
}