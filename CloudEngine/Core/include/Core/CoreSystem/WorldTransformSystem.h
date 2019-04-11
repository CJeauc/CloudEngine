#pragma once

#include <Core/CoreAPI.h>
#include <Core/ECS/System/System.h>
#include "Core/Scene/SceneNode.h"

namespace Core
{
	namespace Systems
	{
		class CORE_API WorldTransformSystem : public System<WorldTransformSystem>
		{
		public:
			WorldTransformSystem();
			~WorldTransformSystem() = default;

			void Awake() override;
			void PostUpdate(double p_deltaTime) override;

		private:
			void UpdateTransformRecursive(Core::SceneNode* p_sceneNode) const;
		};
	}
}
