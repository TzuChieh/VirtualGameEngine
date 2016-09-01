#version 400

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out vec3 p_worldPos;
out vec3 p_normal;

uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;
uniform mat4 u_modelMatrix;

void main()
{
	p_worldPos = position;
	p_normal = normal;
	
	gl_Position = u_projectionMatrix * u_viewMatrix * u_modelMatrix * vec4(position, 1.0);
}