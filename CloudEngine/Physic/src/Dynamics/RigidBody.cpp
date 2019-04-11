#include "Physic/stdafx.h"
#include "Physic/Dynamics/RigidBody.h"
#include "CloudMath.h"
#include "Physic/Math/Conversion.h"
#include "Physic/Simulation/World.h"

Tools::Event<Physic::RigidBody&> Physic::RigidBody::creationEvent;
Tools::Event<Physic::RigidBody&> Physic::RigidBody::destructionEvent;

Physic::RigidBody::RigidBody(ACollider* p_collider, CloudMath::Matrix4f p_transform, float p_mass, float p_friction)
	: m_collider(p_collider), m_constraint{nullptr},
	  m_linearConstraint{1, 1, 1}, m_angularConstraint{1, 1, 1}, m_collisionDetection(CollisionDetection::DISCRETE),
	  m_mass(p_mass), m_friction(p_friction),
	  m_onResizedShapeEvent(0), m_isTrigger(false), m_isKinematic(false)
{
	m_onResizedShapeEvent = m_collider->resizedShape += BIND(&Physic::RigidBody::CreateRigidBody, this);
	btTransform t;
	t.setFromOpenGLMatrix(p_transform.elements);
	m_motion = new btDefaultMotionState(t);
	CreateRigidBody();
}

Physic::RigidBody::~RigidBody()
{
	delete m_motion;
	m_collider->resizedShape -= m_onResizedShapeEvent;

	DestroyRigidBody();
	delete m_constraint;
}

bool Physic::RigidBody::operator==(const RigidBody& p_other) const
{
	return m_mass == p_other.m_mass &&
		m_rigidBody == p_other.m_rigidBody &&
		m_motion == p_other.m_motion &&
		m_collider == p_other.m_collider;
}

btRigidBody* Physic::RigidBody::GetRigidBody() const
{
	return m_rigidBody;
}

CloudMath::Matrix4f Physic::RigidBody::GetTransform() const
{
	CloudMath::Matrix4f mat;
	m_rigidBody->getWorldTransform().getOpenGLMatrix(mat.elements);
	return mat;
}

CloudMath::Vector3f Physic::RigidBody::GetPosition() const
{
	return ToVec3(m_rigidBody->getWorldTransform().getOrigin());
}

CloudMath::Quaternion Physic::RigidBody::GetRotation() const
{
	return ToQuat(m_rigidBody->getWorldTransform().getRotation());
}

void Physic::RigidBody::SetPosition(const CloudMath::Vector3f& p_vector3)
{
	m_rigidBody->getWorldTransform().setOrigin(ToBtVec(p_vector3));
}

void Physic::RigidBody::SetRotation(const CloudMath::Quaternion& p_quaternion)
{
	m_rigidBody->getWorldTransform().setRotation(ToBtQuat(p_quaternion));
}

void Physic::RigidBody::SetTransform(const CloudMath::Matrix4f& p_transform)
{
	m_rigidBody->getWorldTransform().setFromOpenGLMatrix(p_transform.elements);
}

Physic::ACollider* Physic::RigidBody::GetCollider() const
{
	return m_collider;
}

void Physic::RigidBody::SetCollider(ACollider* p_collider)
{
	m_collider = p_collider;

	CreateRigidBody();
}

void Physic::RigidBody::SetMass(float p_mass)
{
	m_mass = p_mass;

	CreateRigidBody();
}

void Physic::RigidBody::SetFriction(float p_friction)
{
	m_friction = p_friction;

	m_rigidBody->setFriction(p_friction);
}

void Physic::RigidBody::SetCollisionDetection(CollisionDetection p_collisionDetection)
{
	m_collisionDetection = p_collisionDetection;

	SetCollisionDetection();
}

void Physic::RigidBody::Activate(bool p_activate)
{
	m_rigidBody->activate(p_activate);
	if (!p_activate)
		m_rigidBody->setCollisionFlags(m_rigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
}

void Physic::RigidBody::AddForce(const CloudMath::Vector3f& p_vector3)
{
	m_rigidBody->applyCentralImpulse(ToBtVec(p_vector3));
}

CloudMath::Vector3f Physic::RigidBody::GetLinearVelocity() const
{
	return ToVec3(m_rigidBody->getLinearVelocity());
}

void Physic::RigidBody::SetLinearVelocity(const CloudMath::Vector3f& p_vector3) const
{
	m_rigidBody->setLinearVelocity(ToBtVec(p_vector3));
}

CloudMath::Vector3f Physic::RigidBody::GetAngularVelocity() const
{
	return ToVec3(m_rigidBody->getAngularVelocity());
}

void Physic::RigidBody::SetAngularVelocity(const CloudMath::Vector3f& p_vector3) const
{
	m_rigidBody->setAngularVelocity(ToBtVec(p_vector3));
}

void Physic::RigidBody::SetConstraint(const CloudMath::Vector3f& p_linear, const CloudMath::Vector3f& p_angular)
{
	m_linearConstraint = p_linear;
	m_angularConstraint = p_angular;

	ApplyConstraint();
}

btTypedConstraint* Physic::RigidBody::GetConstraint() const
{
	return m_constraint;
}

CloudMath::Vector3f Physic::RigidBody::GetLinearConstraint() const
{
	return m_linearConstraint;
}

CloudMath::Vector3f Physic::RigidBody::GetAngularConstraint() const
{
	return m_angularConstraint;
}

void Physic::RigidBody::SetIsTrigger(bool p_isTrigger)
{
	m_isTrigger = p_isTrigger;
	if (p_isTrigger)
		AddFlag(btCollisionObject::CF_NO_CONTACT_RESPONSE);
	else
		RemoveFlag(btCollisionObject::CF_NO_CONTACT_RESPONSE);
}

bool Physic::RigidBody::IsTrigger() const
{
	return m_isTrigger;
}

void Physic::RigidBody::AddFlag(int p_flag)
{
	m_rigidBody->setCollisionFlags(m_rigidBody->getCollisionFlags() | p_flag);
}

void Physic::RigidBody::RemoveFlag(int p_flag)
{
	m_rigidBody->setCollisionFlags(m_rigidBody->getCollisionFlags() & ~ p_flag);
}

void Physic::RigidBody::SetKinematic(bool p_isKinematic)
{
	m_isKinematic = p_isKinematic;
	if (p_isKinematic)
		AddFlag(btCollisionObject::CF_KINEMATIC_OBJECT);
	else
		RemoveFlag(btCollisionObject::CF_KINEMATIC_OBJECT);
}

bool Physic::RigidBody::IsKinematic() const
{
	return m_isKinematic;
}

void Physic::RigidBody::ApplyConstraint()
{
	m_constraint->setLimit(0, m_linearConstraint.x, 0);
	m_constraint->setLimit(1, m_linearConstraint.y, 0);
	m_constraint->setLimit(2, m_linearConstraint.z, 0);

	m_constraint->setLimit(3, m_angularConstraint.x, 0);
	m_constraint->setLimit(4, m_angularConstraint.y, 0);
	m_constraint->setLimit(5, m_angularConstraint.z, 0);
}

void Physic::RigidBody::SetFlags()
{
	SetIsTrigger(m_isTrigger);
	SetKinematic(m_isKinematic);
}

void Physic::RigidBody::SetCollisionDetection()
{
	switch (m_collisionDetection)
	{
	case CollisionDetection::DISCRETE:
		//m_rigidBody->setCcdMotionThreshold(std::numeric_limits<float>::max());	//Don't do continuous collision detection if the motion (in one step) is less then m_ccdMotionThreshold.
		m_rigidBody->setCcdSweptSphereRadius(0.f);
		break;
	case CollisionDetection::CONTINUOUS:
		m_rigidBody->setCcdMotionThreshold(1e-7);								//Don't do continuous collision detection if the motion (in one step) is less then m_ccdMotionThreshold.
		m_rigidBody->setCcdSweptSphereRadius(1.f);
		break;
	default:
		break;
	}
}

void Physic::RigidBody::CreateRigidBody()
{
	btVector3 inertia(0.f, 0.f, 0.f);
	if (m_mass != 0.0f)
		m_collider->GetShape()->calculateLocalInertia(m_mass, inertia);

	btRigidBody::btRigidBodyConstructionInfo info(m_mass, m_motion, m_collider->GetShape(), inertia);
	info.m_friction = m_friction;

	CloudMath::Vector3f linearVelocity(0, 0, 0);
	CloudMath::Vector3f angularVelocity(0, 0, 0);

	if (m_rigidBody)
	{
		linearVelocity = GetLinearVelocity();
		angularVelocity = GetAngularVelocity();
		DestroyRigidBody();
	}

	m_rigidBody = new btRigidBody(info);
	m_rigidBody->setUserPointer(this);

	SetFlags();
	SetCollisionDetection();

	SetLinearVelocity(linearVelocity);
	SetAngularVelocity(angularVelocity);

	m_constraint = new btGeneric6DofConstraint(*m_rigidBody, btTransform::getIdentity(), false);
	ApplyConstraint();

	creationEvent.Invoke(*this);
}

void Physic::RigidBody::DestroyRigidBody()
{
	destructionEvent.Invoke(*this);
	delete m_rigidBody;
}
