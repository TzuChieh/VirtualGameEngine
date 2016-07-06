#pragma once

#include "GameProgram.h"

namespace xe {

class ShaderProgram;
class Mesh;

class TestGameProgram : public GameProgram {

	public:
		virtual ~TestGameProgram() override;

		virtual void update() override;

	private:
		ShaderProgram* m_shaderProgram;
		Mesh* m_mesh;

		virtual bool init() override;
};

}