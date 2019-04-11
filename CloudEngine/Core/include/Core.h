#pragma once

#include "Core/Managers/ResourceManager.h"
#include "Core/Managers/Register.h"
#include "Core/Managers/TypeFunctions.h"

#include "Core/Engine/CloudEngine.h"

// ECS //

#include "Core/ECS/ECS.h"

// Utils
#include "Core/ECS/Utils/Algorithm.h"
#include "Core/ECS/FamilyTypeId.h"
#include "Core/ECS/Types.h"

// Entities
#include "Core/ECS/Entity/AEntity.h"
#include "Core/ECS/Entity/Entity.h"
#include "Core/ECS/Entity/EntityManager.h"

// Component
#include "Core/ECS/Component/AComponent.h"
#include "Core/ECS/Component/Component.h"
#include "Core/ECS/Component/ComponentManager.h"

// System
#include "Core/ECS/System/ASystem.h"
#include "Core/ECS/System/System.h"
#include "Core/ECS/System/SystemManager.h"

// CoreEntity
#include "Core/CoreEntity/GameObject.h"

// CoreComponent
#include "Core/CoreComponent/Transform.h"
#include <Core/CoreComponent/MaterialRenderer.h>
#include <Core/CoreComponent/MeshRenderer.h>

// CoreSystem
//#include "Core/CoreSystem/.h"

//Scene Management
#include <Core/Scene/SceneManager.h>