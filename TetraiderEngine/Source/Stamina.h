/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Author: <Moodie Ghaddar>
- End Header --------------------------------------------------------*/

#pragma once
#ifndef STAMINA_H
#define STAMINA_H

class Stamina : public Component {
public:
	Stamina();
	~Stamina();
	static Component* CreateInstance() { return new Stamina(); }
	virtual void Deactivate();
	virtual void Update(float dt);
	virtual void Serialize(const json& j);
	virtual void LateInitialize();
	virtual void LateUpdate(float dt) {}
	virtual void HandleEvent(Event* pEvent);
	bool IsStaminaEmpty() { return m_isEmpty; }
	bool IsStaminaFull() { return m_isFull; }
	bool UseStamina(float dt);
	float GetCurrentStamina() const { return m_currentStamina; }
	float GetMaxStamina() const { return m_maxStamina; }
private:
	float m_currentStamina;
	float m_maxStamina;
	float m_useSpeed;
	float m_rechargeSpeed;
	float m_rechargeCoolDown;
	float m_timeFromLastUsed;
	bool m_isEmpty;
	bool m_isFull;
};

#endif

