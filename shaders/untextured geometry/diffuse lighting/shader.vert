#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 textureCoords;
layout (location = 3) in vec3 normalCoords;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

out vec4 fragColor;
out vec3 normal;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0);
	fragColor = color;
	
	normal = mat3(transpose(inverse(model))) * normalCoords;
}