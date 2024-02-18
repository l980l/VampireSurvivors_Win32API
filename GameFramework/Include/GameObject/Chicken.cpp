
#include "Chicken.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Collision/ColliderBox.h"

CChicken::CChicken()
{
	SetTypeID<CChicken>();
}

CChicken::CChicken(const CChicken& Obj) :
	CGameObject(Obj)
{
}

CChicken::~CChicken()
{
}

bool CChicken::Init()
{
	CGameObject::Init();

	SetSideWallCheck(true);

	CreateAnimation();

	AddAnimation("Chicken");

	ChangeAnimation("Chicken");

	m_HPHaving = 60;

	// 충돌체 추가
	CColliderBox* Box = AddCollider<CColliderBox>("Chicken");

	Box->SetExtent(33.f, 35.f);
	Box->SetOffset(14.f, 17.f);
	Box->SetCollisionProfile("MonsterAttack");	// MonsterAttack은 플레이어와만 충돌한다.

	Box->SetCollisionBeginFunction<CChicken>(this, &CChicken::CollisionBegin);
	Box->SetCollisionEndFunction<CChicken>(this, &CChicken::CollisionEnd);


	return true;
}

void CChicken::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}


void CChicken::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);
}


void CChicken::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	m_Scene->GetPlayer()->HPUP(m_HPHaving);
	m_Scene->GetSceneResource()->SoundPlay("HPUP");
	SetActive(false);
}

void CChicken::CollisionEnd(CCollider* Src, CCollider* Dest)
{
}
