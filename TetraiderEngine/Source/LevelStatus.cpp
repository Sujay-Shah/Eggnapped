/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Author: <Moodie Ghaddar>
- End Header --------------------------------------------------------*/

#include <Stdafx.h>

LevelStatus::LevelStatus(): Component(ComponentType::C_LevelStatus), m_eggsToCollect(3), m_enemiesInLevel(0) {}
LevelStatus::~LevelStatus() {}

void LevelStatus::Update(float dt) {
	/*if (TETRA_INPUT.IsKeyTriggered(SDL_SCANCODE_T)) {
		Event* pEvent = new Event(EVENT_OnCamGoToBossRoom, 0.5f);
		TETRA_EVENTS.AddDelayedEvent(pEvent);
	}*/
}

void LevelStatus::Deactivate() {
	pGO = nullptr;
}

void LevelStatus::Serialize(const json& j) {}

void LevelStatus::LateInitialize() {
	TETRA_EVENTS.Subscribe(EVENT_EnemySpawned, this);
	TETRA_EVENTS.Subscribe(EVENT_OnEnemyHealthZero, this);
	TETRA_EVENTS.Subscribe(EVENT_EggCollected, this);
	TETRA_EVENTS.Subscribe(EVENT_OnPlayerHealthZero, this);
}

void LevelStatus::HandleEvent(Event* pEvent) {
	//TODO reset enemies in level to 0 on game restart
	switch (pEvent->Type()) {
		case EVENT_OnLevelInitialized: {
			m_eggsCollected = 0;
			m_eggsToCollect = TETRA_LEVELS.EggsToCollect();
			TETRA_EVENTS.BroadcastEventToSubscribers(&Event(EVENT_EggCounterInitialization, &CollectibleData(m_eggsToCollect)));
			break;
		}
		case EVENT_EnemySpawned: {
			m_enemiesInLevel += 1;
			break;
		}
		case EVENT_EggCollected: {
			CollectibleData* pData = pEvent->Data<CollectibleData>();
			m_eggsCollected += pData->m_value;
			if (m_eggsCollected == m_eggsToCollect) {
				Event* pEvent = new Event(EVENT_LevelComplete, 1.5f);
				TETRA_EVENTS.AddDelayedEvent(pEvent);
			}
			else if (TETRA_LEVELS.IsBossLevel() && m_eggsCollected == m_eggsToCollect - 1) {
				Event* pEvent = new Event(EVENT_OnCamGoToBossRoom, 1.5f);
				TETRA_EVENTS.AddDelayedEvent(pEvent);
			}
			break;
		}
		case EVENT_OnEnemyHealthZero: {
			m_enemiesInLevel -= 1;
			if (m_enemiesInLevel < 0) m_enemiesInLevel = 0;
			if (m_enemiesInLevel == 0) {
				//Event* pEvent = new Event(EVENT_LevelComplete, 3.0f);
				//TETRA_EVENTS.AddDelayedEvent(pEvent);
			}
			break;
		}
		case EVENT_OnPlayerHealthZero: {
			Event* pEvent = new Event(EVENT_LevelInComplete, 3.0f);
			TETRA_EVENTS.AddDelayedEvent(pEvent);
		}
	}
}