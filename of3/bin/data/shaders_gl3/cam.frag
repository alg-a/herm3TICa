#version 150

uniform sampler2DRect tex0;
uniform sampler2DRect texE1;
uniform sampler2DRect texE2;
uniform sampler2DRect texE3;
uniform float f1;
uniform float f2;
uniform float f3;

in vec2 texCoordVarying;

out vec4 outputColor;

void main() {
	vec4 texel0 = texture(tex0, texCoordVarying);
	vec2 posR = vec2(texel0.r*255, f1);
	vec2 posG = vec2(texel0.g*255, f2);
	vec2 posB = vec2(texel0.b*255, f3);
	vec4 texelR = texture(texE1, posR);
	vec4 texelG = texture(texE2, posG);
	vec4 texelB = texture(texE3, posB);
	outputColor = vec4(texelR.r, texelG.g, texelB.b, texel0.a);
}
