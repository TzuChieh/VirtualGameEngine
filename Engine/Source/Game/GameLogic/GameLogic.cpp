#include "GameLogic.h"

using namespace ve;

GameLogic::~GameLogic()
{

}

Entity GameLogic::getParentEntity() const
{
	return m_parentEntity;
}

void GameLogic::setParentEntity(const Entity& entity)
{
	m_parentEntity = entity;
}