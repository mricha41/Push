#version 330

in vec4 fragColor;
in vec2 texture;
in vec3 normal;

out vec4 color;

struct directionalLight
{
	vec4 d_color;
	float d_ambientIntensity;
	vec3 d_direction;
	float d_diffuseIntensity;
};

uniform sampler2D currentTexture;
uniform directionalLight dirLight;

void main()
{
	vec4 ambientColor = vec4(dirLight.d_color) * dirLight.d_ambientIntensity;
	//color = vec4(fragColor);
	vec4 texColor = texture2D(currentTexture, texture);
	//vec4 finalColor = vec4(mix(texColor.rgb, texColor.rgb, texColor.a), 1.0);
	//color = finalColor * ambientColor;
	//color = color * texColor;
	
	float diffuseFactor = max(dot(normalize(normal), normalize(dirLight.d_direction)), 0.0f);
	
	vec4 diffuseColor = vec4(dirLight.d_color) * dirLight.d_diffuseIntensity * diffuseFactor;
	
	color = fragColor * texColor * (ambientColor + diffuseColor);
}