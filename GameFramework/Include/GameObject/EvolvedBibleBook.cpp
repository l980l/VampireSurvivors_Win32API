#include "EvolvedBibleBook.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderBox.h"
#include "Effect.h"
#include "../GameManager.h"
#include "../GameObject/GameObject.h"
#include "EvolvedBible.h"

CEvolvedBibleBook::CEvolvedBibleBook()
{
	SetTypeID<CEvolvedBibleBook>();
}

CEvolvedBibleBook::CEvolvedBibleBook(const CEvolvedBibleBook& Obj) :
	CSkill(Obj)
{
}

CEvolvedBibleBook::~CEvolvedBibleBook()
{
}

bool CEvolvedBibleBook::Init()
{
	CSkill::Init();

	// 레벨에 맞는 데미지를 설정해야 함. 
	m_Damage = 35;

	// 충돌체 추가
	CColliderBox* Box = AddCollider<CColliderBox>("EvolvedBibleBook");

	Box->SetExtent(30.f, 40.f);
	Box->SetOffset(45.f, 20.f);
	Box->SetCollisionProfile("PlayerAttack");

	Box->SetCollisionBeginFunction<CEvolvedBibleBook>(this, &CEvolvedBibleBook::CollisionBegin);
	Box->SetCollisionEndFunction<CEvolvedBibleBook>(this, &CEvolvedBibleBook::CollisionEnd);

	CreateAnimation();

	AddAnimation("InitEvolvedBible", false, 0.3f);
	AddAnimation("EvolvedBible");
	AddAnimation("DestructEvolvedBible", false, 0.3f);

	m_vecSequenceKey[0].push_back("InitEvolvedBible");
	m_vecSequenceKey[0].push_back("EvolvedBible");
	m_vecSequenceKey[0].push_back("DestructEvolvedBible");

	SetEndFunction<CEvolvedBibleBook>("InitEvolvedBible", this, &CEvolvedBibleBook::InitEnd);
	SetEndFunction<CEvolvedBibleBook>("DestructEvolvedBible", this, &CEvolvedBibleBook::DestructEnd);

	// 생성시 우선 InitBible을 재생함.
	ChangeAnimation(m_vecSequenceKey[0][0]);

	// 초기 위치를 알아내기 위해 플레이어 간의 각도를 구함.
	float Width = m_Scene->GetPlayer()->GetPos().x - m_Scene->GetCamera()->GetPos().x - m_Pos.x;
	float Height = m_Scene->GetPlayer()->GetPos().y - m_Scene->GetCamera()->GetPos().y - m_Pos.y;

	float Hypotenuse = sqrtf(Width * Width + Height * Height);

	m_Angle = Width / Hypotenuse;

	m_Angle = acosf(m_Angle) / PI * 180.f;

	if ((m_Scene->GetPlayer()->GetPos().y - m_Scene->GetCamera()->GetPos().y) < m_Pos.y)
		m_Angle = 360.f - m_Angle;

	

	return true;
}

void CEvolvedBibleBook::Update(float DeltaTime)
{
	CSkill::Update(DeltaTime);

	m_BibleTimePassed += DeltaTime;
	m_PaperTimePassed += DeltaTime;

	Vector2	Target;
	Target.x = m_Scene->GetPlayer()->GetPos().x
		+ cosf(DegreeToRadian((float)m_BibleTimePassed * 180.f * m_AdditionalSkillSpeed + m_Angle)) * m_EvolvedBible->GetBibleRadius();
	Target.y = m_Scene->GetPlayer()->GetPos().y
		+ sinf(DegreeToRadian((float)m_BibleTimePassed * 180.f * m_AdditionalSkillSpeed + m_Angle)) * m_EvolvedBible->GetBibleRadius();

	m_Pos = Target - Vector2(40.f, 15.f);

	if (m_BibleTimePassed >= m_EvolvedBible->GetBibleDuration() * m_AdditionalSkillDuration)
	{
		// DestructBible 애니메이션이 끝나면 알아서 SetActive(false)한다.
		ChangeAnimation(m_vecSequenceKey[0][2]);
	}

	// 종이 날리는 잔상.
	if (m_PaperTimePassed >= 0.2f)
	{
		CEffect* EvolvedBiblePaper = m_Scene->CreateObject<CEffect>("EvolvedBiblePaper");

		EvolvedBiblePaper->SetPivot(-0.2f, 0.5f);
		EvolvedBiblePaper->SetPos(m_Pos);

		EvolvedBiblePaper->AddAnimation("EvolvedBiblePaper", true, 0.3f);

		m_PaperTimePassed -= 0.2f;
	}
	
}

void CEvolvedBibleBook::PostUpdate(float DeltaTime)
{
	CSkill::PostUpdate(DeltaTime);
}

void CEvolvedBibleBook::Render(HDC hDC, float DeltaTime)
{
	CSkill::Render(hDC, DeltaTime);
}

void CEvolvedBibleBook::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	CEffect* Effect1 = m_Scene->CreateObject<CEffect>("Hit1");

	Effect1->SetPivot(0.5f, 0.5f);
	Effect1->SetPos(Src->GetHitPoint());

	Effect1->AddAnimation("Hit1", false, 0.1f);


	CEffect* Effect3 = m_Scene->CreateObject<CEffect>("ShockWave");

	Effect3->SetPivot(0.5f, 0.5f);
	Effect3->SetPos(Src->GetHitPoint());

	Effect3->AddAnimation("ShockWave", false, 0.1f);
	
	//
	Dest->GetOwner()->SetSkillTypeGarlic(false);
	Dest->GetOwner()->InflictDamage(m_Damage * m_AdditionalSkillDamage);
}

void CEvolvedBibleBook::CollisionEnd(CCollider* Src, CCollider* Dest)
{
}

void CEvolvedBibleBook::InitEnd()
{
	ChangeAnimation(m_vecSequenceKey[0][1]);
}

void CEvolvedBibleBook::DestructEnd()
{
	SetActive(false);
}
