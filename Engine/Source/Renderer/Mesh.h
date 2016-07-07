#pragma once

#include "Common/type.h"

#include "Core/graphicsApi.h"

#include <vector>

namespace xe {

class Mesh {
	public:
		~Mesh();

		void loadData(const std::vector<float32>& positions3d);
		void draw() const;

	private:
		GLuint m_vao;
		GLuint m_vbo;

		GLsizei m_numVertices;
};

}