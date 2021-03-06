/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Author: <Hyoyup Chung>
- End Header --------------------------------------------------------*/

#include <Stdafx.h>

AI_RatBossRetreat::AI_RatBossRetreat()
: AI_State(NPC_State_RatBossRetreat) {
	m_retreatFor = 0.75f;
}

AI_RatBossRetreat::~AI_RatBossRetreat(){
}

void AI_RatBossRetreat::OnEnter(){
	m_retreatTimer = 0.0f;
	pAgent->SetKnockBackMultiplier(0.0f);
}

void AI_RatBossRetreat::OnUpdate(float dt){
	pAgent->LookInDirectionOfMovement();
	if (m_retreatTimer > m_retreatFor && pAgent->IsAttackAnimComplete()) {
		pAgent->ChangeState(NPC_ENGAGE);
	}		
	if (pAgent->UseAttack(0)) {
		pAgent->PlayAttackAnim();
	}
	m_retreatTimer += dt;
}

void AI_RatBossRetreat::OnExit(){
	pAgent->SetKnockBackMultiplier(1.0f);
}


void AI_RatBossRetreat::HandleEvent(Event* pEvent) {

}

void AI_RatBossRetreat::Serialize(const json& j) {
}