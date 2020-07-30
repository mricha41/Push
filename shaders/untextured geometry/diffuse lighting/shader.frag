#version 330

out vec4 color;
in vec4 fragColor;
in vec3 normal;

struct directionalLight
{
	vec4 d_color;
	float d_ambientIntensity;
	vec3 d_direction;
	float d_diffuseIntensity;
};

uniform directionalLight dirLight;

void main()
{	
	vec4 ambientColor = vec4(dirLight.d_color) * dirLight.d_ambientIntensity;
	
	float diffuseFactor = max(dot(normalize(normal), normalize(dirLight.d_direction)), 0.0f);
	
	vec4 diffuseColor = vec4(dirLight.d_color) * dirLight.d_diffuseIntensity * diffuseFactor;
	
	color = vec4(fragColor) * (ambientColor + diffuseColor);
}