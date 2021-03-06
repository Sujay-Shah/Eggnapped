/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Author: <Hyoyup Chung>
- End Header --------------------------------------------------------*/

#include <Stdafx.h>

AI_HitNRunRetreat::AI_HitNRunRetreat()
: AI_State(NPC_State_HitNRunRetreat) {
	minimumRetreat = 1.5;

}

AI_HitNRunRetreat::~AI_HitNRunRetreat(){

}

void AI_HitNRunRetreat::OnEnter(){
	minDistanceToPlayer = 210.0f;
	tryTimeDuration = RandomFloat(1.0f, 2.2f);
	triedMovingSoFar = 0.0f;
	sinceRetreat = 0.0f;
	pAgent->LookInDirectionOfMovement();
	pAgent->MoveAwayFromPlayer(150);
}

void AI_HitNRunRetreat::OnUpdate(float dt){
	pAgent->LookInDirectionOfMovement();
	pAgent->SetSpeedMultiplier(3.0f);
	if (!pAgent->IsPlayerTooClose(minDistanceToPlayer) && (sinceRetreat > minimumRetreat)){
		pAgent->ChangeState(NPC_ATTACK);
		return;
	}
	if ((triedMovingSoFar > tryTimeDuration) && (sinceRetreat > minimumRetreat)) {
		pAgent->StopMoving();
		pAgent->ChangeState(NPC_ATTACK);
		//pAgent->GoToPositionAroundPlayer(minDistanceToPlayer);
		//triedMovingSoFar = 0.0f;
		return;
	}
	if (pAgent->IsArrivedAtDestination()) {
		if (!pAgent->IsPlayerTooClose(minDistanceToPlayer) && (sinceRetreat > minimumRetreat)) {
			pAgent->ChangeState(NPC_ATTACK);
		}
		else {
			pAgent->MoveAwayFromPlayer(150);
			triedMovingSoFar = 0.0f;
		}
	}
	triedMovingSoFar += dt;
	sinceRetreat += dt;
}

void AI_HitNRunRetreat::OnExit(){
}


void AI_HitNRunRetreat::HandleEvent(Event* pEvent) {

}

void AI_HitNRunRetreat::Serialize(const json& j) {
}