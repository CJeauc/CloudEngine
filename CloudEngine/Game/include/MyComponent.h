#pragma once

#include <Core.h>

class MyComponent : public Core::Component<MyComponent>
{
public:
	MyComponent() {}
	MyComponent(MyComponent&&) = default;
	virtual ~MyComponent() {}

	void Display(double p_time)
	{
		SLOG(Log::Info(), "Je display " << p_time);
	}

protected:
	std::string m_name {};
};
