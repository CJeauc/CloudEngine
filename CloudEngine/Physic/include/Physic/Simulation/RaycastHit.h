#pragma once

namespace Physic
{
	class ACollider;

	struct RaycastHit
	{
		std::vector<Physic::RigidBody*> rigidBodies;
		std::vector<float> hitDistances;

		RaycastHit() = default;
		~RaycastHit() = default;

		void Reserve(size_t p_size)
		{
			rigidBodies.reserve(p_size);
			hitDistances.reserve(p_size);
		}

		void Clear()
		{
			rigidBodies.clear();
			hitDistances.clear();
		}
	};
}