uniform sampler2D tex;
uniform float alpha;


void main()
{
// Normalised texture coords
  vec4 outColor = texture2D(tex, gl_TexCoord[0].st);

outColor.r = outColor.r + alpha;
outColor.g = outColor.g + alpha;
outColor.b = outColor.b + alpha;


    gl_FragColor = outColor;
}
