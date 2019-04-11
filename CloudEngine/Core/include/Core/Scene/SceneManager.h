#pragma once

#include <Core/stdafx.h>
#include <Core/CoreAPI.h>
#include <Core/Scene/Scene.h>

namespace Core
{
	namespace SceneManagement
	{
		class CORE_API SceneManager
		{
		public:
			static std::shared_ptr<Core::Scene> AddScene(std::string p_sceneName);
			static std::shared_ptr<Core::Scene> GetActiveScene();

			static std::shared_ptr<Core::Scene> LoadScene(std::string p_sceneName);

		private:
			static void SetActiveScene(std::shared_ptr<Core::Scene> p_newScene);

		private:
			static std::shared_ptr<Core::Scene> m_activeScene;
			static uint16_t m_activeSceneEventID;
		};
	}
}