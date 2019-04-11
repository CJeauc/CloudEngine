#include "Core/stdafx.h"
#include "Core/CoreSystem/WorldTransformSystem.h"
#include "Core/ECS/ECS.h"
#include "Core/CoreComponent/Transform.h"
#include "Core/Scene/SceneManager.h"
#include "Core/Scene/SceneNode.h"

using namespace Core::Systems;

WorldTransformSystem::WorldTransformSystem()
	: System(SystemPriority::HIGHEST_SYSTEM_PRIORITY) { }

void WorldTransformSystem::Awake()
{
	SceneManagement::SceneManager::GetActiveScene()->LinkTransformWithNodes();
}

void WorldTransformSystem::PostUpdate(double p_deltaTime)
{
	auto gameObjectNodeMap = SceneManagement::SceneManager::GetActiveScene()->GetGameObjectNodeMap();
	for (auto it : gameObjectNodeMap)
	{
		if (it.second->IsDirty())
			UpdateTransformRecursive(it.second);
	}
}

void WorldTransformSystem::UpdateTransformRecursive(Core::SceneNode* p_sceneNode) const
{
	// Core::SceneNode* parent = p_sceneNode->GetParent();
	// if (parent && parent->IsDirty())
	// 	UpdateTransformRecursive(parent);
	//
	// auto transform = p_sceneNode->GetGameObject()->GetComponent<Components::Transform>();
	// if (transform)
	// {
	// 	auto parentTransform = parent->GetGameObject() ? parent->GetGameObject()->GetComponent<Components::Transform>() : nullptr;
	// 	transform->SetParentTransform(parentTransform ? parentTransform->GetTransform() : CloudMath::Matrix4f::Identity);
	// }
	//
	// p_sceneNode->SetDirty(false);
}
