/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Author: <Moodie Ghaddar>
- End Header --------------------------------------------------------*/

#pragma once
#ifndef NPCCONTROLLER_H
#define NPCCONTROLLER_H

class Weapon;

#define ObstacleAvoidanceFrontCheack 125.0f
#define ObstacleAvoidanceSideCheck 125.0f
#define ObstacleAvoidanceSideCheckAngle 40.0f

enum class ObstacleAvoidanceDirection {
	RIGHT,
	LEFT
};

class NPCController : public Agent {
public:
	NPCController();
	~NPCController();
	static Component* CreateInstance() { return new NPCController(); }
	virtual void Deactivate();
	virtual void Update(float dt);
	virtual void LateUpdate(float dt);
	virtual void LateInitialize();
	virtual void Serialize(const json& j);
	virtual void HandleEvent(Event* pEvent);

	void ChangeState(NPC_CONTROLLER_AI);
	void MoveToPlayer();
	void GoToPositionAroundPlayer();
	void MoveAwayFromPlayer(float dist);
	void GoToStartingPoint();
	bool UseAttack(int attack);
	bool IsArrivedAtDestination();
	bool IsPlayerInSight();
	bool IsPlayerOutOfSight();
	bool IsPlayerTooClose(float distance);
	bool IsInAttackRange();
	bool IsTooFarFromStartingPoint();
	void PlayAnimation(int animation);
	void PlayReactionEffect();
	void SetDestinationToRandomPointInZone();
	void SetVelocityToZero();
	void StopMoving();
	void SetTargetDestination(const Vector3D& pos);
	void SetPositionBehindPlayer(float distance);
	void SetKnockBackMultiplier(float knockBackMultiplier);
	void LookInDirectionOfMovement();
	void LookAtPlayer();
	void LookAtPlayer(float offsetAngle);
	void SetProjectileSpeed(float speed);
	void SetSpeedMultiplier(float speedMultiplier) { m_speedMultiplier = speedMultiplier; }
	bool RollDie(float probability);
	void SetAvoidObstacles(bool active) { m_isAvoidObstacles = active; }
	void ControlAnimationOnVelocity(bool active) { m_isControlAnimationOnVelocity = active; }
	bool IsAttackAnimComplete();
	void PlayAttackAnim();
	BossPhase GetCurrentPhase();
	void SteerTowardPlayer(float distance);
	void MoveInLookDirection(float distance);
protected:
	Weapon* m_pWeapon;
	float GetSquareDistanceToPlayer();
private:
	void EnterBoss();
	void ExitBoss();
	AIStateFactory AIStateFactory;
	AI_State* m_AIStates[NPC_NUM_BEHAVIOR];
	NPC_CONTROLLER_AI m_currentState;
	NPC_CONTROLLER_AI m_previousState;
	float m_detectionRadius;
	float m_outOfSightRadius;
	float m_zoneWidth;
	float m_zoneHeight;
	float m_attackRange;
	float m_speedMultiplier;
	Vector3D m_startingPoint;
	Vector3D m_targetDestination;
	Vector3D m_secondaryDestination;
	bool m_arrivedAtDestination;
	bool m_isPlayerDead;
	bool m_isAvoidObstacles;
	bool m_isAvoidingObstacle;
	bool m_isDeathAnim;
	int m_deathAnim;
	bool m_isAttackAnim;
	bool m_isBoss;
	bool m_isActive;
	int m_attackAnim;
	bool m_isReactionAnim;
	int m_reactionAnim;
	float m_reactionTimer;
	float m_nextReactionIn;
	std::string m_reactionPrefab;
	const Transform* m_pPlayerTransform;
	GameObjectTag m_tagsToIgnore[7];
	GameObjectTag m_tagsToIgnoreForObstacleAvoidance[4];
	ObstacleAvoidanceDirection m_avoidDirection;
	BossPhase m_currentBossPhase;

	bool IsPlayerOutOfScreen();
	void SetSecondaryTargetDestination(const Vector3D& pos) { m_secondaryDestination = pos; }
	void CheckForObstacleAvoidance();
	void AvoidObstacles(float dt);
	float m_stuckTimer = 0.0f;
	Vector3D m_prevPos;

	std::string m_healthBarPrefab;
	std::string m_puffParticlePrefab;
	float m_puffOffset;
	Vector3D m_healthBarPosOffset;
	float m_healthScale;
	GameObject* m_healthBarUI;

	bool m_isBossEntering;
};

#endif

