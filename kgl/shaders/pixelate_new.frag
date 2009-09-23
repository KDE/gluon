uniform float amount;
uniform sampler2D tex;

void main()
{
  vec4 outColor;
  
  outColor = texture2D(tex, gl_TexCoord[0].st);
  outColor = outColor * 0.5;
  
  gl_FragColor = outColor;
}
