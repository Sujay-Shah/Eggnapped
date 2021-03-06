/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Author: <Hyoyup Chung>
- End Header --------------------------------------------------------*/

#include <Stdafx.h>

AI_DashingAttack::AI_DashingAttack()
: AI_State(NPC_State_DashingAttack) {

}

AI_DashingAttack::~AI_DashingAttack(){
}

void AI_DashingAttack::OnEnter(){	
	pAgent->SetPositionBehindPlayer(175.0f);
	pAgent->SetSpeedMultiplier(4.5f);
	triedSofar = 0.0f;
	tryTime = 1.5f;
	pAgent->SetAvoidObstacles(false);
	pAgent->PlayAnimation(1);
}

void AI_DashingAttack::OnUpdate(float dt){
	if (triedSofar > tryTime) {
		pAgent->ChangeState(NPC_ENGAGE);
	}
	else {
		triedSofar += dt;
	}
	//if (pAgent->IsArrivedAtDestination()){
	//	pAgent->ChangeState(NPC_ENGAGE);
	//}
}

void AI_DashingAttack::OnExit(){
	pAgent->SetSpeedMultiplier(1.0f);
	pAgent->SetAvoidObstacles(true);
	pAgent->ControlAnimationOnVelocity(true);
}

void AI_DashingAttack::HandleEvent(Event* pEvent) {
	switch (pEvent->Type()) {
		case EventType::EVENT_ForceKnockBack:
			pAgent->SetVelocityToZero();
			pAgent->ChangeState(NPC_STUNNED);
			break;
		case EventType::EVENT_OnCollide:
			OnCollideData * pData = pEvent->Data<OnCollideData>();
			if (pData->pGO->m_tag==T_Obstacle) {
				pAgent->ChangeState(NPC_ENGAGE);
			}
			break;
	}
}

void AI_DashingAttack::Serialize(const json& j) {
}