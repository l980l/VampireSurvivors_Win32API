
#include "Player2.h"
#include "../Scene/Scene.h"
#include "../Input.h"
#include "../GameManager.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderBox.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Widget/CharacterHUD.h"
#include "../Widget/WidgetComponent.h"
#include "../Widget/ProgressBar.h"
#include "../Widget/Text.h"
#include "Skill.h"
#include "Garlic.h"
#include "Bible.h"
#include "EvolvedBible.h"
#include "Lightning.h"
#include "Whip.h"
#include "../Widget/LevelUpWindow.h"
#include "../Widget/GameOverWindow.h"


CPlayer2::CPlayer2()
{
	SetTypeID<CPlayer2>();
}

CPlayer2::CPlayer2(const CPlayer2& Obj) :
	CPlayer(Obj)
{
}

CPlayer2::~CPlayer2()
{
}

bool CPlayer2::Init()
{
	CGameObject::Init();

	m_MoveSpeed = 300.f;

	m_DamagedTime = 0;
	m_vecSkill = {};

	m_HP = 100;
	m_HPMax = 100;
	m_Level = 1;
	m_ExpMax = 100;
	m_Exp = 0;

	m_KillCount = 0;

	// 기본은 당연히 1로 설정. 아이템을 먹으면 0.1씩 상승 최대 1.5까지 증가.
	m_AdditionalSkillDamage = 1.0f;
	m_AdditionalSkillDuration = 1.0f;
	m_AdditionalSkillSpeed = 1.0f;
	m_AdditionalSkillProjectile = 0;


	// 기본 스킬이 바이블임.
	CBible* Bible = m_Scene->CreateObject<CBible>("Bible");
	m_vecSkill.push_back(Bible);

	SetPos(1280.f, 1280.f);
	SetPivot(0.5f, 1.f);

	SetSideWallCheck(true);


	CreateAnimation();

	AddAnimation("Player2RightWalk");
	AddAnimation("DamagedPlayer2RightWalk");
	AddAnimation("Player2LeftWalk");
	AddAnimation("DamagedPlayer2LeftWalk");

	m_vecSequenceKey[0].push_back("Player2RightWalk");
	m_vecSequenceKey[0].push_back("DamagedPlayer2RightWalk");

	m_vecSequenceKey[1].push_back("Player2LeftWalk");
	m_vecSequenceKey[1].push_back("DamagedPlayer2LeftWalk");

	// 오른쪽 보고 있음.
	m_PlayerDir = 1;


	// 충돌체 추가
	CColliderBox* Box = AddCollider<CColliderBox>("ColliderBox");

	Box->SetExtent(43.f, 68.f);
	Box->SetOffset(0.f, -40.f);
	Box->SetCollisionProfile("Player");

	Box->SetCollisionBeginFunction<CPlayer2>(this, &CPlayer2::CollisionBegin);
	Box->SetCollisionEndFunction<CPlayer2>(this, &CPlayer2::CollisionEnd);


	CInput::GetInst()->AddBindFunction<CPlayer2>("MoveUp",
		Input_Type::Push, this, &CPlayer2::MoveUp);

	CInput::GetInst()->AddBindFunction<CPlayer2>("MoveDown",
		Input_Type::Push, this, &CPlayer2::MoveDown);

	CInput::GetInst()->AddBindFunction<CPlayer2>("MoveRight",
		Input_Type::Push, this, &CPlayer2::MoveRight);

	CInput::GetInst()->AddBindFunction<CPlayer2>("MoveLeft",
		Input_Type::Push, this, &CPlayer2::MoveLeft);


	m_HPBar = CreateWidgetComponent<CProgressBar>("HPBar1");

	m_HPBar->GetWidget<CProgressBar>()->SetTexture(EProgressBar_Texture_Type::Bar,
		"HPBar1", TEXT("CharacterHPBar.bmp"));
	m_HPBar->GetWidget<CProgressBar>()->SetSize(60.f, 7.f);
	m_HPBar->SetPos(-25.f, 0.f);

	

	return true;
}

void CPlayer2::Update(float DeltaTime)
{
	CCharacter::Update(DeltaTime);

	m_Scene->FindWidget<CCharacterHUD>("CharacterHUD")->SetExp(m_Exp / (float)m_ExpMax);
	m_HPBar->GetWidget<CProgressBar>()->SetValue(m_HP / (float)m_HPMax);

	DeltaTime *= m_TimeScale;
}

void CPlayer2::PostUpdate(float DeltaTime)
{
	CCharacter::PostUpdate(DeltaTime);

	int	AnimDirIndex = 0;

	if (m_PlayerDir == -1)
		AnimDirIndex = 1;

	m_DamagedTime += DeltaTime;

	// 0.5초에 한번씩만 피격당할 수 있게 함.
	if (m_DamagedTime >= 0.5)
	{
		m_Damaged = false;
		m_DamagedTime -= 0.5;
	}


	if (m_Move.x != 0.f || m_Move.y != 0.f)
	{
		if (!m_Damaged)
		{
			ChangeAnimation(m_vecSequenceKey[AnimDirIndex][0]);
			SetPlayScale(m_vecSequenceKey[AnimDirIndex][0], 1.f);
		}

		else
		{
			ChangeAnimation(m_vecSequenceKey[AnimDirIndex][1]);
			SetPlayScale(m_vecSequenceKey[AnimDirIndex][1], 1.f);
		}
	}

	else
	{
		if (!m_Damaged)
		{
			ChangeAnimation(m_vecSequenceKey[AnimDirIndex][0]);
			SetPlayScale(m_vecSequenceKey[AnimDirIndex][0], 0.f);
		}

		else
		{
			ChangeAnimation(m_vecSequenceKey[AnimDirIndex][1]);
			SetPlayScale(m_vecSequenceKey[AnimDirIndex][1], 0.f);
		}
	}
}

void CPlayer2::Render(HDC hDC, float DeltaTime)
{
	CCharacter::Render(hDC, DeltaTime);
}

float CPlayer2::InflictDamage(float Damage)
{
	if (!m_Damaged)
	{
		Damage = CCharacter::InflictDamage(Damage);

		m_HP -= (int)Damage;

		m_Damaged = true;

		m_Scene->GetSceneResource()->SoundPlay("PlayerHit");

		if (m_HP <= 0)
		{
			SetActive(false);

			CGameOverWindow* m_GamePauseWindow = m_Scene->CreateWidgetWindow<CGameOverWindow>("GamePauseWindow");
			CGameManager::GetInst()->SetTimeScale(0.f);

			SetActive(false);
		}
	}

	return Damage;
}

void CPlayer2::ExpUp(int Exp)
{
	if (m_Level/5 == 0)
		m_Exp += Exp;

	else if(m_Level/5 == 1)
		m_Exp += (int)(Exp * 1.1f);

	else if (m_Level / 5 == 2)
		m_Exp += (int)(Exp * 1.2f);

	else if (m_Level / 5 >= 3)
		m_Exp += (int)(Exp * 1.3f);


	// 레벨업 할때마다 다음 레벨업에 필요한 Exp는 10프로씩 증가하게 한다. 
	if (m_Exp >= m_ExpMax)
	{
		++m_Level;
		m_Exp -= m_ExpMax;
		m_ExpMax = (int)(m_ExpMax * 1.1f);

		if (m_Scene->FindWidget<CLevelUpWindow>("LevelUpWindow"))
			m_Scene->FindWidget<CLevelUpWindow>("LevelUpWindow")->SetActive(false);

		m_Scene->CreateWidgetWindow<CLevelUpWindow>("LevelUpWindow");
	}
}

void CPlayer2::MoveUp()
{
	MoveDir(Vector2(0.f, -1.f));
}

void CPlayer2::MoveDown()
{
	MoveDir(Vector2(0.f, 1.f));
}

void CPlayer2::MoveRight()
{
	MoveDir(Vector2(1.f, 0.f));
	m_PlayerDir = 1;
}

void CPlayer2::MoveLeft()
{
	MoveDir(Vector2(-1.f, 0.f));
	m_PlayerDir = -1;
}


void CPlayer2::CollisionBegin(CCollider* Src, CCollider* Dest)
{
}

void CPlayer2::CollisionEnd(CCollider* Src, CCollider* Dest)
{
}
