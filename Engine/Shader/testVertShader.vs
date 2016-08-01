#version 400

layout (location = 0) in vec3 position;

uniform mat4 u_projectionMatrix;

void main(void)
{
	gl_Position = u_projectionMatrix * vec4(position, 1.0);
}