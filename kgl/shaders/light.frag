// Control inputs

uniform float alpha;
// Texture input
uniform sampler2D Texture;

void main()
{
// Normalised texture coords
vec2 texCoord = gl_TexCoord[0].xy;
vec4 color  = texture2D( Texture, texCoord);

color.r = color.r + alpha;
color.g = color.g + alpha;
color.b = color.b + alpha;


    gl_FragColor = color;
}
