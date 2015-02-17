#version 150

uniform sampler2DRect tex0;
uniform float contrast;

in vec2 texCoordVarying;

out vec4 outputColor;

void main() {
	 
	vec4 texel0 = texture(tex0, texCoordVarying);
	float alpha = 1.0;
	if ((floor(mod(texCoordVarying.x, 3)) == 1) && (floor(mod(texCoordVarying.y, 3)) == 1)) {
		alpha = 1.0;
	} else {
		alpha = 0.0;
	}
	if ((texel0.r == 0) && (texel0.g == 0) && (texel0.b == 0)) {
		alpha = 0.0;
	}
	outputColor = vec4(texel0.r, texel0.g, texel0.b, alpha);
	
}
