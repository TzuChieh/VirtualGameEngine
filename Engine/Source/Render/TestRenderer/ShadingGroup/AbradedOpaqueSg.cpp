#include "AbradedOpaqueSg.h"

using namespace xe;

bool AbradedOpaqueSg::init(const ShaderProgram& shaderProgram)
{
	// TODO: check shaderProgram validity

	m_shaderProgram = shaderProgram;

	return true;
}
