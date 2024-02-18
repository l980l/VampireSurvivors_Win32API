
#include "Player.h"
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


CPlayer::CPlayer()
{
	SetTypeID<CPlayer>();
}

CPlayer::CPlayer(const CPlayer& Obj) :
	CCharacter(Obj),
	m_DamagedTime(Obj.m_DamagedTime),
	m_vecSkill{Obj.m_vecSkill}

{
}

CPlayer::~CPlayer()
{
}



bool CPlayer::Init()
{
	CGameObject::Init();

	m_MoveSpeed = 300.f;

	m_DamagedTime = 0;
	m_vecSkill = {};

	m_HP = 200;
	m_HPMax = 200;
	m_Level = 1;
	m_ExpMax = 50;
	m_Exp = 0;

	m_KillCount = 0;

	// 기본은 당연히 1로 설정. 아이템을 먹으면 0.1씩 상승 최대 1.5까지 증가.
	m_AdditionalSkillDamage = 1.0f;
	m_AdditionalSkillDuration = 1.0f;
	m_AdditionalSkillSpeed = 1.0f;
	m_AdditionalSkillProjectile = 0;

	// 기본 스킬이 채찍임.
	/*CGarlic* Garlic = m_Scene->CreateObject<CGarlic>("Garlic");
	m_vecSkill.push_back(Garlic);*/

	//CBible* Bible = m_Scene->CreateObject<CBible>("Bible");
	//m_vecSkill.push_back(Bible);

	//CLightning* Lightning = m_Scene->CreateObject<CLightning>("Lightning");
	//m_vecSkill.push_back(Lightning);

	CWhip* Whip = m_Scene->CreateObject<CWhip>("Whip");
	m_vecSkill.push_back(Whip);



	SetPos(1280.f, 1280.f);
	SetPivot(0.5f, 1.f);

	SetSideWallCheck(true);

	//SetTexture("Player", TEXT("Player/Right/alert.bmp"));
	//SetColorKey(255, 0, 255);


	CreateAnimation();

	AddAnimation("PlayerRightWalk");
	AddAnimation("DamagedPlayerRightWalk");
	AddAnimation("PlayerLeftWalk");
	AddAnimation("DamagedPlayerLeftWalk");

	m_vecSequenceKey[0].push_back("PlayerRightWalk");
	m_vecSequenceKey[0].push_back("DamagedPlayerRightWalk");

	m_vecSequenceKey[1].push_back("PlayerLeftWalk");
	m_vecSequenceKey[1].push_back("DamagedPlayerLeftWalk");

	// 오른쪽 보고 있음.
	m_PlayerDir = 1;


	// 충돌체 추가
	CColliderBox* Box = AddCollider<CColliderBox>("ColliderBox");

	Box->SetExtent(43.f, 68.f);
	Box->SetOffset(0.f, -40.f);
	Box->SetCollisionProfile("Player");

	Box->SetCollisionBeginFunction<CPlayer>(this, &CPlayer::CollisionBegin);
	Box->SetCollisionEndFunction<CPlayer>(this, &CPlayer::CollisionEnd);


	CInput::GetInst()->AddBindFunction<CPlayer>("MoveUp",
		Input_Type::Push, this, &CPlayer::MoveUp);

	CInput::GetInst()->AddBindFunction<CPlayer>("MoveDown",
		Input_Type::Push, this, &CPlayer::MoveDown);

	CInput::GetInst()->AddBindFunction<CPlayer>("MoveRight",
		Input_Type::Push, this, &CPlayer::MoveRight);

	CInput::GetInst()->AddBindFunction<CPlayer>("MoveLeft",
		Input_Type::Push, this, &CPlayer::MoveLeft);

	m_HPBar = CreateWidgetComponent<CProgressBar>("HPBar1");

	m_HPBar->GetWidget<CProgressBar>()->SetTexture(EProgressBar_Texture_Type::Bar,
		"HPBar1", TEXT("CharacterHPBar.bmp"));
	m_HPBar->GetWidget<CProgressBar>()->SetSize(60.f, 7.f);
	m_HPBar->SetPos(-25.f, 0.f);

	
	return true;
}


void CPlayer::Update(float DeltaTime)
{
	CCharacter::Update(DeltaTime);

	m_Scene->FindWidget<CCharacterHUD>("CharacterHUD")->SetExp(m_Exp / (float)m_ExpMax);
	m_HPBar->GetWidget<CProgressBar>()->SetValue(m_HP / (float)m_HPMax);

	DeltaTime *= m_TimeScale;
}

void CPlayer::PostUpdate(float DeltaTime)
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

void CPlayer::Render(HDC hDC, float DeltaTime)
{
	CCharacter::Render(hDC, DeltaTime);
}

float CPlayer::InflictDamage(float Damage)
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
		}
	}

	return Damage;
}

int CPlayer::GetGarlicLevel()
{
	auto iter = m_vecSkill.begin();
	auto iterEnd = m_vecSkill.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->GetName() == "Garlic")
			return (*iter)->GetSkillLevel();
	}

	return 0;
}

int CPlayer::GetBibleLevel()
{
	auto iter = m_vecSkill.begin();
	auto iterEnd = m_vecSkill.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->GetName() == "Bible")
			return (*iter)->GetSkillLevel();

	}

	return 0;
}

int CPlayer::GetLightningLevel()
{
	auto iter = m_vecSkill.begin();
	auto iterEnd = m_vecSkill.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->GetName() == "Lightning")
			return (*iter)->GetSkillLevel();

	}

	return 0;
}

int CPlayer::GetWhipLevel()
{
	auto iter = m_vecSkill.begin();
	auto iterEnd = m_vecSkill.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->GetName() == "Whip")
			return (*iter)->GetSkillLevel();

	}

	return 0;
}

void CPlayer::GarlicSkillLevelUp()
{
	auto iter = m_vecSkill.begin();
	auto iterEnd = m_vecSkill.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->GetName() == "Garlic")
		{
			(*iter)->SkillLevelUp();
		}
	}
}

void CPlayer::BibleSkillLevelUp()
{
	auto iter = m_vecSkill.begin();
	auto iterEnd = m_vecSkill.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->GetName() == "Bible")
		{
			(*iter)->SkillLevelUp();
		}
	}
}

void CPlayer::LightningSkillLevelUp()
{
	auto iter = m_vecSkill.begin();
	auto iterEnd = m_vecSkill.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->GetName() == "Lightning")
		{
			(*iter)->SkillLevelUp();
		}
	}
}

void CPlayer::WhipSkillLevelUp()
{
	auto iter = m_vecSkill.begin();
	auto iterEnd = m_vecSkill.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->GetName() == "Whip")
		{
			(*iter)->SkillLevelUp();
		}
	}
}

void CPlayer::BibleSkillEvolution()
{
	// 지속시간 증가 아이템이 없다면 그냥 바로 return 한다.
	/*if (m_AdditionalSkillDuration < 2)
		return;*/

	auto iter = m_vecSkill.begin();
	auto iterEnd = m_vecSkill.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->GetName() == "Bible")
		{
			// Bible이 8렙이면 진화
			if ((*iter)->GetSkillLevel() == 8)
			{
				// 일단 스킬 죽이고 진화 스킬로 바꿈.
				(*iter)->SetActive(false);

				CEvolvedBible* EvolvedBible = m_Scene->CreateObject<CEvolvedBible>("EvolvedBible");

				*iter = EvolvedBible;

				m_Scene->FindWidget<CCharacterHUD>("CharacterHUD")->AddEvolvedBible();
				m_Scene->FindWidget<CCharacterHUD>("CharacterHUD")->UpdateSkillAndItemIcon();
			}
		}
	}
}


void CPlayer::SkillSpeedUp()
{
	if (m_AdditionalSkillSpeed >= 1.5f)
		m_AdditionalSkillSpeed = 1.5f;

	else if (m_AdditionalSkillSpeed < 1)
		m_AdditionalSkillSpeed = 1;

	else
	{
		m_AdditionalSkillSpeed += 0.1f;
	}
}

void CPlayer::SkillDamageUp()
{
	if (m_AdditionalSkillDamage >= 1.5f)
		m_AdditionalSkillDamage = 1.5f;

	else if (m_AdditionalSkillDamage < 1)
		m_AdditionalSkillDamage = 1;

	else
	{
		m_AdditionalSkillDamage += 0.1f;
	}
}

void CPlayer::SkillDurationUp()
{
	if (m_AdditionalSkillDuration >= 1.5f)
		m_AdditionalSkillDuration = 1.5f;

	else if (m_AdditionalSkillDuration < 1)
		m_AdditionalSkillDuration = 1;

	else
	{
		m_AdditionalSkillDuration += 0.1f;
	}
}

void CPlayer::SkillProjectileUp()
{
	if (m_AdditionalSkillDuration >= 2)
		m_AdditionalSkillProjectile = 2;

	else if (m_AdditionalSkillDuration < 0)
		m_AdditionalSkillProjectile = 0;

	else
	{
		m_AdditionalSkillProjectile += 1;
	}
}

void CPlayer::CreateGarlicSkill()
{
	CGarlic* Garlic = m_Scene->CreateObject<CGarlic>("Garlic");
	m_vecSkill.push_back(Garlic);
}

void CPlayer::CreateBibleSkill()
{
	CBible* Bible = m_Scene->CreateObject<CBible>("Bible");
	m_vecSkill.push_back(Bible);
}

void CPlayer::CreateLightningSkill()
{
	CLightning* Lightning = m_Scene->CreateObject<CLightning>("Lightning");
	m_vecSkill.push_back(Lightning); 
}

void CPlayer::CreateWhipSkill()
{
	CWhip* Whip = m_Scene->CreateObject<CWhip>("Whip");
	m_vecSkill.push_back(Whip);
}

void CPlayer::ExpUp(int Exp)
{
	m_Exp += Exp;

	// 레벨업 할때마다 다음 레벨업에 필요한 Exp는 10프로씩 증가하게 한다. 
	if (m_Exp >= m_ExpMax)
	{
		++m_Level;
		m_Exp -= m_ExpMax;
		m_ExpMax = (int)(m_ExpMax * 1.1f);
		
		if(m_Scene->FindWidget<CLevelUpWindow>("LevelUpWindow"))
			m_Scene->FindWidget<CLevelUpWindow>("LevelUpWindow")->SetActive(false);

		m_Scene->CreateWidgetWindow<CLevelUpWindow>("LevelUpWindow");
	}
}

void CPlayer::HPUP(int HP)
{
	m_HP += HP;

	if (m_HP >= m_HPMax)
	{
		m_HP = m_HPMax;
	}
}

ETreasure_Result CPlayer::TreasureRandom()
{
	std::vector<CSharedPtr<CSkill>>	VecSkill = m_vecSkill;

	auto iter = VecSkill.begin();
	auto iterEnd = VecSkill.end();

	for (; iter != iterEnd;)
	{
		if ((*iter)->GetSkillLevel() == 8)
		{
			// Bible 8렙이면 무조건 진화
			if ((*iter)->GetName() == "Bible")
			{
				CPlayer::BibleSkillEvolution();
				return ETreasure_Result::EvolvedBible;
			}

			// 8렙인데 Bible 아니면 그냥 빼.
			iter = VecSkill.erase(iter);
			iterEnd = VecSkill.end();
		}

		else
			++iter;
	}

	// 일단 스킬 갯수만큼.
	int Num = (int)VecSkill.size();

	if (m_AdditionalSkillDamage > 1 && m_AdditionalSkillDamage < 1.5)
		++Num;

	if (m_AdditionalSkillDuration > 1 && m_AdditionalSkillDuration < 1.5)
		++Num;

	if (m_AdditionalSkillSpeed > 1 && m_AdditionalSkillSpeed < 1.5)
		++Num;

	if (m_AdditionalSkillProjectile > 0 && m_AdditionalSkillProjectile < 2)
		++Num;

	srand((unsigned int)time(0));

	int Random = rand();
	
	Random = rand() % Num;

	if (Random < VecSkill.size())
	{
		iter = VecSkill.begin();

		for (int i = 0; i < Random; ++i)
		{
			++iter;
		}

		if ((*iter)->GetName() == "Garlic")
		{
			CPlayer::GarlicSkillLevelUp();
			return ETreasure_Result::Garlic;
		}

		else if ((*iter)->GetName() == "Bible")
		{
			CPlayer::BibleSkillLevelUp();
			return ETreasure_Result::Bible;
		}

		else if ((*iter)->GetName() == "Lightning")
		{
			CPlayer::LightningSkillLevelUp();
			return ETreasure_Result::Lightning;
		}

		else if ((*iter)->GetName() == "Whip")
		{
			CPlayer::WhipSkillLevelUp();
			return ETreasure_Result::Whip;
		}
	}

	else
	{
		int Num2 = rand() % (Random - (VecSkill.size()-1));

		if (Num2 == 0)
		{
			if (m_AdditionalSkillDamage > 1 && m_AdditionalSkillDamage < 1.5)
			{
				CPlayer::SkillDamageUp();
				return ETreasure_Result::AdditionalSkillDamage;
			}

			else if (m_AdditionalSkillDuration > 1 && m_AdditionalSkillDuration < 1.5)
			{
				CPlayer::SkillDurationUp();
				return ETreasure_Result::AdditionalSkillDuration;
			}

			else if (m_AdditionalSkillSpeed > 1 && m_AdditionalSkillSpeed < 1.5)
			{
				CPlayer::SkillSpeedUp();
				return ETreasure_Result::AdditionalSkillSpeed;
			}

			else if (m_AdditionalSkillProjectile > 0 && m_AdditionalSkillProjectile < 2)
			{
				CPlayer::SkillProjectileUp();
				return ETreasure_Result::AdditionalSkillProjectile;
			}

		}

		else if (Num2 == 1)
		{
			if (m_AdditionalSkillDuration > 1 && m_AdditionalSkillDuration < 1.5)
			{
				CPlayer::SkillDurationUp();
				return ETreasure_Result::AdditionalSkillDuration;
			}

			else if (m_AdditionalSkillSpeed > 1 && m_AdditionalSkillSpeed < 1.5)
			{
				CPlayer::SkillSpeedUp();
				return ETreasure_Result::AdditionalSkillSpeed;
			}

			else if (m_AdditionalSkillProjectile > 0 && m_AdditionalSkillProjectile < 2)
			{
				CPlayer::SkillProjectileUp();
				return ETreasure_Result::AdditionalSkillProjectile;
			}
		}

		else if (Num2 == 2)
		{
			if (m_AdditionalSkillSpeed > 1 && m_AdditionalSkillSpeed < 1.5)
			{
				CPlayer::SkillSpeedUp();
				return ETreasure_Result::AdditionalSkillSpeed;
			}

			else if (m_AdditionalSkillProjectile > 0 && m_AdditionalSkillProjectile < 2)
			{
				CPlayer::SkillProjectileUp();
				return ETreasure_Result::AdditionalSkillProjectile;
			}
		}

		else if (Num2 == 3)
		{
			if (m_AdditionalSkillProjectile > 0 && m_AdditionalSkillProjectile < 2)
			{
				CPlayer::SkillProjectileUp();
				return ETreasure_Result::AdditionalSkillProjectile;
			}
		}
	}
	
	// 나올거 없으면 치킨 나오게 함.
	CPlayer::HPUP(60);
	return ETreasure_Result::Chicken;
}

std::list<std::string>  CPlayer::LevelUpRandom()
{
	std::vector<CSharedPtr<CSkill>>	VecSkill = m_vecSkill;
	
	std::list<std::string> ResultList;
	ResultList.push_back("Garlic");
	ResultList.push_back("Bible");
	ResultList.push_back("Lightning");
	ResultList.push_back("Whip");
	ResultList.push_back("AdditionalSkillDamage");
	ResultList.push_back("AdditionalSkillDuration");
	ResultList.push_back("AdditionalSkillSpeed");
	ResultList.push_back("AdditionalSkillProjectile");

	auto iter = VecSkill.begin();
	auto iterEnd = VecSkill.end();

	for (; iter != iterEnd; ++iter)
	{
		// 8렙인 스킬 빼기
		if ((*iter)->GetSkillLevel() == 8)
		{
			auto iter1 = ResultList.begin();
			auto iter1End = ResultList.end();

			for (; iter1 != iter1End;)
			{
				if ((*iter)->GetName() == (*iter1))
				{
					ResultList.erase(iter1);
					break;
				}

				++iter1;
			}
		}

		if ((*iter)->GetName() == "EvolvedBible")
		{
			auto iter1 = ResultList.begin();
			auto iter1End = ResultList.end();

			for (; iter1 != iter1End; ++iter1)
			{
				if ("Bible" == (*iter1))
				{
					ResultList.erase(iter1);
					break;
				}
			}
		}
	}
	
	if (m_AdditionalSkillDamage >= 1.5)
	{
		auto iter1 = ResultList.begin();
		auto iter1End = ResultList.end();

		for (; iter1 != iter1End; ++iter1)
		{
			if ("AdditionalSkillDamage" == (*iter1))
			{
				ResultList.erase(iter1);
				break;
			}
		}
	}
	if (m_AdditionalSkillDuration >= 1.5)
	{
		auto iter1 = ResultList.begin();
		auto iter1End = ResultList.end();

		for (; iter1 != iter1End; ++iter1)
		{
			if ("AdditionalSkillDuration" == (*iter1))
			{
				ResultList.erase(iter1);
				break;
			}
		}
	}

	if (m_AdditionalSkillSpeed >= 1.5)
	{
		auto iter1 = ResultList.begin();
		auto iter1End = ResultList.end();

		for (; iter1 != iter1End; ++iter1)
		{
			if ("AdditionalSkillSpeed" == (*iter1))
			{
				ResultList.erase(iter1);
				break;
			}
		}
	}

	if (m_AdditionalSkillProjectile >= 2)
	{
		auto iter1 = ResultList.begin();
		auto iter1End = ResultList.end();

		for (; iter1 != iter1End; ++iter1)
		{
			if ("AdditionalSkillProjectile" == (*iter1))
			{
				ResultList.erase(iter1);
				break;
			}
		}
	}

	// 전부 다 만렙이면 예외처리
	if (ResultList.size() == 0)
	{
		ResultList.push_back("Chicken");
		return ResultList;
	}

	for (int j = 0; j < 100; ++j)
	{
		auto iter = ResultList.begin();

		for (int i = 0; i < rand() % ResultList.size(); ++i)
		{
			++iter;
		}

		std::string temp = *ResultList.begin();

		*ResultList.begin() = *iter;
		*iter = temp;
	}

	if (ResultList.size() <= 3)
		return ResultList;


	ResultList.resize(3);

	return ResultList;
}

int CPlayer::GetSkillLevel(std::string SkillName)
{
	auto iter = m_vecSkill.begin();
	auto iterEnd = m_vecSkill.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->GetName() == SkillName)
		{
			return (*iter)->GetSkillLevel();
		}
	}

	// 못찾으면 0 반환.
	return 0;
}

void CPlayer::MoveUp()
{
	MoveDir(Vector2(0.f, -1.f));
}

void CPlayer::MoveDown()
{
	MoveDir(Vector2(0.f, 1.f));
}

void CPlayer::MoveRight()
{
	MoveDir(Vector2(1.f, 0.f));
	m_PlayerDir = 1;
}

void CPlayer::MoveLeft()
{
	MoveDir(Vector2(-1.f, 0.f));
	m_PlayerDir = -1;
}

void CPlayer::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	
}

void CPlayer::CollisionEnd(CCollider* Src, CCollider* Dest)
{
}
