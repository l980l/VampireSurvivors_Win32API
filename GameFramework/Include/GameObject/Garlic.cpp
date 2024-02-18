
#include "Garlic.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderCircle.h"
#include "Effect.h"
#include "../GameManager.h"
#include "../GameObject/GameObject.h"

CGarlic::CGarlic() :
	m_Radius(70.f)
{
	SetTypeID<CGarlic>();
}

CGarlic::CGarlic(const CGarlic& Obj) :
	CSkill(Obj)
{
}

CGarlic::~CGarlic()
{
}

bool CGarlic::Init()
{
	CSkill::Init();
	
	// 갈릭을 플레이어 뒤로 보내기 위해 Size를 음수로 줬음.
	SetSize(-30,-30);

	m_Damage = 10.f;

	// 레벨, 아이템에 따라 크기가 변하는 큰 원
	CColliderCircle* Circle1 = AddCollider<CColliderCircle>("Circle");

	Circle1->SetRadius(m_Radius + 10);
	Circle1->SetCollisionProfile("PlayerAttack");

	Circle1->SetCollisionBeginFunction<CGarlic>(this, &CGarlic::CollisionBegin);
	Circle1->SetCollisionEndFunction<CGarlic>(this, &CGarlic::CollisionEnd);

	return true;
}

void CGarlic::Update(float DeltaTime)
{
	CSkill::Update(DeltaTime);

	m_DamageTime += DeltaTime;

	auto iter = m_ColliderOwnerList.begin();
	auto iterEnd = m_ColliderOwnerList.end();

	for (; iter != iterEnd; )
	{
		if (!(*iter)->GetActive())
		{
			iter = m_ColliderOwnerList.erase(iter);
			iterEnd = m_ColliderOwnerList.end();
		}

		else
			++iter;
	}


	if (m_DamageTime >= 0.3f)
	{
		auto iter1 = m_ColliderOwnerList.begin();
		auto iter1End = m_ColliderOwnerList.end();

		for (; iter1 != iter1End; ++iter1)
		{
			//
			(*iter1)->SetSkillTypeGarlic(true);
			(*iter1)->InflictDamage(m_Damage * m_AdditionalSkillDamage);
		}

		m_DamageTime -= 0.3f;
	}
}

void CGarlic::PostUpdate(float DeltaTime)
{
	CSkill::PostUpdate(DeltaTime);

	m_Pos = m_Scene->GetPlayer()->GetPos();
}

void CGarlic::Render(HDC hDC, float DeltaTime)
{
	CSkill::Render(hDC, DeltaTime);

	HPEN	Pen = CGameManager::GetInst()->GetPen(EBrush_Type::Khaki);

	HPEN	PrevPen = (HPEN)SelectObject(hDC, Pen);

	CCamera* Camera = m_Scene->GetCamera();

	Vector2	Pos = m_Pos - Camera->GetPos();

	for (int j = 0; j < 3; ++j)
	{
		MoveToEx(hDC, (long)(Pos.x + m_Radius * (1 - j * 0.3)), (long)Pos.y, nullptr);

		for (int i = 12; i <= 360; i += 12)
		{
			Vector2	Target;
			Target.x = Pos.x + cosf(DegreeToRadian((float)i)) * m_Radius *(1-j*0.3f);
			Target.y = Pos.y + sinf(DegreeToRadian((float)i)) * m_Radius *(1-j*0.3f);

			LineTo(hDC, (long)Target.x, (long)Target.y);
		}
	}
		
	SelectObject(hDC, PrevPen);

}

void CGarlic::SkillLevelUp()
{
	CSkill::SkillLevelUp();

	// 반지름이랑 데미지 설정.
	m_Radius = 70 + 15.f * (m_SkillLevel - 1);
	m_Damage = 10 + 1.f * (m_SkillLevel - 1);

	auto	iter = m_ColliderList.begin();
	auto	iterEnd = m_ColliderList.end();

	for (; iter != iterEnd;)
	{
		(*iter)->ClearCollisionList();
		iter = m_ColliderList.erase(iter);
		iterEnd = m_ColliderList.end();
	}

	// 레벨, 아이템에 따라 크기가 변하는 큰 원
	CColliderCircle* Circle1 = AddCollider<CColliderCircle>("Circle");

	Circle1->SetRadius(m_Radius + 10);
	Circle1->SetCollisionProfile("PlayerAttack");

	Circle1->SetCollisionBeginFunction<CGarlic>(this, &CGarlic::CollisionBegin);
	Circle1->SetCollisionEndFunction<CGarlic>(this, &CGarlic::CollisionEnd);

}



void CGarlic::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	m_ColliderOwnerList.push_back(Dest->GetOwner());

	CEffect* Effect1 = m_Scene->CreateObject<CEffect>("Hit1");

	Effect1->SetPivot(0.5f, 0.5f);
	Effect1->SetPos(Src->GetHitPoint());

	Effect1->AddAnimation("Hit1", false, 0.1f);

	/*CEffect* Effect2 = m_Scene->CreateObject<CEffect>("Slash");

	Effect2->SetPivot(0.5f, 0.5f);
	Effect2->SetPos(Src->GetHitPoint());

	Effect2->AddAnimation("Slash", false, 0.3f);*/

	CEffect* Effect3 = m_Scene->CreateObject<CEffect>("ShockWave");

	Effect3->SetPivot(0.5f, 0.5f);
	Effect3->SetPos(Src->GetHitPoint());

	Effect3->AddAnimation("ShockWave", false, 0.1f);

	//
	Dest->GetOwner()->SetSkillTypeGarlic(true);
	Dest->GetOwner()->InflictDamage(m_Damage * m_AdditionalSkillDamage);
}

void CGarlic::CollisionEnd(CCollider* Src, CCollider* Dest)
{
	auto iter = m_ColliderOwnerList.begin();
	auto iterEnd = m_ColliderOwnerList.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter) == Dest->GetOwner())
		{
			m_ColliderOwnerList.erase(iter);
			break;
		}
	}
}
