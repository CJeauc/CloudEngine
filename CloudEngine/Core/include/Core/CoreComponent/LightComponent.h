#pragma once

#include <Core/CoreAPI.h>
#include <Core/ECS/Component/Component.h>
#include <Rendering/Light/Light.h>
#include <CloudMath.h>

/*
The Light Component hold a referemce to a rendering Light
The component it self only has data such as position and color

This component Only has the basic functionality for our first prototype to work
Later on, this component will have all Light data such as intensity, an enum for different light types ...

This component is manager by the Rendering System
*/

namespace Core
{
	namespace Components
	{
		class CORE_API LightComponent : public Component<LightComponent>
		{
		public:
			LightComponent();
			~LightComponent();

			void SetPosition(const CloudMath::Vector3f& p_position);
			void SetColor(const CloudMath::Vector3f& p_color);

			std::shared_ptr<Rendering::Light> GetLight();

		protected:
			void Init() override;

		private:
			std::shared_ptr<Rendering::Light> m_light;
		};
	}
}