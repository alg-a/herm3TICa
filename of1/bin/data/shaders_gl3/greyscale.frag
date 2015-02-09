#version 150

uniform sampler2DRect tex0;
uniform sampler2DRect texE;
uniform float f;
uniform int adjust;

in vec2 texCoordVarying;

out vec4 outputColor;

void main() {
	   
	vec4 texel0 = texture(tex0, texCoordVarying);
	float grey = 0.2126 * texel0.r + 0.7152 * texel0.g + 0.0722 * texel0.b;
	if (adjust==1) {
		vec2 pos = vec2(grey*255, f);
		vec4 texel1 = texture(texE, pos);
		outputColor = vec4(texel1.r, texel1.g, texel1.b, texel0.a);
	} else {
		outputColor = vec4(grey, grey, grey, texel0.a);
	}
	
}
