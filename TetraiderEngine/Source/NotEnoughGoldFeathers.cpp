/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Author: <Moodie Ghaddar>
- End Header --------------------------------------------------------*/

#include <Stdafx.h>


NotEnoughGoldFeathers::NotEnoughGoldFeathers():Component(ComponentType::C_NotEngouhGoldFeathers)
{
	TETRA_EVENTS.Subscribe(EVENT_ShopOpened, this);
	TETRA_EVENTS.Subscribe(EVENT_ShopClosed, this);
	TETRA_EVENTS.Subscribe(EVENT_NotEnoughGoldenFeathers, this);
	TETRA_EVENTS.Subscribe(EVENT_EnoughGoldenFeathers, this);
}

NotEnoughGoldFeathers::~NotEnoughGoldFeathers(){}


void NotEnoughGoldFeathers::Update(float dt)
{

}

void NotEnoughGoldFeathers::Serialize(const json & j)
{
}

void NotEnoughGoldFeathers::HandleEvent(Event * pEvent)
{
	if (pEvent->Type() == EVENT_ShopClosed || pEvent->Type() == EVENT_ShopOpened || pEvent->Type() == EVENT_EnoughGoldenFeathers) {
		pGO->m_isRender = false;
	}
	else if (pEvent->Type() == EVENT_NotEnoughGoldenFeathers) {
		pGO->m_isRender = true;
	}
}

void NotEnoughGoldFeathers::LateInitialize()
{

}

