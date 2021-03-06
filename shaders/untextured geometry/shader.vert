#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

out vec4 fragColor;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0);
	fragColor = color;
}