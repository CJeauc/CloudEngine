#pragma once

#include <Core/CoreAPI.h>
#include <Core/ECS/Component/Component.h>
#include <Rendering/Shading/Material.h>

/*
The MaterialRenderer Component hold a referemce to a rendering Material
The component it self only has data such as the shader different values for the map samplers 

This component Only has the basic functionality for our first prototype to work
Later on, this component will have all Material data and functionalities to map between 
shader uniforms and samplers and other component or resources

This component is manager by the Material System
*/

namespace Core
{
	namespace Components
	{
		class CORE_API MaterialRenderer : public Component<MaterialRenderer>
		{
		public:
			MaterialRenderer();
			MaterialRenderer(std::shared_ptr<Rendering::Material> p_material);
			~MaterialRenderer();

			void SetMaterial(std::shared_ptr<Rendering::Material> p_material);
			Rendering::Material& Material();
			std::shared_ptr<Rendering::Material> MaterialSP();

			void Serialize(TinyXML2::XMLDocument& p_doc, TinyXML2::XMLNode* p_parent) const override;
			void DeSerialize(TinyXML2::XMLElement* p_componentNode) override;

		protected:
			void Init() override;

		private:
			std::shared_ptr<Rendering::Material> m_material;
		};
	}
}