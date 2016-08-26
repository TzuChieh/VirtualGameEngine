#include "PbrOpaqueParamSet.h"

using namespace ve;

static const float32 DEFAULT_ROUGHNESS = 0.5f;

PbrOpaqueParamSet::PbrOpaqueParamSet() :
	m_roughness(DEFAULT_ROUGHNESS)
{

}

PbrOpaqueParamSet::~PbrOpaqueParamSet()
{

}

void PbrOpaqueParamSet::reset()
{
	m_roughness = DEFAULT_ROUGHNESS;
}