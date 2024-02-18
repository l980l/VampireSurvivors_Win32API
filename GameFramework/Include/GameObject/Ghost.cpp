
#include "Ghost.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Collision/ColliderBox.h"
#include "../Collision/ColliderCircle.h"
#include "Effect.h"
#include "Gem.h"
#include "../Widget/WidgetComponent.h"
#include "../Widget/DamageNumber.h"

CGhost::CGhost() :
	m_HP(50),
	m_Damage(5),
	m_MonsterDir(1),
	m_Death(false),
	m_Damaged(false),
	m_PushBackSpeed(1.3f)
{
	SetTypeID<CGhost>();
}

CGhost::CGhost(const CGhost& Obj) :
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

CGhost::~CGhost()
{
}

bool CGhost::Init()
{
	CMonster::Init();

	m_MoveSpeed = 250.f;

	//SetSpawnPosition();

	CreateAnimation();

	AddAnimation("Ghost");
	AddAnimation("GhostDeath", false, 0.3f);
	AddAnimation("DamagedGhost", false, 0.3f);
	AddAnimation("GhostRight");
	AddAnimation("GhostDeathRight", false, 0.3f);
	AddAnimation("DamagedGhostRight", false, 0.3f);

	m_vecSequenceKey[0].push_back("Ghost");
	m_vecSequenceKey[0].push_back("GhostDeath");
	m_vecSequenceKey[0].push_back("DamagedGhost");

	m_vecSequenceKey[1].push_back("GhostRight");
	m_vecSequenceKey[1].push_back("GhostDeathRight");
	m_vecSequenceKey[1].push_back("DamagedGhostRight");


	SetEndFunction<CGhost>("GhostDeath", this, &CGhost::Death);
	SetEndFunction<CGhost>("GhostDeathRight", this, &CGhost::Death);

	SetEndFunction<CGhost>("DamagedGhost", this, &CGhost::Damaged);
	SetEndFunction<CGhost>("DamagedGhostRight", this, &CGhost::Damaged);

	CColliderBox* Box = AddCollider<CColliderBox>("Body");

	Box->SetExtent(55.f, 75.f);
	Box->SetOffset(40.f, 40.f);
	Box->SetCollisionProfile("Monster");

	Box->SetCollisionBeginFunction<CGhost>(this, &CGhost::CollisionBegin);
	Box->SetCollisionEndFunction<CGhost>(this, &CGhost::CollisionEnd);

	return true;
}

void CGhost::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	m_Dir = (m_Scene->GetPlayer()->GetPos()
		- (m_Scene->GetPlayer()->GetPivot() * m_Scene->GetPlayer()->GetSize()) * 0.8f) - m_Pos;

	float TotalMove = abs(m_Dir.x) + abs(m_Dir.y);

	if (m_Dir.x > 0)
		m_MonsterDir = 1;

	else
		m_MonsterDir = 0;

	if (m_Damaged && !m_Garlic)
		MoveDir((m_Dir * -1) * m_PushBackSpeed / TotalMove);

	// Player랑 겹치면 플레이어랑 반대로 가게함.
	else if (m_PlayerOverlap)
		Move((m_Dir * -1) * 2.f / TotalMove);

	else
		MoveDir(m_Dir / TotalMove);
}

void CGhost::PostUpdate(float DeltaTime)
{
	CCharacter::PostUpdate(DeltaTime);

	if (!m_Death && !m_Damaged)
		ChangeAnimation(m_vecSequenceKey[m_MonsterDir][0]);
}

void CGhost::Render(HDC hDC, float DeltaTime)
{
	CCharacter::Render(hDC, DeltaTime);
}

float CGhost::InflictDamage(float Damage)
{
	Damage = CCharacter::InflictDamage(Damage);

	if (m_Death)
		return Damage;

	// 데미지 출력
	CSharedPtr<CWidgetComponent> DamageNumber1 = CreateWidgetComponent<CDamageNumber>("DamageNumber1");
	CSharedPtr<CWidgetComponent> DamageNumber2 = CreateWidgetComponent<CDamageNumber>("DamageNumber2");

	std::vector<std::wstring>	vecFileName;

	if (Damage < 30)
	{
		for (int i = 0; i <= 9; ++i)
		{
			TCHAR	FileName[MAX_PATH] = {};
			// %d에 i의 값이 대입되어 문자열이 만들어지게 된다.
			wsprintf(FileName, TEXT("Texture/Number/White/%d.bmp"), i);
			vecFileName.push_back(FileName);
		}

		DamageNumber1->GetWidget<CDamageNumber>()->SetTexture("NumberWhite", vecFileName);
		DamageNumber2->GetWidget<CDamageNumber>()->SetTexture("NumberWhite", vecFileName);
	}

	else if (Damage >= 30)
	{
		for (int i = 0; i <= 9; ++i)
		{
			TCHAR	FileName[MAX_PATH] = {};
			// %d에 i의 값이 대입되어 문자열이 만들어지게 된다.
			wsprintf(FileName, TEXT("Texture/Number/Red/%d.bmp"), i);
			vecFileName.push_back(FileName);
		}

		DamageNumber1->GetWidget<CDamageNumber>()->SetTexture("NumberRed", vecFileName);
		DamageNumber2->GetWidget<CDamageNumber>()->SetTexture("NumberRed", vecFileName);
	}



	DamageNumber1->GetWidget<CDamageNumber>()->SetColorKey(255, 0, 255);
	DamageNumber2->GetWidget<CDamageNumber>()->SetColorKey(255, 0, 255);

	DamageNumber1->GetWidget<CDamageNumber>()->SetSize(15.f, 24.f);
	DamageNumber1->SetPos(10.f, -10.f);
	DamageNumber2->GetWidget<CDamageNumber>()->SetSize(15.f, 24.f);
	DamageNumber2->SetPos(26.f, -10.f);

	DamageNumber1->GetWidget<CDamageNumber>()->SetNumber((int)Damage / 10);
	DamageNumber2->GetWidget<CDamageNumber>()->SetNumber((int)Damage % 10);

	DamageNumber1->SetWidgetComponentTimer(0.2f);
	DamageNumber2->SetWidgetComponentTimer(0.2f);


	m_Scene->GetSceneResource()->SoundPlay("MonsterHit");

	m_HP -= (int)Damage;

	if (!m_Damaged)
		ChangeAnimation(m_vecSequenceKey[m_MonsterDir][2]);

	m_Damaged = true;

	if (m_HP <= 0)
	{
		ChangeAnimation(m_vecSequenceKey[m_MonsterDir][1]);
		m_Scene->CreateObject<CGem>("Gem", m_Pos);

		m_Scene->GetPlayer()->KillCountUp();

		m_Damaged = false;

		m_Death = true;

		auto iter = m_ColliderList.begin();
		auto iterEnd = m_ColliderList.end();

		for (; iter != iterEnd; ++iter)
		{
			(*iter)->SetCollisionProfile("DeadMonster");
		}
	}

	return Damage;
}

void CGhost::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	if (Dest->GetProfile()->Channel == ECollision_Channel::Player)
	{
		Dest->GetOwner()->InflictDamage(m_Damage);

		m_PlayerOverlap = true;
	}

}

void CGhost::CollisionEnd(CCollider* Src, CCollider* Dest)
{
	if (Dest->GetProfile()->Channel == ECollision_Channel::Player)
		m_PlayerOverlap = false;
}

void CGhost::CollisionMouseBegin(CCollider* Src, const Vector2& MousePos)
{
}

void CGhost::CollisionMouseEnd(CCollider* Src, const Vector2& MousePos)
{
}

void CGhost::Death()
{
	SetActive(false);
}

void CGhost::Damaged()
{
	m_Damaged = false;
}