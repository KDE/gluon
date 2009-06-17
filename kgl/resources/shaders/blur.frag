uniform sampler2D tex1;
uniform float blurfactor;

void main()
{   
	vec4 baseColor = vec4(0.0, 0.0, 0.0, 0.0);
	
        float ddy = blurfactor;
        float ddx = blurfactor;
 
  // Horizontal blur
  baseColor += 0.015625 * texture2D(tex1, gl_TexCoord[0].xy + vec2(0.0, ddy*-3.0) );
  baseColor += 0.09375 * texture2D(tex1, gl_TexCoord[0].xy + vec2(0.0, ddy*-2.0) );
  baseColor += 0.234375 * texture2D(tex1, gl_TexCoord[0].xy + vec2(0.0, ddy*-1.0) );
  baseColor += 0.3125 * texture2D(tex1, gl_TexCoord[0].xy + vec2(0.0, 0.0) );
  baseColor += 0.234375 * texture2D(tex1, gl_TexCoord[0].xy + vec2(0.0, ddy*1.0) );
  baseColor += 0.09375 * texture2D(tex1, gl_TexCoord[0].xy + vec2(0.0, ddy*2.0) );
  baseColor += 0.015625 * texture2D(tex1, gl_TexCoord[0].xy + vec2(0.0, ddy*3.0) );
  
  // Vertical blur
  baseColor += 0.015625 * texture2D(tex1, gl_TexCoord[0].xy + vec2(ddx*-3.0, 0.0) );
  baseColor += 0.09375 * texture2D(tex1, gl_TexCoord[0].xy + vec2(ddx*-2.0, 0.0) );
  baseColor += 0.234375 * texture2D(tex1, gl_TexCoord[0].xy + vec2(ddx*-1.0, 0.0) );
  baseColor += 0.3125 * texture2D(tex1, gl_TexCoord[0].xy + vec2(0.0, 0.0) );
  baseColor += 0.234375 * texture2D(tex1, gl_TexCoord[0].xy + vec2(ddx*1.0, 0.0) );
  baseColor += 0.09375 * texture2D(tex1, gl_TexCoord[0].xy + vec2(ddx*2.0, 0.0) );
  baseColor += 0.015625 * texture2D(tex1, gl_TexCoord[0].xy + vec2(ddx*3.0, 0.0) );
  
  // Mix both
  baseColor *= 0.5;
	
	gl_FragColor = baseColor;
}

