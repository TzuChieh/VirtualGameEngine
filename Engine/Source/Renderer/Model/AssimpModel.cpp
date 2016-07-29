#include "AssimpModel.h"

using namespace xe;

AssimpModel::AssimpModel(const std::string& fullFilename)
	: m_fullFilename(fullFilename)
{

}

AssimpModel::~AssimpModel()
{

}

bool AssimpModel::load()
{
	return true;
}