#version 150

uniform sampler2DRect tex0;
uniform sampler2DRect tex1;
uniform float mixture;

in vec2 texCoordVarying;

out vec4 outputColor;

void main() {
	vec4 texel0 = texture(tex0, texCoordVarying);
	vec4 texel1 = texture(tex1, texCoordVarying);
	outputColor = vec4(texel0.r*mixture + texel1.r*(1-mixture), texel0.g*mixture + texel1.g*(1-mixture), texel0.b*mixture + texel1.b*(1-mixture), 1);
}
