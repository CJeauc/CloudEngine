#pragma once

#include "Physic/PhysicAPI.h"
#include <bullet/btBulletDynamicsCommon.h>
#include "Physic/Dynamics/RigidBody.h"
#include "Physic/Config/WorldConfig.h"
#include "Physic/Simulation/RaycastHit.h"

namespace Physic
{
	class PHYSIC_API World
	{
	public:
		explicit World(WorldConfig p_worldConfig = {EARTH_GRAVITY});
		~World();

		void Update(double p_deltaTime);

		void AddRigidBody(RigidBody& p_rigidBody);
		void RemoveRigidBody(RigidBody& p_rigidBody);

		bool RayCast(CloudMath::Vector3f p_origin, CloudMath::Vector3f p_direction, float p_maxDistance) const;
		bool RayCast(CloudMath::Vector3f p_origin, CloudMath::Vector3f p_direction, float p_maxDistance,
		             RaycastHit& p_hits) const;

	private:
		static bool OnContactCallback(btManifoldPoint& cp,
		                              const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0,
		                              const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1);

	private:
		WorldConfig m_worldConfig;

		btCollisionConfiguration* m_collisionConfig;
		btDispatcher* m_dispatcher;
		btBroadphaseInterface* m_broadphase;
		btConstraintSolver* m_solver;
		btDynamicsWorld* m_world;

		std::vector<std::reference_wrapper<RigidBody>> m_rigidBodies;
	};
}
