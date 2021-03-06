/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Author: <Moodie Ghaddar>
- End Header --------------------------------------------------------*/

#include <Stdafx.h>

AOEAttack::AOEAttack(float coolDown, int baseDamage, float knockBackSpeed, AttackType type, float radius):
	Attack(coolDown, baseDamage, knockBackSpeed, type),
	m_radius(radius)
{}

AOEAttack::~AOEAttack() {}

void AOEAttack::Update(float dt) {
	Attack::Update(dt);
}

bool AOEAttack::Use(const Vector3D& position) {
	if (!Attack::Use(position)) return false;

	const std::vector<GameObject*> gameObjectsWithHealthComponents = TETRA_GAME_OBJECTS.GetObjectsWithHealthComponents();

	// Currently this affects players and enemies
	for (unsigned int i = 0; i < gameObjectsWithHealthComponents.size(); ++i) {
		Transform* pTransform = gameObjectsWithHealthComponents[i]->GetComponent<Transform>(ComponentType::C_Transform);
		if (StaticPointToStaticCircle(pTransform->GetPosition(), position, m_radius)) {
			Health* pHealth = gameObjectsWithHealthComponents[i]->GetComponent<Health>(ComponentType::C_Health);
			Vector3D dirOfAttack = pTransform->GetPosition() - position;
			dirOfAttack.Normalize();
			pHealth->TakeDamage(m_baseDamage, dirOfAttack, m_knockBackSpeed, false);
		}
	}

	return true;
}