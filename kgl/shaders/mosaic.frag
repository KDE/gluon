//Uniform input parameters
//The size of the tiles
uniform int size;
//Width of the texture used
uniform int texWidth;
//Height of the texture used
uniform int texHeight;
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

  outColor = texture2D(tex, texCoord);
  gl_FragColor = outColor;
}
