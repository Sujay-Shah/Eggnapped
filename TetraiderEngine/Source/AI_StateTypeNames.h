/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Author: <Hyoyup Chung>
- End Header --------------------------------------------------------*/

// NPC States
REGISTER_STATE(NPC_State_Idle)
REGISTER_STATE(NPC_State_IdleForDuration)
REGISTER_STATE(NPC_State_Engage)
REGISTER_STATE(NPC_State_Attack)
REGISTER_STATE(NPC_State_RangeAttack)
REGISTER_STATE(NPC_State_Retreat)
REGISTER_STATE(NPC_State_MoveToRandomPointInZone)
REGISTER_STATE(NPC_State_WalkTowardPlayerIdle)
REGISTER_STATE(NPC_State_WalkTowardPlayerAttack)
REGISTER_STATE(NPC_State_WalkTowardPlayerEngage)
REGISTER_STATE(NPC_State_DashingAttack)
REGISTER_STATE(NPC_State_DashingEngage)
REGISTER_STATE(NPC_State_DashingStunned)
REGISTER_STATE(NPC_State_HitNRunAttack)
REGISTER_STATE(NPC_State_HitNRunRetreat)
REGISTER_STATE(NPC_State_HitNRunEngage)
REGISTER_STATE(NPC_State_BomberAttack)
REGISTER_STATE(NPC_State_BomberRetreat)
REGISTER_STATE(NPC_State_Reaction)
REGISTER_STATE(NPC_State_EnemyBatReaction)
REGISTER_STATE(NPC_State_RatBossIdle)
REGISTER_STATE(NPC_State_RatBossReaction)
REGISTER_STATE(NPC_State_RatBossEngage)
REGISTER_STATE(NPC_State_RatBossAttack)
REGISTER_STATE(NPC_State_RatBossRetreat)
REGISTER_STATE(NPC_State_RockBossIdle)
REGISTER_STATE(NPC_State_RockBossReaction)
REGISTER_STATE(NPC_State_RockBossEngage)
REGISTER_STATE(NPC_State_RockBossAttack)


// Add Some Other Controller States Below...
//REGISTER_STATE(Player_State_Idle)