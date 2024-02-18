
#include "Flower2.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Collision/ColliderBox.h"
#include "../Collision/ColliderCircle.h"
#include "Effect.h"
#include "Gem.h"
#include "../Widget/WidgetComponent.h"
#include "../Widget/DamageNumber.h"

CFlower2::CFlower2() :
	m_HP(400),
	m_Damage(7),
	m_MonsterDir(1),
	m_Death(false),
	m_Damaged(false),
	m_PushBackSpeed(0.1f)

{
	SetTypeID<CFlower2>();
}

CFlower2::CFlower2(const CFlower2& Obj) :
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

CFlower2::~CFlower2()
{
}

bool CFlower2::Init()
{
	CMonster::Init();

	m_MoveSpeed = 10.f;

	//SetSpawnPosition();

	CreateAnimation();

	AddAnimation("Flower2");
	AddAnimation("Flower2Death", false, 0.3f);
	AddAnimation("DamagedFlower2", false, 0.3f);
	AddAnimation("Flower2Right");
	AddAnimation("Flower2DeathRight", false, 0.3f);
	AddAnimation("DamagedFlower2Right", false, 0.3f);

	m_vecSequenceKey[0].push_back("Flower2");
	m_vecSequenceKey[0].push_back("Flower2Death");
	m_vecSequenceKey[0].push_back("DamagedFlower2");

	m_vecSequenceKey[1].push_back("Flower2Right");
	m_vecSequenceKey[1].push_back("Flower2DeathRight");
	m_vecSequenceKey[1].push_back("DamagedFlower2Right");


	SetEndFunction<CFlower2>("Flower2Death", this, &CFlower2::Death);
	SetEndFunction<CFlower2>("Flower2DeathRight", this, &CFlower2::Death);

	SetEndFunction<CFlower2>("DamagedFlower2", this, &CFlower2::Damaged);
	SetEndFunction<CFlower2>("DamagedFlower2Right", this, &CFlower2::Damaged);

	CColliderBox* Box = AddCollider<CColliderBox>("Body");

	Box->SetExtent(60.f, 60.f);
	Box->SetOffset(45.f, 30.f);
	Box->SetCollisionProfile("Monster");

	Box->SetCollisionBeginFunction<CFlower2>(this, &CFlower2::CollisionBegin);
	Box->SetCollisionEndFunction<CFlower2>(this, &CFlower2::CollisionEnd);

	return true;
}

void CFlower2::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	m_Dir = (m_Scene->GetPlayer()->GetPos()
		- (m_Scene->GetPlayer()->GetPivot() * m_Scene->GetPlayer()->GetSize()) * 0.7f) - m_Pos;

	float TotalMove = abs(m_Dir.x) + abs(m_Dir.y);

	if (m_Dir.x > 0)
		m_MonsterDir = 1;

	else
		m_MonsterDir = 0;

	if (m_Damaged && !m_Garlic)
		MoveDir((m_Dir * -1) * m_PushBackSpeed / TotalMove);

	else
		MoveDir(m_Dir / TotalMove);
}

void CFlower2::PostUpdate(float DeltaTime)
{
	CCharacter::PostUpdate(DeltaTime);

	if (!m_Death && !m_Damaged)
		ChangeAnimation(m_vecSequenceKey[m_MonsterDir][0]);
}

void CFlower2::Render(HDC hDC, float DeltaTime)
{
	CCharacter::Render(hDC, DeltaTime);
}

float CFlower2::InflictDamage(float Damage)
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
	DamageNumber1->SetPos(30.f, -5.f);
	DamageNumber2->GetWidget<CDamageNumber>()->SetSize(15.f, 24.f);
	DamageNumber2->SetPos(46.f, -5.f);

	DamageNumber1->GetWidget<CDamageNumber>()->SetNumber((int)Damage / 10);
	DamageNumber2->GetWidget<CDamageNumber>()->SetNumber((int)Damage % 10);

	DamageNumber1->SetWidgetComponentTimer(0.2f);
	DamageNumber2->SetWidgetComponentTimer(0.2f);

	if (Damage != INT_MAX)
		m_Scene->GetSceneResource()->SoundPlay("MonsterHit");

	m_HP -= (int)Damage;

	if (!m_Damaged)
		ChangeAnimation(m_vecSequenceKey[m_MonsterDir][2]);

	m_Damaged = true;

	if (m_HP <= 0)
	{
		ChangeAnimation(m_vecSequenceKey[m_MonsterDir][1]);
		//m_Scene->CreateObject<CGem>("Gem", m_Pos);

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

void CFlower2::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	if (Dest->GetProfile()->Channel == ECollision_Channel::Player)
	{
		Dest->GetOwner()->InflictDamage(m_Damage);
	}
}

void CFlower2::CollisionEnd(CCollider* Src, CCollider* Dest)
{
}

void CFlower2::CollisionMouseBegin(CCollider* Src, const Vector2& MousePos)
{
}

void CFlower2::CollisionMouseEnd(CCollider* Src, const Vector2& MousePos)
{
}

void CFlower2::Death()
{
	SetActive(false);

}

void CFlower2::Damaged()
{
	m_Damaged = false;
}
