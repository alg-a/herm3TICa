#version 150

uniform sampler2DRect tex0;
uniform sampler2DRect mask;

in vec2 texCoordVarying;

out vec4 outputColor;

void main() {
	vec4 texel0 = texture(tex0, texCoordVarying);
	vec4 texel1 = texture(mask, texCoordVarying);
	outputColor = vec4(texel0.r, texel0.g, texel0.b, texel1.r);
}
