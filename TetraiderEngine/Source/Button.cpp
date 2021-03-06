/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Author: <Sujay Shah>
- End Header --------------------------------------------------------*/

#include <Stdafx.h>

#define OPTION_WINDOWED 0
#define OPTION_FULLSCREEN 1

Button::Button() :Component(ComponentType::C_Button) 
{
	m_isQuit = false;
	m_isRestart = false;
	m_isHover = false;
}
Button::~Button() {}

void Button::Update(float dt)
{
	m_pSprite->SetVOffset(0);
}

void Button::LateUpdate(float dt) {
	if (!m_isHover && m_pSprite->GetVOffset() > 0 && m_pSprite->GetVOffset() < 0.5f) {
		m_isHover = true;
		Audio* pAudio = pGO->GetComponent<Audio>(C_Audio);
		if (pAudio)
			pAudio->Play(0);
	}
	else if(m_isHover && m_pSprite->GetVOffset() < 0.1f) {
		m_isHover = false;
	}
}

void Button::Serialize(const json & j)
{
	m_levelNumber = ParseInt(j, "level");
	m_isQuit = ParseBool(j, "quit");
	m_isRestart = ParseBool(j,"restart");
	m_isLoadCanvas = ParseBool(j, "isLoadCanvas");
	m_isCloseShop = ParseBool(j, "isCloseShop");
	m_isApplyButton = ParseBool(j, "isApplyButton");
	m_isResume = ParseBool(j, "resume");
	if (m_isLoadCanvas) {
		m_canvasToActivate = (CanvasType)ParseInt(j, "canvasToActivate");
		m_canvasToDeActivate = (CanvasType)ParseInt(j, "canvasToDeActivate");
	}
	m_isRandomGenerated = ParseBool(j, "isRandomGenerated");
	m_isLoadLevelEditor = ParseBool(j, "isLoadLevelEditor");
}

void Button::LateInitialize()
{
	if (!m_pSprite) 
	{
		if (pGO)
			m_pSprite = pGO->GetComponent<Sprite>(ComponentType::C_Sprite);
		else {
			printf("No Game Object found. Button component failed to operate.\n");
			return;
		}

		if (!m_pSprite) {
			printf("No Sprite component found. Button component failed to operate.\n");
			assert(m_pSprite);
			return;
		}
	}
	if (m_isApplyButton)
	{
		TETRA_EVENTS.Subscribe(EVENT_OnResolutionChanged, this);
		TETRA_EVENTS.Subscribe(EVENT_OnWindowedChanged, this);
	}

}

void Button::HandleEvent(Event* pEvent)
{
	if (!pGO->m_isActive) return; 

	if (pEvent->Type() == EVENT_OnResolutionChanged)
	{
		ChoiceData* pChoiceData = pEvent->Data<ChoiceData>();
		m_Choice[(int)ChoiceType::CHOICE_RESOLUTION] = pChoiceData->m_choiceData;
	}

	if (pEvent->Type() == EVENT_OnWindowedChanged)
	{
		ChoiceData* pChoiceData = pEvent->Data<ChoiceData>();
		m_Choice[(int)ChoiceType::CHOICE_FULLSCREEN] = pChoiceData->m_choiceData;
	}

	if (pEvent->Type() == EVENT_OnCollide)
	{
		OnCollideData* pData = pEvent->Data<OnCollideData>();
		if (pData->pGO->m_tag == T_Cursor) {
			if (TETRA_UI.m_ignoreButtonsForOneFrame) {
				TETRA_UI.m_ignoreButtonsForOneFrame = false;
				return;
			}

			m_pSprite->SetVOffset(0.3333f);
			if (TETRA_INPUT.IsMouseButtonPressed(MOUSEBTN::MOUSE_BTN_LEFT)) {
				m_pSprite->SetVOffset(0.6666f);
			}
			else if (TETRA_INPUT.IsMouseButtonReleased(MOUSEBTN::MOUSE_BTN_LEFT)) {
				Audio* pAudio = pGO->GetComponent<Audio>(C_Audio);
				if (pAudio)
					pAudio->Play(1);
				if (m_isQuit) {
					TETRA_EVENTS.BroadcastEvent(&Event(EVENT_WINDOW_CLOSED));
				}
				else if (m_isRestart) {
					TETRA_LEVELS.ActivateRandomGeneration(false);
					TETRA_LEVELS.ResetGame();
					TETRA_PLAYERSTATS.ClearStats();
					TETRA_LEVELS.ChangeLevel(m_levelNumber);
					TETRA_EVENTS.BroadcastEventToSubscribers(&Event(EventType::EVENT_EXITING_GAME_LEVEL));
				}
				else if (m_isResume)
				{
					TETRA_EVENTS.BroadcastEvent(&Event(EVENT_INPUT_PAUSEGAME,&InputButtonData(false,true,false)));
				}
				else if (m_isLoadLevelEditor) {
					TETRA_LEVELS.LoadLevelEditor(m_levelNumber);
					TETRA_AUDIO.StopSongs();
				}
				else if(m_isLoadCanvas)
				{
					TETRA_UI.ActivateCanvas(m_canvasToActivate);
					TETRA_UI.DeactivateCanvas(m_canvasToDeActivate);
				}
				else if (m_isCloseShop) {
					TETRA_EVENTS.BroadcastEventToSubscribers(&Event(EventType::EVENT_ShopClosed));
				}
				else if (m_isApplyButton) 
				{
					TETRA_GAME_CONFIG.SelectResolutionAndScreenMode(m_Choice[(int)ChoiceType::CHOICE_RESOLUTION], m_Choice[(int)ChoiceType::CHOICE_FULLSCREEN] == OPTION_FULLSCREEN);
				}
				else {
					TETRA_LEVELS.ActivateRandomGeneration(m_isRandomGenerated);
					TETRA_LEVELS.ChangeLevel(m_levelNumber);
					TETRA_EVENTS.BroadcastEventToSubscribers(&Event(EventType::EVENT_EXITING_GAME_LEVEL));
				}
			}
		}
	}

	
}

#undef OPTION_WINDOWED
#undef OPTION_FULLSCREEN