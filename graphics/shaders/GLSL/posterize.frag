uniform sampler2D tex;

uniform float level;

void main()
{
  vec4 outColor = texture2D(tex, gl_TexCoord[0].st);
  outColor = outColor * gl_Color;

  outColor.r = floor(outColor.r * level) / level;
  outColor.g = floor(outColor.g * level) / level;
  outColor.b = floor(outColor.b * level) / level;
  
  gl_FragColor = outColor;
}