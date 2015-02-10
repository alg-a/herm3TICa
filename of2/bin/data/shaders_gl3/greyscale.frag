#version 150

uniform sampler2DRect tex0;

in vec2 texCoordVarying;

out vec4 outputColor;

void main() {
	vec4 texel0 = texture(tex0, texCoordVarying);
	float grey = 0.2126 * texel0.r + 0.7152 * texel0.g + 0.0722 * texel0.b;
	outputColor = vec4(grey, grey, grey, texel0.a);
}
