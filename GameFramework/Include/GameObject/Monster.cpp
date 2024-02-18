
#include "Monster.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Collision/ColliderBox.h"
#include "../Collision/ColliderCircle.h"
#include "../Widget/WidgetComponent.h"
#include "../Widget/DamageNumber.h"
#include "Effect.h"

CMonster::CMonster() :
	m_HP(100),
	m_Damage(20),
	m_MonsterDir(1),
	m_Death(false),
	m_PlayerOverlap(false)
{
	SetTypeID<CMonster>();
}

CMonster::CMonster(const CMonster& Obj) :
	CCharacter(Obj),
	m_Dir(Obj.m_Dir)
{
}

CMonster::~CMonster()
{
}

bool CMonster::Init()
{
	CGameObject::Init();

	SetSideWallCheck(true);

	return true;
}

void CMonster::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CMonster::PostUpdate(float DeltaTime)
{
	CCharacter::PostUpdate(DeltaTime);
}

void CMonster::Render(HDC hDC, float DeltaTime)
{
	CCharacter::Render(hDC, DeltaTime);
}

float CMonster::InflictDamage(float Damage)
{
	return Damage;
}

void CMonster::CollisionBegin(CCollider* Src, CCollider* Dest)
{
}

void CMonster::CollisionEnd(CCollider* Src, CCollider* Dest)
{
}

void CMonster::CollisionMouseBegin(CCollider* Src, const Vector2& MousePos)
{
}

void CMonster::CollisionMouseEnd(CCollider* Src, const Vector2& MousePos)
{
}

void CMonster::Death()
{
}

void CMonster::Damaged()
{
}