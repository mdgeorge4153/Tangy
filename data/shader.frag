
uniform vec2  waves[32];
uniform int   nwaves    =     0;
uniform float radius    =  10.0;
uniform float frequency =   1.0;
uniform vec4  color1    = vec4(0.0, 0.0, 1.0, 1.0);
uniform vec4  color2    = vec4(0.2, 0.0, 0.5, 1.0);

float wave_height(vec2 wave_pos) {
	float d      = length(gl_TexCoord[0].st - wave_pos);
	float atten  = max(radius - d, 0.0) / radius;  // between 0 and 1

	return atten * (1.0 + cos(d/frequency)) / 2.0;
}

void main()
{
	float height=0.0;
	for (int i = 0; i < nwaves; i++)
		height = height + wave_height(waves[i]);
	gl_FragColor = mix(color1, color2, fract(height));
}


