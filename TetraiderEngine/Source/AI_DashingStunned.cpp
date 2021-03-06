/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Author: <Hyoyup Chung>
- End Header --------------------------------------------------------*/

#include <Stdafx.h>

AI_DashingStunned::AI_DashingStunned()
: AI_State(NPC_State_DashingStunned) {

}

AI_DashingStunned::~AI_DashingStunned(){
}

void AI_DashingStunned::OnEnter(){	
	triedSofar = 0.0f;
	tryTime = 2.0f;
	pAgent->PlayAnimation(3);
}

void AI_DashingStunned::OnUpdate(float dt){
	if (triedSofar > tryTime) {
		pAgent->ChangeState(NPC_IDLE);
	}
	else {
		triedSofar += dt;
	}
}

void AI_DashingStunned::OnExit(){
	pAgent->ControlAnimationOnVelocity(true);
}

void AI_DashingStunned::HandleEvent(Event* pEvent) {

}

void AI_DashingStunned::Serialize(const json& j) {
}