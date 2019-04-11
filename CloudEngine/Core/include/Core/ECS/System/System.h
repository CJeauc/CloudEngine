#pragma once

#include "ASystem.h"
#include "Core/Managers/TypeFunctions.h"
#include "Core/Engine/Cloud.h"

namespace Core::Systems
{
	class FPCameraSystem;
	class FirstPersonControllerSystem;
}

namespace Core
{
	template <typename T>
	class System : public ASystem
	{
		friend class SystemManager;

	protected:
		explicit System(SystemPriority p_priority = SystemPriority::NORMAL_SYSTEM_PRIORITY,
		                double p_updateInterval_s = -1.0) : ASystem(p_priority, p_updateInterval_s),
		                                                     m_systemManager{nullptr} {}

	public:
		virtual ~System() = default;

		inline SystemTypeId GetSystemTypeId() const override { return StaticSystemTypeId; }

		template <class... Dependencies>
		void AddDependencies(Dependencies&&... p_dependencies)
		{
			this->m_systemManager->AddSystemDependency(this, std::forward<Dependencies>(p_dependencies)...);
		}

		virtual void Awake() override {}
		virtual void FixedUpdate(double p_fixedDeltaTime) override {}
		virtual void PreUpdate(double p_deltaTime) override {}
		virtual void Update(double p_deltaTime) override {}
		virtual void PostUpdate(double p_deltaTime) override {}

	public:
		static const SystemTypeId StaticSystemTypeId;

	private:
		SystemManager* m_systemManager;
	};

	template <>
	const SystemTypeId System<Core::Systems::FPCameraSystem>::StaticSystemTypeId = *Cloud::Get().FamilyType<ASystem>()->Get<Core::Systems::FPCameraSystem>("FPCameraSystem");

	template <>
	const SystemTypeId System<Core::Systems::FirstPersonControllerSystem>::StaticSystemTypeId = *Cloud::Get().FamilyType<ASystem>()->Get<Core::Systems::FirstPersonControllerSystem>("FirstPersonControllerSystem");

	// set unique type id for this System<T>
	template <typename T>
	const SystemTypeId System<T>::StaticSystemTypeId = *Cloud::Get().FamilyType<ASystem>()->Get<T>(GetNameFromType<T>());
}
