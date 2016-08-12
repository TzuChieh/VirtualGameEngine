#version 400

layout (location = 0) in vec3 position;

out vec3 p_worldPos;

uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;

void main()
{
	p_worldPos = position;
	gl_Position = u_projectionMatrix * u_viewMatrix * vec4(position, 1.0);
}