/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Author: <Sujay Shah>
- End Header --------------------------------------------------------*/

#pragma once
#include "Component.h"
#include "Endpoints.h"
#include "SliderBallNames.h"

class Slider : public Component
{
private:
	float m_currentValue;
	float m_minX;
	float m_maxX;
	float m_diff;
	float m_val;
	std::string m_barPrefab;

	//Sprite* m_pSpriteBall;
	Transform* m_pTransform;
	FollowCursor* m_pfollow;
	Endpoints* m_pEndpoints;
	bool m_isPressed;
	SliderBallType m_sliderBallType;
	void UpdateBall();
public:
	Slider();
	~Slider();
	static Component* CreateInstance() { return new Slider(); }
	void Update(float);
	void Serialize(const json& j);
	void LateInitialize();
	void HandleEvent(Event* pEvent);
};

