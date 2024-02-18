
#include "Lightning.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../GameManager.h"
#include "../GameObject/GameObject.h"
#include "FallingLightning.h"

CLightning::CLightning()
{
	SetTypeID<CLightning>();
}

CLightning::CLightning(const CLightning& Obj) :
	CSkill(Obj)
{
}

CLightning::~CLightning()
{
}

bool CLightning::Init()
{
	CSkill::Init();

	m_LightningCount = 2;

	m_LightningCoolTime = 4.5f;	// 쿨타임
	m_SkillUseTime = m_LightningCoolTime;

	return true;
}

void CLightning::Update(float DeltaTime)
{
	CSkill::Update(DeltaTime);

	m_Pos = m_Scene->GetPlayer()->GetPos();

	m_SkillUseTime += DeltaTime;

	// 스킬 쿨타임은 스킬 지속시간이 전부 끝나고 돈다. 따라서 그냥 쿨타임과 지속시간을 
	// 더해서 처리했다.
	if (m_SkillUseTime >= m_LightningCoolTime)
	{
		std::list<CSharedPtr<CMonster>> MonsterList = m_Scene->GetMonsterList();

		// 비었다면 바로 리턴해서 쿨 안돌게 함.
		if (MonsterList.empty())
			return;

		// 셔플
		for (int j = 0; j < 100; ++j)
		{
			auto iter = MonsterList.begin();

			for (int i = 0; i < rand() % MonsterList.size(); ++i)
			{
				++iter;
			}

			CMonster* temp = *MonsterList.begin();

			*MonsterList.begin() = *iter;
			*iter = temp;
		}


		auto iter = MonsterList.begin();
		auto iterEnd = MonsterList.end();

		int SkillCount = 0;

		for (; iter != iterEnd; ++iter)
		{
			Vector2 Pos = (*iter)->GetPos();

			if (Pos.x >= m_Pos.x - 640.f &&
				Pos.x <= m_Pos.x + 640.f &&
				Pos.y >= m_Pos.y - 400.f &&
				Pos.y <= m_Pos.y + 400.f)
			{
				CFallingLightning* FallingLightning = m_Scene->CreateObject<CFallingLightning>("FallingLightning", Pos + Vector2(30, - 2310));
				FallingLightning->SetLightning(this);

				SkillCount++;

				if (SkillCount == (m_LightningCount + m_AdditionalSkillProjectile))
					break;
			}
		}

		m_SkillUseTime -= m_LightningCoolTime;
	}
}

void CLightning::PostUpdate(float DeltaTime)
{
	CSkill::PostUpdate(DeltaTime);
}

void CLightning::Render(HDC hDC, float DeltaTime)
{
	CSkill::Render(hDC, DeltaTime);
}

void CLightning::SkillLevelUp()
{
	CSkill::SkillLevelUp();

	// 번개 갯수는 홀수 레벨에 1개씩 오름. 기본이 2개임.
	m_LightningCount = ((m_SkillLevel + 1) / 2) + 1;
}

