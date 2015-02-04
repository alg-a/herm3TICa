#version 150

uniform sampler2DRect tex0;
uniform sampler2DRect texBKG;

in vec2 texCoordVarying;

out vec4 outputColor;

void main() {
	vec4 texel0 = texture(tex0, texCoordVarying);
	vec4 texelBkg = texture(texBKG, texCoordVarying);
	float color = abs(texel0.r - texelBkg.r);
	outputColor = vec4(color, color, color, texel0.a);
}
