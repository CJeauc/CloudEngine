#pragma once

#include <Core.h>

class MyEntity : public Core::Entity<MyEntity>
{
public:
	MyEntity() = default;
	~MyEntity() = default;

private:
	int m_data;
};