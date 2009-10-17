uniform sampler2D src_tex_unit0;
uniform vec2 src_tex_offset0;

void main(void)
{
	float dx = src_tex_offset0.s;
	float dy = src_tex_offset0.t;
	vec2 st = gl_TexCoord[0].st;

	// Getting colors of the center and surrounding texels.
	vec4 color	 = 4.0 * texture2D(src_tex_unit0, st);
	color		+= 2.0 * texture2D(src_tex_unit0, st + vec2(+dx, 0.0));
	color		+= 2.0 * texture2D(src_tex_unit0, st + vec2(-dx, 0.0));
	color		+= 2.0 * texture2D(src_tex_unit0, st + vec2(0.0, +dy));
	color		+= 2.0 * texture2D(src_tex_unit0, st + vec2(0.0, -dy));
	color		+= texture2D(src_tex_unit0, st + vec2(+dx, +dy));
	color		+= texture2D(src_tex_unit0, st + vec2(-dx, +dy));
	color		+= texture2D(src_tex_unit0, st + vec2(-dx, -dy));
	color		+= texture2D(src_tex_unit0, st + vec2(+dx, -dy));
	
        // Output color is the average.
	gl_FragColor = color / 16.0;
}