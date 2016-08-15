#include "Mesh.h"

#include "Common/ThirdPartyLib/glew.h"

#include <vector>

using namespace xe;

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
}

void Mesh::loadData(const std::vector<float32>& positions3d)
{
	m_numVertices = (GLsizei)positions3d.size() / 3;

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, positions3d.size() * sizeof(float32), positions3d.data(), GL_STATIC_DRAW);
	
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

void Mesh::draw() const
{
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, m_numVertices);
}