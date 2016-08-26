#include "PhongMaterial.h"

using namespace ve;

PhongMaterial::PhongMaterial() :
	m_kd(0.5f), m_ks(0.5f), m_shininess(8)
{

}

PhongMaterial::~PhongMaterial()
{

}

bool PhongMaterial::populateMatlParamSet(PbrOpaqueParamSet* matlParamSet) const
{
	return false;
}