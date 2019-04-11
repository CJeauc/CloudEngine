#include <Core/stdafx.h>
#include <Core/Scene/SceneManager.h>
#include <Core/ECS/ECS.h>

using namespace Core::SceneManagement;

std::shared_ptr<Core::Scene> SceneManager::m_activeScene = nullptr;
uint16_t SceneManager::m_activeSceneEventID;

std::shared_ptr<Core::Scene> SceneManager::AddScene(std::string p_sceneName)
{
	if (m_activeScene)
	{
		GameObject::CreationEvent -= m_activeSceneEventID;
		Core::ECS::Get().Clear();
	}

	m_activeScene = std::make_shared<Core::Scene>(p_sceneName);
	m_activeSceneEventID = GameObject::CreationEvent += BIND(&Scene::AddNode, m_activeScene.get(), HOLDER_1);
	return m_activeScene;
}

void SceneManager::SetActiveScene(std::shared_ptr<Core::Scene> p_newScene)
{
	if (p_newScene)
	{
		GameObject::CreationEvent -= m_activeSceneEventID;
		m_activeScene = p_newScene;
		Core::ECS::Get().Clear();
		m_activeSceneEventID = GameObject::CreationEvent += BIND(&Scene::AddNode, m_activeScene.get(), HOLDER_1);
	}
}

std::shared_ptr<Core::Scene> Core::SceneManagement::SceneManager::GetActiveScene()
{
	return m_activeScene;
}

std::shared_ptr<Core::Scene> SceneManager::LoadScene(std::string p_sceneName)
{
	SetActiveScene(std::make_shared<Core::Scene>(p_sceneName));
	m_activeScene->Load(p_sceneName);

	return m_activeScene;
}
