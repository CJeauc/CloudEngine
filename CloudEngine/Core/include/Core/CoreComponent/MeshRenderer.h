#pragma once

#include <Core/CoreAPI.h>
#include <Core/ECS/Component/Component.h>
#include <Rendering/Resource/Mesh.h>
#include <Rendering/Shading/Material.h>
#include <Rendering/Resource/Model.h>

/*
The MeshRenderer Component hold a referemce to a rendering Mesh
The component it self only has data such as the mesh reference

This component Only has the basic functionality for our first prototype to work

This component is manager by the Rendering System
*/

namespace Core
{
	namespace Components
	{
		class CORE_API MeshRenderer : public Component<MeshRenderer>
		{
		public:
			MeshRenderer();
			~MeshRenderer();

			void Serialize(TinyXML2::XMLDocument& p_doc, TinyXML2::XMLNode* p_parent) const override;
			void DeSerialize(TinyXML2::XMLElement* p_componentNode) override;
			
			void SetModel(std::shared_ptr<Rendering::Model> p_model);
			std::shared_ptr<Rendering::Model> Model();

		private:
			std::shared_ptr<Rendering::Model> m_model;
		};
	}
}