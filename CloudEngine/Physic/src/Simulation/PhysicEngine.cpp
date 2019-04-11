#include "Physic/stdafx.h"
#include "Physic/Simulation/PhysicEngine.h"

PhysicEngine::PhysicEngine() {}

PhysicEngine::~PhysicEngine() {}

void PhysicEngine::Update(double p_deltaTime)
{
	m_world.Update(p_deltaTime);
}

bool PhysicEngine::RayCast(CloudMath::Vector3f p_origin, CloudMath::Vector3f p_direction, float p_maxDistance) const
{
	return m_world.RayCast(p_origin, p_direction, p_maxDistance);
}

bool PhysicEngine::RayCast(CloudMath::Vector3f p_origin, CloudMath::Vector3f p_direction,
                           float p_maxDistance, Physic::RaycastHit& p_hits) const
{
	return m_world.RayCast(p_origin, p_direction, p_maxDistance, p_hits);
}
