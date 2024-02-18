#include "WhipProjectile.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderBox.h"
#include "Effect.h"
#include "../GameManager.h"
#include "../GameObject/GameObject.h"
#include "Whip.h"

CWhipProjectile::CWhipProjectile()
{
	SetTypeID<CWhipProjectile>();
}

CWhipProjectile::CWhipProjectile(const CWhipProjectile& Obj) :
	CSkill(Obj)
{
}

CWhipProjectile::~CWhipProjectile()
{
}

bool CWhipProjectile::Init()
{
	CSkill::Init();

	m_YOffset = m_Pos.y - (m_Scene->GetPlayer()->GetPos().y - m_Scene->GetCamera()->GetPos().y);

	CreateAnimation();
	
	AddAnimation("InitWhipLU", false, 0.3f);	
	AddAnimation("InitWhipRU", false, 0.3f);	

	m_vecSequenceKey[0].push_back("InitWhipLU");
	m_vecSequenceKey[0].push_back("InitWhipRU");

	SetEndFunction<CWhipProjectile>("InitWhipLU", this, &CWhipProjectile::InitEnd);
	SetEndFunction<CWhipProjectile>("InitWhipRU", this, &CWhipProjectile::InitEnd);

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
		CColliderBox* Box = AddCollider<CColliderBox>("WhipProjectile");

		Box->SetExtent(300.f, 60.f);
		Box->SetOffset(250.f, 20.f);
		Box->SetCollisionProfile("PlayerAttack");

		Box->SetCollisionBeginFunction<CWhipProjectile>(this, &CWhipProjectile::CollisionBegin);
		Box->SetCollisionEndFunction<CWhipProjectile>(this, &CWhipProjectile::CollisionEnd);
	}

	else if (m_WhipDir == 1)
	{
		m_Pos = m_Scene->GetPlayer()->GetPos() - Vector2(100, 60) - Vector2(0, m_YOffset);

		// 충돌체 추가
		CColliderBox* Box = AddCollider<CColliderBox>("WhipProjectile");

		Box->SetExtent(300.f, 60.f);
		Box->SetOffset(250.f, 20.f);
		Box->SetCollisionProfile("PlayerAttack");

		Box->SetCollisionBeginFunction<CWhipProjectile>(this, &CWhipProjectile::CollisionBegin);
		Box->SetCollisionEndFunction<CWhipProjectile>(this, &CWhipProjectile::CollisionEnd);
	}
	
	return true;
}

void CWhipProjectile::Update(float DeltaTime)
{
	CSkill::Update(DeltaTime);

	// 레벨에 맞는 데미지를 설정해야 함. 
	CWhipProjectile::GetWhipLevel();

	if (m_WhipDir == 0)
	{
		m_Pos = m_Scene->GetPlayer()->GetPos() - Vector2(405, 60) - Vector2(0, m_YOffset);

	}

	else if (m_WhipDir == 1)
	{
		m_Pos = m_Scene->GetPlayer()->GetPos() - Vector2(100, 60) - Vector2(0, m_YOffset);

	}
}

void CWhipProjectile::PostUpdate(float DeltaTime)
{
	CSkill::PostUpdate(DeltaTime);
}

void CWhipProjectile::Render(HDC hDC, float DeltaTime)
{
	CSkill::Render(hDC, DeltaTime);
}

void CWhipProjectile::GetWhipLevel()
{
	// 데미지는 1레벨에는 10이고, 씩 증가하게 함.	
	m_Damage = 10 + 4.f * (m_Whip->GetSkillLevel() - 1);
}

void CWhipProjectile::CollisionBegin(CCollider* Src, CCollider* Dest)
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

void CWhipProjectile::CollisionEnd(CCollider* Src, CCollider* Dest)
{
}

void CWhipProjectile::InitEnd()
{
	SetActive(false);
}

