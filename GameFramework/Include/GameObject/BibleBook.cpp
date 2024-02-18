#include "BibleBook.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderBox.h"
#include "Effect.h"
#include "../GameManager.h"
#include "../GameObject/GameObject.h"
#include "Bible.h"

CBibleBook::CBibleBook()
{
	SetTypeID<CBibleBook>();
}

CBibleBook::CBibleBook(const CBibleBook& Obj) :
	CSkill(Obj)
{
}

CBibleBook::~CBibleBook()
{
}

bool CBibleBook::Init()
{
	CSkill::Init();
	
	// 충돌체 추가
	CColliderBox* Box = AddCollider<CColliderBox>("BibleBook");

	Box->SetExtent(30.f, 40.f);
	Box->SetOffset(45.f, 20.f);
	Box->SetCollisionProfile("PlayerAttack");

	Box->SetCollisionBeginFunction<CBibleBook>(this, &CBibleBook::CollisionBegin);
	Box->SetCollisionEndFunction<CBibleBook>(this, &CBibleBook::CollisionEnd);

	CreateAnimation();

	AddAnimation("InitBible", false, 0.3f);
	AddAnimation("Bible");
	AddAnimation("DestructBible", false, 0.3f);

	m_vecSequenceKey[0].push_back("InitBible");
	m_vecSequenceKey[0].push_back("Bible");
	m_vecSequenceKey[0].push_back("DestructBible");

	SetEndFunction<CBibleBook>("InitBible", this, &CBibleBook::InitEnd);
	SetEndFunction<CBibleBook>("DestructBible", this, &CBibleBook::DestructEnd);

	// 생성시 우선 InitBible을 재생함.
	ChangeAnimation(m_vecSequenceKey[0][0]);

	// 초기 위치를 알아내기 위해 플레이어 간의 각도를 구함.
	float Width = m_Scene->GetPlayer()->GetPos().x - m_Scene->GetCamera()->GetPos().x - m_Pos.x;
	float Height = m_Scene->GetPlayer()->GetPos().y - m_Scene->GetCamera()->GetPos().y - m_Pos.y;

	float Hypotenuse = sqrtf(Width * Width + Height * Height);

	m_Angle = Width / Hypotenuse;

	m_Angle = acosf(m_Angle) / PI * 180.f;

	if ((m_Scene->GetPlayer()->GetPos().y - m_Scene->GetCamera()->GetPos().y)  < m_Pos.y)
		m_Angle = 360.f - m_Angle;


	return true;
}

void CBibleBook::Update(float DeltaTime)
{
	// 레벨에 맞는 데미지를 설정해야 함. 
	CBibleBook::GetBibleLevel();
	
	CSkill::Update(DeltaTime);

	m_BibleTimePassed += DeltaTime;
	m_PaperTimePassed += DeltaTime;

	Vector2	Target;
	Target.x = m_Scene->GetPlayer()->GetPos().x 
		+ cosf(DegreeToRadian((float)m_BibleTimePassed* 180.f * m_AdditionalSkillSpeed + m_Angle)) * m_Bible->GetBibleRadius();
	Target.y = m_Scene->GetPlayer()->GetPos().y 
		+ sinf(DegreeToRadian((float)m_BibleTimePassed* 180.f * m_AdditionalSkillSpeed + m_Angle)) * m_Bible->GetBibleRadius();

	m_Pos = Target - Vector2(40.f,15.f);

	if (m_BibleTimePassed >= m_Bible->GetBibleDuration() * m_AdditionalSkillDuration)
	{
		// DestructBible 애니메이션이 끝나면 알아서 SetActive(false)한다.
		ChangeAnimation(m_vecSequenceKey[0][2]);
	}

	// 종이 날리는 잔상.
	if (m_PaperTimePassed >= 0.2f)
	{
		CEffect* EvolvedBiblePaper = m_Scene->CreateObject<CEffect>("BiblePaper");

		EvolvedBiblePaper->SetPivot(-0.2f, 0.5f);
		EvolvedBiblePaper->SetPos(m_Pos);

		EvolvedBiblePaper->AddAnimation("BiblePaper", true, 0.3f);

		m_PaperTimePassed -= 0.2f;
	}
}

void CBibleBook::PostUpdate(float DeltaTime)
{
	CSkill::PostUpdate(DeltaTime);
}

void CBibleBook::Render(HDC hDC, float DeltaTime)
{
	CSkill::Render(hDC, DeltaTime);
}

void CBibleBook::GetBibleLevel()
{
	// 데미지는 1레벨에는 10, 그 이후 짝수 레벨마다 5씩 증가한다.
	m_Damage = 10 + 5.f * (m_Bible->GetSkillLevel() / 2) ;
}

void CBibleBook::CollisionBegin(CCollider* Src, CCollider* Dest)
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

void CBibleBook::CollisionEnd(CCollider* Src, CCollider* Dest)
{
}

void CBibleBook::InitEnd()
{
	ChangeAnimation(m_vecSequenceKey[0][1]);
}

void CBibleBook::DestructEnd()
{
	SetActive(false);
}
