#version 150

uniform sampler2DRect tex0;
uniform sampler2DRect texE;
uniform float f;
uniform float minColor;
uniform float maxColor;

in vec2 texCoordVarying;

out vec4 outputColor;

void main() {
	vec4 texel0 = texture(tex0, texCoordVarying);
	vec2 pos = vec2(texel0.r*255, f);
	vec4 texel1 = texture(texE, pos);
	if (texel1.r>=maxColor) {
		texel1.r = 1.0;
	} else if (texel1.r<=minColor) {
		texel1.r = 0.0;
	}
	outputColor = vec4(texel1.r, texel1.r, texel1.r, texel0.a);
}
