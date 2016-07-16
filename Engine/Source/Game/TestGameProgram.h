#pragma once

#include "GameProgram.h"

#include <vector>

namespace xe
{

// TEMP
class ShaderProgram;
class Mesh;

class Component;

class TestGameProgram : public GameProgram
{
public:
	virtual ~TestGameProgram() override;
	
private:
	// TEMP
	ShaderProgram* m_shaderProgram;
	Mesh* m_mesh;

	virtual bool init(Engine* engine) override;
	virtual void update() override;
};

}