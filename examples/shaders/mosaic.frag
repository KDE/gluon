//Uniform input parameters
//The size of the tiles
uniform float tileSize;
//Size of the texture used
uniform int texSize;
//Texture
uniform sampler2D tex;

void main()
{
  float w = 1/(float(texSize) / tileSize);

  float s = floor(gl_TexCoord[0].s / w);
  float t = floor(gl_TexCoord[0].t / w);

  float ct = float(w / 2);

  vec2 texCoord = vec2(s * w + ct, t * w + ct);
  
  vec4 outColor = texture2D(tex, texCoord);
  outColor = outColor * gl_Color;

  gl_FragColor = outColor;
}
