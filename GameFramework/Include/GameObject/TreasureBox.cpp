
#include "TreasureBox.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Collision/ColliderBox.h"
#include "../Widget/ImageWidget.h"
#include "../Widget/Button.h"
#include "../Widget/TreasureBoxWindow.h"

CTreasureBox::CTreasureBox()
{
	SetTypeID<CTreasureBox>();
}

CTreasureBox::CTreasureBox(const CTreasureBox& Obj) :
	CGameObject(Obj)
{
}

CTreasureBox::~CTreasureBox()
{
}

bool CTreasureBox::Init()
{
	CGameObject::Init();

	SetSideWallCheck(true);

	CreateAnimation();

	AddAnimation("FieldTreasureBox");

	ChangeAnimation("FieldTreasureBox");

	// 충돌체 추가
	CColliderBox* Box = AddCollider<CColliderBox>("FieldTreasureBox");

	Box->SetExtent(33.f, 25.f);
	Box->SetOffset(14.f, 15.f);
	Box->SetCollisionProfile("MonsterAttack");	// MonsterAttack은 플레이어와만 충돌한다.

	Box->SetCollisionBeginFunction<CTreasureBox>(this, &CTreasureBox::CollisionBegin);
	Box->SetCollisionEndFunction<CTreasureBox>(this, &CTreasureBox::CollisionEnd);


	return true;
}

void CTreasureBox::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}


void CTreasureBox::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);
}


void CTreasureBox::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	m_Scene->CreateWidgetWindow<CTreasureBoxWindow>("TreasureBoxWindow");
}

void CTreasureBox::CollisionEnd(CCollider* Src, CCollider* Dest)
{
	m_Scene->FindWidget<CTreasureBoxWindow>("TreasureBoxWindow")->SetActive(false);

	SetActive(false);
}
