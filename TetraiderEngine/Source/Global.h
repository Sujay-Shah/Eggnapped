/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Author: <Holden Profit>
- End Header --------------------------------------------------------*/

#pragma once

#ifndef GLOBAL_DEFINES_H
#define GLOBAL_DEFINES_H

#define TETRA_EVENTS Singleton<EventManager>::GetInstance()
#define TETRA_MEMORY Singleton<MemoryManager>::GetInstance()
#define TETRA_GAME_CONFIG Singleton<GameConfig>::GetInstance()
#define TETRA_GAME_STATE Singleton<GameStateManager>::GetInstance()
#define TETRA_FRAMERATE Singleton<FrameRateManager>::GetInstance()
#define TETRA_POST_PROCESSING Singleton<PostProcessing>::GetInstance()
#define TETRA_RENDERER Singleton<RenderManager>::GetInstance()
#define TETRA_INPUT Singleton<InputManager>::GetInstance()
#define TETRA_RESOURCES Singleton<ResourceManager>::GetInstance()
#define TETRA_LEVELS Singleton<LevelManager>::GetInstance()
#define TETRA_DEBUG Singleton<DebugManager>::GetInstance()
#define TETRA_AUDIO Singleton<AudioManager>::GetInstance()
#define TETRA_PHYSICS Singleton<PhysicsManager>::GetInstance()
#define TETRA_GAME_OBJECTS Singleton<GameObjectManager>::GetInstance()
#define TETRA_LUA Singleton<LuaScript>::GetInstance()
#define TETRA_LEVEL_GEN Singleton<FloorPlanGenerator>::GetInstance()
#define TETRA_IMGUI Singleton<ImguiManager>::GetInstance()
#define TETRA_EDITOR Singleton<LevelEditor>::GetInstance()
#define TETRA_COMPONENTS Singleton<ComponentFactory>::GetInstance()
#define TETRA_UI Singleton<UIManager>::GetInstance()
#define TETRA_PLAYERSTATS Singleton<PlayerStatsManager>::GetInstance()

#endif