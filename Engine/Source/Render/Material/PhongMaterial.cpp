#include "PhongMaterial.h"
#include "Render/Material/MaterialDefinition/EmptyMaterialDefinition.h"

using namespace xe;

PhongMaterial::PhongMaterial() :
	m_exponent(0.0f)
{

}

PhongMaterial::~PhongMaterial()
{

}

const MaterialDefinition& PhongMaterial::getMaterialDefinition() const
{
	return EmptyMaterialDefinition();
}

void PhongMaterial::updateProgram(const ShaderProgram& shaderProgram)
{

}