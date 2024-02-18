
#include "FirePot.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Collision/ColliderBox.h"
#include "Chicken.h"

CFirePot::CFirePot()
{
	SetTypeID<CFirePot>();
}

CFirePot::CFirePot(const CFirePot& Obj) :
	CGameObject(Obj)
{
}

CFirePot::~CFirePot()
{
}

bool CFirePot::Init()
{
	CGameObject::Init();

	SetSideWallCheck(true);

	CreateAnimation();

	AddAnimation("FirePot", true, 0.3f);

	ChangeAnimation("FirePot");

	// 충돌체 추가
	CColliderBox* Box = AddCollider<CColliderBox>("FirePot");

	Box->SetExtent(41.f, 60.f);
	Box->SetOffset(20.f, 35.f);
	Box->SetCollisionProfile("Monster");	

	Box->SetCollisionBeginFunction<CFirePot>(this, &CFirePot::CollisionBegin);
	Box->SetCollisionEndFunction<CFirePot>(this, &CFirePot::CollisionEnd);


	return true;
}

void CFirePot::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}


void CFirePot::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);
}


void CFirePot::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	if (Dest->GetProfile()->Channel == ECollision_Channel::PlayerAttack)
	{
		srand((unsigned int)time(0));

		int Random = rand();

		Random = rand() % 10;

		if (Random < 5)
		{
			m_Scene->CreateObject<CChicken>("Chicken", m_Pos);
		}

		SetActive(false);
	}
}

void CFirePot::CollisionEnd(CCollider* Src, CCollider* Dest)
{
}
