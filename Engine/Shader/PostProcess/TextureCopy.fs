#version 400

in vec2 p_texCoord;

layout (location = 0) out vec4 out_destinationColor;
//out vec4 out_destinationColor;

uniform sampler2D u_sourceTextureSampler;

void main()
{
	//out_destinationColor = vec4(p_texCoord, 0.0, 1.0);
	out_destinationColor = texture(u_sourceTextureSampler, p_texCoord);
}