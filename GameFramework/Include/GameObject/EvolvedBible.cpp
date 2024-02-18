
#include "EvolvedBible.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../GameManager.h"
#include "../GameObject/GameObject.h"
#include "EvolvedBibleBook.h"

CEvolvedBible::CEvolvedBible()
{
	SetTypeID<CEvolvedBible>();
}

CEvolvedBible::CEvolvedBible(const CEvolvedBible& Obj) :
	CSkill(Obj)
{
}

CEvolvedBible::~CEvolvedBible()
{
}

bool CEvolvedBible::Init()
{
	CSkill::Init();

	m_EvolvedBibleCount = 4 + m_AdditionalSkillProjectile;

	m_Radius = 250.f;
	m_EvolvedBibleDuration = 3.f;	// 지속시간
	m_EvolvedBibleCoolTime = 3.f;	// 쿨타임
	m_SkillUseTime = m_EvolvedBibleDuration + m_EvolvedBibleCoolTime;

	return true;
}

void CEvolvedBible::Update(float DeltaTime)
{
	CSkill::Update(DeltaTime);

	m_Pos = m_Scene->GetPlayer()->GetPos();

	Vector2	Pos = m_Pos - m_Scene->GetCamera()->GetPos();

	m_SkillUseTime += DeltaTime;


	if (m_SkillUseTime >=m_EvolvedBibleDuration)
	{
		for (int i = 0; i < m_EvolvedBibleCount + m_AdditionalSkillProjectile; ++i)
		{
			Vector2	Target;
			Target.x = Pos.x + cosf(DegreeToRadian((float)(360.f / (m_EvolvedBibleCount + m_AdditionalSkillProjectile)) * i)) * m_Radius;
			Target.y = Pos.y + sinf(DegreeToRadian((float)(360.f / (m_EvolvedBibleCount + m_AdditionalSkillProjectile)) * i)) * m_Radius;

			CEvolvedBibleBook* EvolvedBibleBook = m_Scene->CreateObject<CEvolvedBibleBook>("EvolvedBibleBook", Target);
			EvolvedBibleBook->SetEvolvedBible(this);
		}

		m_SkillUseTime -= m_EvolvedBibleCoolTime;
	}
}

void CEvolvedBible::PostUpdate(float DeltaTime)
{
	CSkill::PostUpdate(DeltaTime);
}

void CEvolvedBible::Render(HDC hDC, float DeltaTime)
{
	CSkill::Render(hDC, DeltaTime);
}

