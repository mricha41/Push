#version 330

in vec4 fragmentColor;
in vec3 normal;
in vec3 fragmentPosition;

out vec4 color;

struct directionalLight
{
	vec4 d_color;
	float d_ambientIntensity;
	vec3 d_direction;
	float d_diffuseIntensity;
};

struct Material
{
	float d_specularIntensity;
	float d_shininess;
};

uniform directionalLight dirLight;
uniform Material material;

uniform vec3 eyePosition;

void main()
{
	vec4 ambientColor = vec4(dirLight.d_color) * dirLight.d_ambientIntensity;
	
	float diffuseFactor = max(dot(normalize(normal), normalize(dirLight.d_direction)), 0.0f);
	
	vec4 diffuseColor = vec4(dirLight.d_color) * dirLight.d_diffuseIntensity * diffuseFactor;
	
	vec4 specularColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);
	if(diffuseFactor > 0.0f)
	{
		vec3 fragmentToEyePosition = normalize(eyePosition - fragmentPosition);
		vec3 reflectedVertex = normalize(reflect(dirLight.d_direction, normalize(normal)));
		
		float specularFactor = dot(fragmentToEyePosition, reflectedVertex);
		if(specularFactor > 0.0f)
		{
			specularFactor = pow(specularFactor, material.d_shininess);
			specularColor = vec4(dirLight.d_color * material.d_specularIntensity * specularFactor);
		}
	}
	
	color = fragmentColor * (ambientColor + diffuseColor + specularColor);
}