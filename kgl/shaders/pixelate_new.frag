//uniform float amount;
uniform sampler2D tex;

void main()
{
  float amount = 5.0;
  
  vec4 outColor;

  vec2 texCoord = gl_TexCoord[0].st;
  //vec2 texSize = textureSize(tex);

  /*int w = texSize.x; /// int(amount);
  int h = texSize.y; // / int(amount);
  */
  //vec2 modCoord = texCoord;
  /*//modCoord.s = int(texCoord.s / amount) * w;
  //modCoord.t = int(texCoord.t / amount) * h;
    */
  outColor = texture2D(tex, texCoord);
  gl_FragColor = outColor;
}
