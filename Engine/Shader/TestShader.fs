#version 400

in vec3 p_worldPos;
in vec3 p_normal;

layout (location = 0) out vec4 out_fragColor;

const vec3 lightPos = vec3(-100, 100, 0);

void main()
{
	vec3 L = normalize(lightPos - p_worldPos);
	vec3 N = p_normal;

	vec3 color = vec3(dot(L, N));
	out_fragColor = vec4(color, 1.0);
	//out_fragColor = vec4(1.0, 0.0, 0.0, 1.0);
}