#include "WhipProjectile2.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderBox.h"
#include "Effect.h"
#include "../GameManager.h"
#include "../GameObject/GameObject.h"
#include "Whip.h"

CWhipProjectile2::CWhipProjectile2()
{
	SetTypeID<CWhipProjectile2>();
}

CWhipProjectile2::CWhipProjectile2(const CWhipProjectile2& Obj) :
	CSkill(Obj)
{
}

CWhipProjectile2::~CWhipProjectile2()
{
}

bool CWhipProjectile2::Init()
{
	CSkill::Init();

	m_YOffset = m_Pos.y - (m_Scene->GetPlayer()->GetPos().y-m_Scene->GetCamera()->GetPos().y);

	CreateAnimation();

	AddAnimation("InitWhipLD", false, 0.3f);
	AddAnimation("InitWhipRD", false, 0.3f);

	m_vecSequenceKey[0].push_back("InitWhipLD");
	m_vecSequenceKey[0].push_back("InitWhipRD");

	SetEndFunction<CWhipProjectile2>("InitWhipLD", this, &CWhipProjectile2::InitEnd);
	SetEndFunction<CWhipProjectile2>("InitWhipRD", this, &CWhipProjectile2::InitEnd);

	// 애니메이션 어느쪽인지 정함.
	if (m_Pos.x < m_Scene->GetPlayer()->GetPos().x - m_Scene->GetCamera()->GetPos().x)
	{
		ChangeAnimation(m_vecSequenceKey[0][0]);
		m_WhipDir = 0;
	}

	else
	{
		ChangeAnimation(m_vecSequenceKey[0][1]);
		m_WhipDir = 1;
	}


	if (m_WhipDir == 0)
	{
		m_Pos = m_Scene->GetPlayer()->GetPos() - Vector2(405, 60) - Vector2(0, m_YOffset);

		// 충돌체 추가
		CColliderBox* Box = AddCollider<CColliderBox>("WhipProjectile2");

		Box->SetExtent(300.f, 60.f);
		Box->SetOffset(250.f, 40.f);
		Box->SetCollisionProfile("PlayerAttack");

		Box->SetCollisionBeginFunction<CWhipProjectile2>(this, &CWhipProjectile2::CollisionBegin);
		Box->SetCollisionEndFunction<CWhipProjectile2>(this, &CWhipProjectile2::CollisionEnd);
	}

	else if (m_WhipDir == 1)
	{
		m_Pos = m_Scene->GetPlayer()->GetPos() - Vector2(100, 60) - Vector2(0, m_YOffset);

		// 충돌체 추가
		CColliderBox* Box = AddCollider<CColliderBox>("WhipProjectile2");

		Box->SetExtent(300.f, 60.f);
		Box->SetOffset(250.f, 20.f);
		Box->SetCollisionProfile("PlayerAttack");

		Box->SetCollisionBeginFunction<CWhipProjectile2>(this, &CWhipProjectile2::CollisionBegin);
		Box->SetCollisionEndFunction<CWhipProjectile2>(this, &CWhipProjectile2::CollisionEnd);
	}

	return true;
}

void CWhipProjectile2::Update(float DeltaTime)
{
	CSkill::Update(DeltaTime);

	// 레벨에 맞는 데미지를 설정해야 함. 
	CWhipProjectile2::GetWhipLevel();

	if (m_WhipDir == 0)
	{
		m_Pos = m_Scene->GetPlayer()->GetPos() - Vector2(405, 60) - Vector2(0, m_YOffset);;

	}

	else if (m_WhipDir == 1)
	{
		m_Pos = m_Scene->GetPlayer()->GetPos() - Vector2(100, 60) - Vector2(0, m_YOffset);;

	}
}

void CWhipProjectile2::PostUpdate(float DeltaTime)
{
	CSkill::PostUpdate(DeltaTime);
}

void CWhipProjectile2::Render(HDC hDC, float DeltaTime)
{
	CSkill::Render(hDC, DeltaTime);
}

void CWhipProjectile2::GetWhipLevel()
{
	// 데미지는 1레벨에는 10씩 증가하게 함.	
	m_Damage = 10 + 5.f * m_Whip->GetSkillLevel();
}

void CWhipProjectile2::CollisionBegin(CCollider* Src, CCollider* Dest)
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

void CWhipProjectile2::CollisionEnd(CCollider* Src, CCollider* Dest)
{
}

void CWhipProjectile2::InitEnd()
{
	SetActive(false);
}

