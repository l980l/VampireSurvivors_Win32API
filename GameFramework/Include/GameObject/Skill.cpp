
#include "Skill.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderCircle.h"
#include "Effect.h"
#include "../GameManager.h"

CSkill::CSkill() :
	m_SkillLevel(1)
{
	SetTypeID<CSkill>();
}

CSkill::CSkill(const CSkill& Obj) :
	CGameObject(Obj)
{
}

CSkill::~CSkill()
{
}

bool CSkill::Init()
{
	m_SkillLevel = 1;

	return true;
}

void CSkill::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	m_AdditionalSkillSpeed = m_Scene->GetPlayer()->GetAdditionSkillSpeed();
	m_AdditionalSkillDamage = m_Scene->GetPlayer()->GetAdditionSkillDamage();
	m_AdditionalSkillDuration = m_Scene->GetPlayer()->GetAdditionSkillDuration();
	m_AdditionalSkillProjectile = m_Scene->GetPlayer()->GetAdditionSkillProjectile();

	if (g_PlayerSelect == 0)
	{
		if ((m_Scene->GetPlayer()->GetPlayerLevel() / 10) == 1)
			m_AdditionalSkillDamage += 0.1f;
		else if ((m_Scene->GetPlayer()->GetPlayerLevel() / 10) == 2)
			m_AdditionalSkillDamage += 0.2f;
		else if ((m_Scene->GetPlayer()->GetPlayerLevel() / 10) == 3)
			m_AdditionalSkillDamage += 0.3f;
		else if ((m_Scene->GetPlayer()->GetPlayerLevel() / 10) == 4)
			m_AdditionalSkillDamage += 0.4f;
		else if ((m_Scene->GetPlayer()->GetPlayerLevel() / 10) == 5)
			m_AdditionalSkillDamage += 0.5f;
	}
}

void CSkill::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CSkill::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);
}

void CSkill::SkillLevelUp()
{
	if (m_SkillLevel >= 8)
		m_SkillLevel = 8;

	else if (m_SkillLevel < 1)
		m_SkillLevel = 1;

	else
	{
		++m_SkillLevel;
	}
}



void CSkill::CollisionBegin(CCollider* Src, CCollider* Dest)
{
}

void CSkill::CollisionEnd(CCollider* Src, CCollider* Dest)
{
}
