#version 150

uniform sampler2DRect tex0;

in vec2 texCoordVarying;

out vec4 outputColor;

void main() {
	vec4 texel0 = texture(tex0, texCoordVarying);
	outputColor = vec4(1 - texel0.r, 1 - texel0.g, 1 - texel0.b, texel0.a);
}
