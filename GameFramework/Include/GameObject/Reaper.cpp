
#include "Reaper.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Collision/ColliderBox.h"
#include "../Collision/ColliderCircle.h"
#include "Effect.h"

CReaper::CReaper() :
	m_HP(100),
	m_Damage(50),
	m_MonsterDir(1),
	m_Death(false),
	m_Damaged(false),
	m_PushBackSpeed(0.f)
{
	SetTypeID<CReaper>();
}

CReaper::CReaper(const CReaper& Obj) :
	CMonster(Obj),
	m_Dir(Obj.m_Dir),
	m_HP(Obj.m_HP),
	m_Damage(Obj.m_Damage),
	m_MonsterDir(Obj.m_MonsterDir),
	m_Death(Obj.m_Death),
	m_Damaged(Obj.m_Damaged),
	m_PushBackSpeed(Obj.m_PushBackSpeed)
{
}

CReaper::~CReaper()
{
}

bool CReaper::Init()
{
	CMonster::Init();

	// 리퍼는 벽을 뚫어~
	SetSideWallCheck(false);

	m_MoveSpeed = 1000.f;

	CreateAnimation();

	AddAnimation("Reaper");
	AddAnimation("ReaperRight");

	m_vecSequenceKey[0].push_back("Reaper");

	m_vecSequenceKey[1].push_back("ReaperRight");

	CColliderBox* Box = AddCollider<CColliderBox>("Body");

	/*Box->SetExtent(115.f, 110.f);
	Box->SetOffset(90.f, 65.f);*/

	Box->SetExtent(70.f, 80.f);
	Box->SetOffset(88.f, 72.5f);
	Box->SetCollisionProfile("Monster");

	Box->SetCollisionBeginFunction<CReaper>(this, &CReaper::CollisionBegin);
	Box->SetCollisionEndFunction<CReaper>(this, &CReaper::CollisionEnd);

	return true;
}

void CReaper::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	m_Dir = (m_Scene->GetPlayer()->GetPos()
		- (m_Scene->GetPlayer()->GetPivot() * m_Scene->GetPlayer()->GetSize()) * 1.5f) 
		- m_Pos - Vector2(10,0);

	float TotalMove = abs(m_Dir.x) + abs(m_Dir.y);

	if (m_Dir.x > 0)
		m_MonsterDir = 1;

	else
		m_MonsterDir = 0;

	// Player랑 겹치면 플레이어랑 반대로 가게함.
	if (m_PlayerOverlap)
	{
		Move((m_Dir * -1) * 1.5f / TotalMove);

		m_Scene->GetPlayer()->InflictDamage(m_Damage);
	}

	else
		MoveDir(m_Dir / TotalMove);

}

void CReaper::PostUpdate(float DeltaTime)
{
	CCharacter::PostUpdate(DeltaTime);

	ChangeAnimation(m_vecSequenceKey[m_MonsterDir][0]);
}

void CReaper::Render(HDC hDC, float DeltaTime)
{
	CCharacter::Render(hDC, DeltaTime);
}

float CReaper::InflictDamage(float Damage)
{
	Damage = CCharacter::InflictDamage(Damage);

	return Damage;
}

void CReaper::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	if (Dest->GetProfile()->Channel == ECollision_Channel::Player)
	{
		Dest->GetOwner()->InflictDamage(m_Damage);

		m_PlayerOverlap = true;
	}
}

void CReaper::CollisionEnd(CCollider* Src, CCollider* Dest)
{
	if (Dest->GetProfile()->Channel == ECollision_Channel::Player)
		m_PlayerOverlap = false;
}

void CReaper::CollisionMouseBegin(CCollider* Src, const Vector2& MousePos)
{
}

void CReaper::CollisionMouseEnd(CCollider* Src, const Vector2& MousePos)
{
}

void CReaper::Damaged()
{
}

