
#include "Bible.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../GameManager.h"
#include "../GameObject/GameObject.h"
#include "BibleBook.h"

CBible::CBible()
{
	SetTypeID<CBible>();
}

CBible::CBible(const CBible& Obj) :
	CSkill(Obj)
{
}

CBible::~CBible()
{
}

bool CBible::Init()
{
	CSkill::Init();

	m_BibleCount = 1 + m_AdditionalSkillProjectile;

	m_Radius = 70.f;
	m_BibleDuration = 3.f;	// 지속시간
	m_BibleCoolTime = 3.f;	// 쿨타임
	m_SkillUseTime = m_BibleCoolTime + m_BibleDuration + m_AdditionalSkillDuration + 0.3f;

	return true;
}

void CBible::Update(float DeltaTime)
{
	CSkill::Update(DeltaTime);
	
	m_Pos = m_Scene->GetPlayer()->GetPos();

	Vector2	Pos = m_Pos - m_Scene->GetCamera()->GetPos();

	m_SkillUseTime += DeltaTime;

	// 스킬 쿨타임은 스킬 지속시간이 전부 끝나고 돈다. 따라서 그냥 쿨타임과 지속시간을 
	// 더해서 처리했다.
	if (m_SkillUseTime >= m_BibleCoolTime + m_BibleDuration + m_AdditionalSkillDuration + 0.3)
	{
		for (int i = 0; i < m_BibleCount + m_AdditionalSkillProjectile; ++i)
		{
			Vector2	Target;
			Target.x = Pos.x + cosf(DegreeToRadian((float)(360.f /( m_BibleCount + m_AdditionalSkillProjectile)) * i)) * m_Radius;
			Target.y = Pos.y + sinf(DegreeToRadian((float)(360.f / (m_BibleCount + m_AdditionalSkillProjectile)) * i)) * m_Radius;

			CBibleBook* BibleBook = m_Scene->CreateObject<CBibleBook>("BibleBook", Target);
			BibleBook->SetBible(this);
		}

		m_SkillUseTime -= m_BibleCoolTime + m_BibleDuration + m_AdditionalSkillDuration + 0.3f;
	}
}

void CBible::PostUpdate(float DeltaTime)
{
	CSkill::PostUpdate(DeltaTime);
}

void CBible::Render(HDC hDC, float DeltaTime)
{
	CSkill::Render(hDC, DeltaTime);
}

void CBible::SkillLevelUp()
{
	CSkill::SkillLevelUp();
	
	// 반지름이랑 데미지 설정. 짝수 레벨에 1번씩 오름
	m_Radius = 70 + 30.f * (m_SkillLevel / 2);

	// 바이블 갯수는 홀수 레벨에 1개씩 오름
	m_BibleCount = ((m_SkillLevel + 1) / 2);

	// 지속시간도 짝수 레벨마다 올려줘야함.
	m_BibleDuration = 3.f + m_SkillLevel * 0.2f;
}
