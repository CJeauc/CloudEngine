#include "Physic/stdafx.h"
#include "Physic/Simulation/World.h"
#include "Physic/Math/Conversion.h"
#include "Physic/Dynamics/RigidBody.h"

using namespace Physic;

World::World(WorldConfig p_worldConfig)
	: m_worldConfig(std::move(p_worldConfig))
{
	m_collisionConfig = new btDefaultCollisionConfiguration();
	m_dispatcher = new btCollisionDispatcher(m_collisionConfig);
	m_broadphase = new btDbvtBroadphase();
	m_solver = new btSequentialImpulseConstraintSolver();
	m_world = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfig);
	m_world->setGravity(ToBtVec(m_worldConfig.gravity));

	Physic::RigidBody::creationEvent += BIND(&World::AddRigidBody, this, HOLDER_1);
	Physic::RigidBody::destructionEvent += BIND(&World::RemoveRigidBody, this, HOLDER_1);

	gContactAddedCallback = OnContactCallback;
}

World::~World()
{
	delete m_collisionConfig;
	delete m_dispatcher;
	delete m_broadphase;
	delete m_solver;
	delete m_world;
}

void World::Update(double p_deltaTime)
{
	m_world->stepSimulation(p_deltaTime);
}

void World::AddRigidBody(RigidBody& p_rigidBody)
{
	m_world->addRigidBody(p_rigidBody.GetRigidBody());
	m_rigidBodies.emplace_back(p_rigidBody);
	m_world->addConstraint(p_rigidBody.GetConstraint());
}

void World::RemoveRigidBody(RigidBody& p_rigidBody)
{
	m_world->removeCollisionObject(p_rigidBody.GetRigidBody());

	auto rigidBody = m_rigidBodies.begin();
	for (; rigidBody != m_rigidBodies.end(); ++rigidBody)
	{
		if (rigidBody->get() == p_rigidBody)
			break;
	}

	if (rigidBody != m_rigidBodies.end())
	{
		m_world->removeConstraint(rigidBody->get().GetConstraint());
		m_rigidBodies.erase(rigidBody);
	}
}

bool World::RayCast(CloudMath::Vector3f p_origin, CloudMath::Vector3f p_direction, float p_maxDistance) const
{
	p_direction = p_origin + p_direction.Normalize() * p_maxDistance;

	btCollisionWorld::AllHitsRayResultCallback rayCallback(ToBtVec(p_origin), ToBtVec(p_direction));
	m_world->rayTest(ToBtVec(p_origin), ToBtVec(p_direction), rayCallback);

	return rayCallback.hasHit();
}

bool World::RayCast(CloudMath::Vector3f p_origin, CloudMath::Vector3f p_direction,
                    float p_maxDistance, RaycastHit& p_hits) const
{
	p_hits.Clear();

	p_direction = p_origin + p_direction.Normalize() * p_maxDistance;

	btCollisionWorld::AllHitsRayResultCallback rayCallback(ToBtVec(p_origin), ToBtVec(p_direction));
	m_world->rayTest(ToBtVec(p_origin), ToBtVec(p_direction), rayCallback);

	if (rayCallback.hasHit())
	{
		p_hits.Reserve(rayCallback.m_collisionObjects.size());
		for (uint16_t i = 0; i < rayCallback.m_collisionObjects.size(); i++)
		{
			p_hits.rigidBodies.emplace_back(
				static_cast<Physic::RigidBody*>(rayCallback.m_collisionObjects[i]->getUserPointer()));
			p_hits.hitDistances.emplace_back(rayCallback.m_hitFractions[i] * (p_direction - p_origin).Length());
		}
	}

	return rayCallback.hasHit();
}

bool World::OnContactCallback(btManifoldPoint& cp,
                              const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0,
                              const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1)
{
	auto rigidBody1 = static_cast<Physic::RigidBody*>(colObj0Wrap->getCollisionObject()->getUserPointer());
	auto rigidBody2 = static_cast<Physic::RigidBody*>(colObj1Wrap->getCollisionObject()->getUserPointer());

	if (rigidBody1->IsTrigger())
		rigidBody1->onTrigger.Invoke(rigidBody2);
	else if (!rigidBody2->IsTrigger())
		rigidBody1->onCollision.Invoke(rigidBody2);

	if (rigidBody2->IsTrigger())
		rigidBody2->onTrigger.Invoke(rigidBody1);
	else if (!rigidBody1->IsTrigger())
		rigidBody2->onCollision.Invoke(rigidBody1);



	return false;
}
