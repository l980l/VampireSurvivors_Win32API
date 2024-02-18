
#include "Gem.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Collision/ColliderBox.h"

CGem::CGem()
{
	SetTypeID<CGem>();
}

CGem::CGem(const CGem& Obj) :
	CGameObject(Obj)
{
}

CGem::~CGem()
{
}

bool CGem::Init()
{
	CGameObject::Init();

	SetSideWallCheck(true);

	CreateAnimation();

	AddAnimation("Gem");

	ChangeAnimation("Gem");

	m_ExpHaving = 10;

	// 충돌체 추가
	CColliderBox* Box = AddCollider<CColliderBox>("Gem");

	Box->SetExtent(19.f, 25.f);
	Box->SetOffset(10.f, 15.f);
	Box->SetCollisionProfile("MonsterAttack");	// MonsterAttack은 플레이어와만 충돌한다.

	Box->SetCollisionBeginFunction<CGem>(this, &CGem::CollisionBegin);
	Box->SetCollisionEndFunction<CGem>(this, &CGem::CollisionEnd);


	return true;
}

void CGem::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}


void CGem::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);
}


void CGem::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	m_Scene->GetPlayer()->ExpUp(m_ExpHaving);
	m_Scene->GetSceneResource()->SoundPlay("Gem");
	SetActive(false);
}

void CGem::CollisionEnd(CCollider* Src, CCollider* Dest)
{
}
