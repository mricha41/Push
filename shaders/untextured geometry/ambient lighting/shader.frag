#version 330

out vec4 color;
in vec4 fragColor;

struct directionalLight
{
	vec4 d_color;
	float d_ambientIntensity;
};

uniform directionalLight dirLight;

void main()
{
	vec4 ambientColor = vec4(dirLight.d_color) * dirLight.d_ambientIntensity;
	color = vec4(fragColor) * ambientColor;
}