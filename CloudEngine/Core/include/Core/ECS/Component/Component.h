#pragma once

#include "AComponent.h"
#include "Core/Managers/TypeFunctions.h"
#include "Core/Engine/Cloud.h"

namespace Core::Components
{
	class Transform;
	class MaterialRenderer;
	class MeshRenderer;
	class BoxCollider;
	class SphereCollider;
	class CapsuleCollider;
	class RigidBody;
	class UniformRendering;
	class LightComponent;
	class CameraComponent;
	class FirstPersonController;
}

namespace Core
{
	template <typename T>
	class Component : public AComponent
	{
	public:
		Component() = default;
		virtual ~Component() = default;

		ComponentTypeId GetComponentTypeId() const override { return StaticComponentTypeId; }
		virtual void Serialize(TinyXML2::XMLDocument& p_doc, TinyXML2::XMLNode* p_parent) const override {}
		virtual void DeSerialize(TinyXML2::XMLElement* p_componentNode) override {}

	public:
		static const ComponentTypeId StaticComponentTypeId;
	};

	template <>
	const ComponentTypeId Component<Core::Components::Transform>::StaticComponentTypeId = *Cloud::Get().FamilyType<AComponent>()->Get<Core::Components::Transform>("Transform");

	template <>
	const ComponentTypeId Component<Core::Components::MaterialRenderer>::StaticComponentTypeId = *Cloud::Get().FamilyType<AComponent>()->Get<Core::Components::MaterialRenderer>("MaterialRenderer");

	template <>
	const ComponentTypeId Component<Core::Components::MeshRenderer>::StaticComponentTypeId = *Cloud::Get().FamilyType<AComponent>()->Get<Core::Components::MeshRenderer>("MeshRenderer");

	template <>
	const ComponentTypeId Component<Core::Components::BoxCollider>::StaticComponentTypeId = *Cloud::Get().FamilyType<AComponent>()->Get<Core::Components::BoxCollider>("BoxCollider");

	template <>
	const ComponentTypeId Component<Core::Components::SphereCollider>::StaticComponentTypeId = *Cloud::Get().FamilyType<AComponent>()->Get<Core::Components::SphereCollider>("SphereCollider");

	template <>
	const ComponentTypeId Component<Core::Components::CapsuleCollider>::StaticComponentTypeId = *Cloud::Get().FamilyType<AComponent>()->Get<Core::Components::CapsuleCollider>("CapsuleCollider");

	template <>
	const ComponentTypeId Component<Core::Components::RigidBody>::StaticComponentTypeId = *Cloud::Get().FamilyType<AComponent>()->Get<Core::Components::RigidBody>("RigidBody");

	template <>
	const ComponentTypeId Component<Core::Components::UniformRendering>::StaticComponentTypeId = *Cloud::Get().FamilyType<AComponent>()->Get<Core::Components::UniformRendering>("UniformRendering");

	template <>
	const ComponentTypeId Component<Core::Components::LightComponent>::StaticComponentTypeId = *Cloud::Get().FamilyType<AComponent>()->Get<Core::Components::LightComponent>("LightComponent");
	
	template <>
	const ComponentTypeId Component<Core::Components::CameraComponent>::StaticComponentTypeId = *Cloud::Get().FamilyType<AComponent>()->Get<Core::Components::CameraComponent>("CameraComponent");

	template <>
	const ComponentTypeId Component<Core::Components::FirstPersonController>::StaticComponentTypeId = *Cloud::Get().FamilyType<AComponent>()->Get<Core::Components::FirstPersonController>("FirstPersonController");

	// Set unique type id for this Component<T>
	template <class T>
	const ComponentTypeId Component<T>::StaticComponentTypeId = *Cloud::Get().FamilyType<AComponent>()->Get<T>(GetNameFromType<T>());
}
