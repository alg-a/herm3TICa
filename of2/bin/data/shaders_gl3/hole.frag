#version 150

uniform sampler2DRect tex0;
uniform sampler2DRect texE1;
uniform sampler2DRect texE2;
uniform sampler2DRect mask;

uniform float f1;
uniform float f2;

in vec2 texCoordVarying;

out vec4 outputColor;

void main() {
	
	vec4 texel0 = texture(tex0, texCoordVarying);
	float greyBase = 0.2126 * texel0.r + 0.7152 * texel0.g + 0.0722 * texel0.b;
	
	vec4 texelMask = texture(mask, texCoordVarying);
	
	vec2 pos1 = vec2(greyBase*255, f1);
	vec2 pos2 = vec2(greyBase*255, f2);
		
	vec4 texel1 = texture(texE1, pos1);
	vec4 texel2 = texture(texE2, pos2);
	
	float color = texel1.r * texelMask.r + texel2.r * (1-texelMask.r);
	outputColor = vec4(color, color, color, texel0.a);
	
}
