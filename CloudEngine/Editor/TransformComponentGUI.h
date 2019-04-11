#pragma once
#include "AComponentGUI.h"
#include "Core/ECS/Component/Component.h"
#include "SmartLabelEdit.h"
#include <vector>
#include "CloudMath/Vector/Vector3.h"

class SmartLabelEdit;
namespace QtEditor
{
	class Vec3Widget;

	class TransformComponentGUI : public AComponentGUI
	{
		Q_OBJECT
	public:
		explicit TransformComponentGUI(const std::string& p_name, QWidget* p_parent = nullptr);
		~TransformComponentGUI();
		void Setup();

		void SetupFrame() override;
		void BindComponent(std::shared_ptr<Core::AComponent> p_component) override;

		void SetupPositions() const ;
		void SetupRotations() const;
		void SetupScale() const;

	public slots:
		void OnValuePositionChanged(CloudMath::Vector3f p_vector) const ;
		void OnValueScaleChanged(CloudMath::Vector3f p_vector) const ;
		void OnValueRotationChanged(CloudMath::Vector3f p_vector) const ;

	private:
		std::shared_ptr<Core::Components::Transform>  m_transform;
		Vec3Widget* m_positions;
		Vec3Widget* m_rotations;
		Vec3Widget* m_scalers;
	};
}
