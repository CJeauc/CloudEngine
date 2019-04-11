#pragma once

#include "Physic/PhysicAPI.h"
#include "World.h"

namespace Core
{
	namespace Systems
	{
		class PhysicSystem;
	}
}

class PHYSIC_API PhysicEngine
{
	friend class Core::Systems::PhysicSystem;

public:
	PhysicEngine();
	~PhysicEngine();

	void Update(double p_deltaTime);

	bool RayCast(CloudMath::Vector3f p_origin, CloudMath::Vector3f p_direction, float p_maxDistance) const;
	bool RayCast(CloudMath::Vector3f p_origin, CloudMath::Vector3f p_direction, float p_maxDistance, Physic::RaycastHit& p_hits) const;

private:
	Physic::World m_world;
};
