#version 330

in vec4 fragColor;
in vec2 texture;

out vec4 color;

struct directionalLight
{
	vec4 d_color;
	float d_ambientIntensity;
};

uniform sampler2D currentTexture;
uniform directionalLight dirLight;

void main()
{
	vec4 ambientColor = vec4(dirLight.d_color) * dirLight.d_ambientIntensity;
	//color = vec4(fragColor);
	color = texture2D(currentTexture, texture) * ambientColor;
	//vec4 finalColor = vec4(mix(texColor.rgb, texColor.rgb, texColor.a), 1.0);
	//color = finalColor * ambientColor;
	//color = color * texColor;
}