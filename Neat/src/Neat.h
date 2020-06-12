#pragma once

// For using in Neat applications -------------------------------------------
#include "Neat/Core/Application.h"
#include "Neat/Core/Layer.h"
#include "Neat/Core/Log.h"
#include "Neat/Core/Types.h"
#include "Neat/Core/Exceptions.h"

#include "Neat/Core/Input.h"
#include "Neat/Core/KeyCodes.h"
#include "Neat/Core/MouseCodes.h"

#include "Neat/Core/Timer.h"

#include "Neat/Events/Event.h"
#include "Neat/Events/EventManager.h"
// ----------------------------------------------------------------------------

// Graphics -------------------------------------------------------------------
#include "Neat/Graphics/Renderer.h"
#include "Neat/Graphics/Renderer2D.h"
#include "Neat/Graphics/RenderCommand.h"

#include "Neat/Graphics/Texture.h"
#include "Neat/Graphics/SubTexture2D.h"

#include "Neat/Graphics/Camera.h"
// ----------------------------------------------------------------------------

// ECS ------------------------------------------------------------------------
#include "Neat/ECS/SystemManager.h"
#include "Neat/ECS/System.h"
#include "Neat/ECS/Entity.h"
#include "Neat/ECS/Systems/Render2DSystem.h"
#include "Neat/ECS/Systems/Camera2DControllerSystem.h"
#include "Neat/ECS/Systems/Camera3DControllerSystem.h"
#include "Neat/ECS/Components.h"
// ----------------------------------------------------------------------------

// Math -----------------------------------------------------------------------
#include "Neat/Math/Vector.h"
#include "Neat/Math/VectorOperations.h"
#include "Neat/Math/Matrix.h"
#include "Neat/Math/MatrixOperations.h"
#include "Neat/Math/Transform.h"
#include "Neat/Math/Utility.h"
#include "Neat/Math/Projection.h"
// ----------------------------------------------------------------------------