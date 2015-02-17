#version 150

uniform sampler2DRect tex0;
uniform float alpha;
uniform int doAlpha;

in vec2 texCoordVarying;

out vec4 outputColor;

void main() {
	 
	vec4 texel0 = texture(tex0, texCoordVarying);
	float a = alpha;
	if (doAlpha==1) {
		if ((floor(mod(texCoordVarying.x, 3)) == 1) && (floor(mod(texCoordVarying.y, 3)) == 1)) {
			a = alpha;
		} else {
			a = 0.0;
		}
		if ((texel0.r == 0) && (texel0.g == 0) && (texel0.b == 0)) {
			a = 0.0;
		}
	}
	outputColor = vec4(texel0.r, texel0.g, texel0.b, a);
	
}
