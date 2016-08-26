#include "AbradedOpaqueSg.h"

using namespace ve;

bool AbradedOpaqueSg::init(const ShaderProgram& shaderProgram)
{
	// TODO: check shaderProgram validity

	m_shaderProgram = shaderProgram;

	return true;
}
