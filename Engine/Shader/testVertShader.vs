#version 400

layout (location = 0) in vec3 position;

uniform mat4 u_viewProjectionMatrix;

void main()
{
	gl_Position = u_viewProjectionMatrix * vec4(position, 1.0);
}