#pragma once

#include <Core.h>
#include "MyComponent.h"

class FpsDisplayer : public Core::System<FpsDisplayer>
{
public:
	FpsDisplayer()
		: System<FpsDisplayer>(Core::SystemPriority::NORMAL_SYSTEM_PRIORITY, 1)
	{
	}

	void Update(double p_deltaTime) override
	{
		//if (Core::Input::GetKeyDown(Core::Key::KEY_M))
		//	cubeWithGravity->GetComponent<Core::Components::Transform>()->SetScale({ 10.f, 10.f, 10.f });

		//if (Core::Input::GetKeyUp(Core::Key::KEY_M))
		//	cubeWithGravity->GetComponent<Core::Components::Transform>()->SetScale({ 1.f, 1.f, 1.f });

		//if (Core::Input::GetKeyDown(Core::Key::KEY_B))
		//	rb->GetTransform()->SetPosition({ 0, 5, 0 });

		//if (Core::Input::GetKeyDown(Core::Key::KEY_PAGE_UP))
		//	oui->SetMass(1);

		//if (Core::Input::GetKeyDown(Core::Key::KEY_PAGE_DOWN))
		//	oui->SetMass(0);

		//if (Core::Input::GetKeyDown(Core::Key::KEY_C) && rb->IsGrounded())
		//	rb->AddForce({ 0.f, 5.f, 0.f });

		//if (Core::Input::GetKey(Core::Key::KEY_RIGHT))
		//	rb->SetLinearVelocity({
		//	(rb->GetLinearVelocity().x + 0.2f) <= 5.f ? (rb->GetLinearVelocity().x + 0.2f) : 5.f,
		//	rb->GetLinearVelocity().y,
		//	rb->GetLinearVelocity().z
		//		});

		//if (Core::Input::GetKey(Core::Key::KEY_LEFT))
		//	rb->SetLinearVelocity({
		//	(rb->GetLinearVelocity().x - 0.2f) >= -5.f ? (rb->GetLinearVelocity().x - 0.2f) : -5.f,
		//	rb->GetLinearVelocity().y,
		//	rb->GetLinearVelocity().z
		//		});

		//if (Core::Input::GetKey(Core::Key::KEY_DOWN))
		//	rb->SetLinearVelocity({
		//	rb->GetLinearVelocity().x,
		//	rb->GetLinearVelocity().y,
		//	(rb->GetLinearVelocity().z + 0.2f) <= 5.f ? (rb->GetLinearVelocity().z + 0.2f) : 5.f
		//		});

		//if (Core::Input::GetKey(Core::Key::KEY_UP))
		//	rb->SetLinearVelocity({
		//	rb->GetLinearVelocity().x,
		//	rb->GetLinearVelocity().y,
		//	(rb->GetLinearVelocity().z - 0.2f) >= -5.f ? (rb->GetLinearVelocity().z - 0.2f) : -5.f
		//		});

		//if (Core::Input::GetKeyUp(Core::Key::KEY_RIGHT))
		//	rb->SetLinearVelocity({ 0.2f, rb->GetLinearVelocity().y, rb->GetLinearVelocity().z });
		//if (Core::Input::GetKeyUp(Core::Key::KEY_LEFT))
		//	rb->SetLinearVelocity({ -0.2f, rb->GetLinearVelocity().y, rb->GetLinearVelocity().z });
		//if (Core::Input::GetKeyUp(Core::Key::KEY_DOWN))
		//	rb->SetLinearVelocity({ rb->GetLinearVelocity().x, rb->GetLinearVelocity().y, 0.2f });
		//if (Core::Input::GetKeyUp(Core::Key::KEY_UP))
		//	rb->SetLinearVelocity({ rb->GetLinearVelocity().x, rb->GetLinearVelocity().y, -0.2f });
	}

	void PostUpdate(double p_deltaTime) override
	{
		SLOG(Log::Info(), "FPS : " << 1 / p_deltaTime);
	}
};
