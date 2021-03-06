/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Author: <Moodie Ghaddar>
- End Header --------------------------------------------------------*/

#include <Stdafx.h>

FlashOnTakeDamage::FlashOnTakeDamage(): Component(ComponentType::C_FlashOnTakeDamage), m_flashTime(2.0f) {}
FlashOnTakeDamage::~FlashOnTakeDamage() {}

void FlashOnTakeDamage::Deactivate() {
	pGO = nullptr; 
	m_pSprite = nullptr; 
}

void FlashOnTakeDamage::Update(float dt) {
	if (m_flashTime > 1.f)
		return;

	m_pSprite->SetSaturationColor(Lerp(m_flashColor, m_originalColor, m_flashTime));
	m_flashTime += dt*m_decaySpeed;

	if(m_flashTime > 1.f)
		m_pSprite->SetSaturationColor(m_originalColor); // In order not to overshoot
}

void FlashOnTakeDamage::Serialize(const json& j) {
	m_decaySpeed = ParseFloat(j, "decaySpeed");
	m_flashColor = ParseColor(j, "flashColor");
}

void FlashOnTakeDamage::LateInitialize() {
	if (!m_pSprite) {
		if (pGO)
			m_pSprite = pGO->GetComponent<Sprite>(ComponentType::C_Sprite);
		else {
			printf("No Game Object found. FlashOnTakeDamage component failed to operate.\n");
			return;
		}

		if (!m_pSprite) {
			printf("No Sprite component found. FlashOnTakeDamage component failed to operate.\n");
			assert(m_pSprite);
			return;
		}
	}

	m_originalColor = m_pSprite->GetSaturationColor();
}

void FlashOnTakeDamage::HandleEvent(Event* pEvent) {
	if (pEvent->Type() == EventType::EVENT_OnTakeDamage)
		Flash();
}

void FlashOnTakeDamage::Flash() {
	m_flashTime = 0.0f;
}