//Uniform input parameters
//The size of the tiles
uniform int amount;
//Size of the texture used
uniform int texSize;
//Texture
uniform sampler2D tex;

void main()
{
  vec4 outColor;

  float w = 1/float(texSize / amount);

  float s = floor(gl_TexCoord[0].s / w);
  float t = floor(gl_TexCoord[0].t / w);

  float ct = float(w / 2);

  vec2 texCoord = vec2(s * w + ct, t * w + ct);

  //texCoord = gl_TexCoord[0].st;

  outColor = texture2D(tex, texCoord);
  gl_FragColor = outColor;
}
