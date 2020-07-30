#version 330

out vec4 color;
in vec4 fragColor;
in vec2 texture;

uniform sampler2D currentTexture;

void main()
{
	color = vec4(fragColor);
	vec4 texColor = texture2D(currentTexture, texture);
	vec4 finalColor = vec4(mix(texColor.rgb, texColor.rgb, texColor.a), 1.0);
	//color = finalColor;
	color = color * texColor;
}