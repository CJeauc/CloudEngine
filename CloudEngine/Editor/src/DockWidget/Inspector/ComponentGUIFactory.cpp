#include "stdafx.h"
#include "ComponentGUIFactory.h"

#include "Core/CoreComponent/Transform.h"
#include "Core/CoreComponent/CameraComponent.h"
#include "Core/CoreComponent/LightComponent.h"
#include "Core/CoreComponent/MaterialRenderer.h"
#include "Core/CoreComponent/MeshRenderer.h"

#include "MeshRendererGUI.h"
#include "LightComponentGUI.h"
#include "TransformComponentGUI.h"
#include "MaterialComponentGUI.h"
#include "CameraComponentGUI.h"

using namespace QtEditor;

AComponentGUI* ComponentGUIFactory::CreateComponentGUI(Core::ComponentTypeId p_cTypeID, QWidget* p_parent)
{

	if (p_cTypeID == Core::Components::Transform::StaticComponentTypeId)
		return new TransformComponentGUI("Transform", p_parent);

	if (p_cTypeID == Core::Components::CameraComponent::StaticComponentTypeId)
		return new CameraComponentGUI("Camera", p_parent);

	if (p_cTypeID == Core::Components::LightComponent::StaticComponentTypeId)
		return new LightComponentGUI("Light", p_parent);

	if (p_cTypeID == Core::Components::MaterialRenderer::StaticComponentTypeId)
		return new MaterialComponentGUI("Material", p_parent);

	if (p_cTypeID == Core::Components::MeshRenderer::StaticComponentTypeId)
		return new MeshRendererGUI("Mesh", p_parent);

	else
		return nullptr;
}
