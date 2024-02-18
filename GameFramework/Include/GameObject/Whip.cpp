
#include "Whip.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../GameManager.h"
#include "../GameObject/GameObject.h"
#include "WhipProjectile.h"
#include "WhipProjectile2.h"
#include "../Scene/SceneResource.h"

CWhip::CWhip()
{
	SetTypeID<CWhip>();
}

CWhip::CWhip(const CWhip& Obj) :
	CSkill(Obj)
{
}

CWhip::~CWhip()
{
}

bool CWhip::Init()
{
	CSkill::Init();

	m_WhipCount = 1;
	m_WhipSpawnCount = 0;

	m_WhipCoolTime = 1.5f;	// 쿨타임
	m_SkillUseTime = m_WhipCoolTime;
	m_SkillElementUseTime = 0.12f;

	return true;
}

void CWhip::Update(float DeltaTime)
{
	CSkill::Update(DeltaTime);

	m_Pos = m_Scene->GetPlayer()->GetPos();

	m_SkillUseTime += DeltaTime;

	m_SkillElementUseTime += DeltaTime;

	int Dir = m_Scene->GetPlayer()->GetPlayerDir();

	if (Dir == 0)
	{
		Dir = -1;
	}

	// 스킬 쿨타임은 스킬 지속시간이 전부 끝나고 돈다. 따라서 그냥 쿨타임과 지속시간을 
	// 더해서 처리했다.
	if (m_SkillUseTime >= m_WhipCoolTime &&
		m_SkillElementUseTime >= 0.12f)
	{
		if (m_WhipSpawnCount >= m_WhipCount + m_AdditionalSkillProjectile)
		{
			m_SkillUseTime -= m_WhipCoolTime;
			m_WhipSpawnCount = 0;
		}

		else if (m_WhipSpawnCount % 2)
		{
			m_Scene->GetSceneResource()->SoundPlay("Whip");
			Vector2 Target = m_Pos - m_Scene->GetCamera()->GetPos();
			Target = Target + Vector2(-500 * Dir, 20* m_WhipSpawnCount);
			CWhipProjectile2* WhipProjectile2 = m_Scene->CreateObject<CWhipProjectile2>("WhipProjectile2", Target);
			WhipProjectile2->SetWhip(this);
			++m_WhipSpawnCount;
			m_SkillElementUseTime = 0.f;
		}

		else
		{
			m_Scene->GetSceneResource()->SoundPlay("Whip");
			Vector2 Target = m_Pos - m_Scene->GetCamera()->GetPos();
			Target = Target + Vector2(500 * Dir, 20 * m_WhipSpawnCount);
			CWhipProjectile* WhipProjectile = m_Scene->CreateObject<CWhipProjectile>("WhipProjectile", Target);
			WhipProjectile->SetWhip(this);
			++m_WhipSpawnCount;
			m_SkillElementUseTime = 0.f;
		}
	}
}

void CWhip::PostUpdate(float DeltaTime)
{
	CSkill::PostUpdate(DeltaTime);
}

void CWhip::Render(HDC hDC, float DeltaTime)
{
	CSkill::Render(hDC, DeltaTime);
}

void CWhip::SkillLevelUp()
{
	CSkill::SkillLevelUp();

	// 채찍 갯수는 최대 3개까지 오름.
	m_WhipCount = (m_SkillLevel + 2) / 3;
}

