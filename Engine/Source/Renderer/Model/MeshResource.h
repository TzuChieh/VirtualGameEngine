#pragma once

#include "Core/graphicsApi.h"

namespace xe
{

class MeshResource
{
public:
	MeshResource();

	void shareVertexBufferWith(MeshResource* meshResource) const;

private:
	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ibo;
};

}