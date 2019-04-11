#include "Core/stdafx.h"
#include "Core/Engine/Cloud.h"

Cloud::Cloud()
{
	m_physicEngine = new ::PhysicEngine;
}

Cloud::~Cloud()
{
	for (auto& it : m_familyTypeIds)
		delete it.second;

	delete m_physicEngine;
}

Cloud& Cloud::Get()
{
	static Cloud instance;
	return instance;
}

PhysicEngine* Cloud::PhysicEngine() const
{
	return m_physicEngine;
}
