#include "FallingLightning.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderCircle.h"
#include "Effect.h"
#include "../GameManager.h"
#include "../GameObject/GameObject.h"
#include "Lightning.h"
#include "../Scene/SceneResource.h"

CFallingLightning::CFallingLightning()
{
	SetTypeID<CFallingLightning>();
}

CFallingLightning::CFallingLightning(const CFallingLightning& Obj) :
	CSkill(Obj)
{
}

CFallingLightning::~CFallingLightning()
{
}

bool CFallingLightning::Init()
{
	CSkill::Init();

	// 충돌체 추가
	CColliderCircle* Circle1 = AddCollider<CColliderCircle>("Circle");

	Circle1->SetRadius(20);
	Circle1->SetOffset(20,2332);
	Circle1->SetCollisionProfile("PlayerAttack");

	Circle1->SetCollisionBeginFunction<CFallingLightning>(this, &CFallingLightning::CollisionBegin);
	Circle1->SetCollisionEndFunction<CFallingLightning>(this, &CFallingLightning::CollisionEnd);

	CreateAnimation();

	AddAnimation("Lightning", false, 0.3f);

	m_Scene->GetSceneResource()->SoundPlay("Lightning");

	m_vecSequenceKey[0].push_back("Lightning");

	SetEndFunction<CFallingLightning>("Lightning", this, &CFallingLightning::LightningEnd);

	// 생성시 우선 InitBible을 재생함.
	ChangeAnimation(m_vecSequenceKey[0][0]);
	

	return true;
}

void CFallingLightning::Update(float DeltaTime)
{
	// 레벨에 맞는 데미지를 설정해야 함. 
	CFallingLightning::GetLightning();

	CSkill::Update(DeltaTime);

	m_LightningTimePassed += DeltaTime;
}

void CFallingLightning::PostUpdate(float DeltaTime)
{
	CSkill::PostUpdate(DeltaTime);
}

void CFallingLightning::Render(HDC hDC, float DeltaTime)
{
	CSkill::Render(hDC, DeltaTime);
}

void CFallingLightning::GetLightning()
{
	// 데미지는 1레벨에는 15, 그 이후 6씩 증가한다.
	m_Damage = 15 + 6.f * (m_Lightning->GetSkillLevel() - 1);
}

void CFallingLightning::CollisionBegin(CCollider* Src, CCollider* Dest)
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

void CFallingLightning::CollisionEnd(CCollider* Src, CCollider* Dest)
{
}

void CFallingLightning::LightningEnd()
{
	SetActive(false);
}
