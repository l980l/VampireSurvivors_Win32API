
#include "CharacterHUD.h"
#include "Button.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../GameManager.h"
#include "../Scene/MainScene.h"
#include "../Scene/SceneManager.h"
#include "../Input.h"
#include "ProgressBar.h"
#include "ImageWidget.h"
#include "Text.h"
#include "../GameObject/Skill.h"

CCharacterHUD::CCharacterHUD()
{
}

CCharacterHUD::~CCharacterHUD()
{
}

bool CCharacterHUD::Init()
{
	if (!CWidgetWindow::Init())
		return false;

	SetSize(210.f, 110.f);
	SetPos(0.f, 0.f);

	// ExpBar
	m_ExpBarFrame = CreateWidget<CImageWidget>("ExpBarFrame");

	m_ExpBarFrame->SetTexture("ExpBarFrame", TEXT("Texture/UI/ExpBarFrame.bmp"));
	m_ExpBarFrame->SetColorKey(255, 0, 255);

	m_ExpBarFrame->SetSize(1280.f, 31.f);
	m_ExpBarFrame->SetZOrder(1);

	m_ExpPBar = CreateWidget<CProgressBar>("ExpBar");

	m_ExpPBar->SetTexture(EProgressBar_Texture_Type::Bar, "HUDExpBar", TEXT("Texture/UI/ExpBar.bmp"));

	m_ExpPBar->SetSize(1280.f, 29.f);
	m_ExpPBar->SetPos(0.f, 0.f);
	m_ExpPBar->SetZOrder(0);

	m_ExpPBar->SetBarDir(EProgressBar_Dir::LeftToRight);

	// Level
	m_LevelText = CreateWidget<CText>("LevelText");

	TCHAR	FileName1[MAX_PATH] = {};
	wsprintf(FileName1, TEXT("LV %d"), m_Scene->GetPlayer()->GetPlayerLevel());

	m_LevelText->SetText(FileName1);
	m_LevelText->SetPos(1220.f, 5.f);
	m_LevelText->SetTextColor(255, 255, 255);
	m_LevelText->SetFont("SmallFont");
	m_LevelText->SetZOrder(2);

#ifdef _DEBUG

	// FPS
	m_FPSText = CreateWidget<CText>("Text");

	m_FPSText->SetText(TEXT("FPS"));
	m_FPSText->SetPos(900.f, 50.f);
	m_FPSText->SetTextColor(255, 0, 0);

	m_FPSText->EnableShadow(true);
	m_FPSText->SetShadowOffset(2.f, 2.f);

#endif

	// Skull
	CSharedPtr<CImageWidget> Skull = CreateWidget<CImageWidget>("Skull");

	Skull->SetTexture("Skull", TEXT("Texture/UI/Skull.bmp"));
	Skull->SetColorKey(255, 0, 255);

	Skull->SetSize(16.f, 14.f);
	Skull->SetPos(1066.f, 33.f);

	// KillCount
	m_KillCountText = CreateWidget<CText>("KillCountText");

	TCHAR	FileName2[MAX_PATH] = {};
	wsprintf(FileName2, TEXT("%d"), m_Scene->GetPlayer()->GetKillCount());

	m_KillCountText->SetText(FileName2);
	m_KillCountText->SetPos(1020.f, 31.f);
	m_KillCountText->SetTextColor(255, 255, 255);
	m_KillCountText->SetFont("SmallFont");

	// 흐른 시간
	m_Time = 0;
	m_TimeText = CreateWidget<CText>("TimeText");

	m_TimeText->SetText(TEXT("00 : 00"));
	m_TimeText->SetPos(580.f, 40.f);	
	m_TimeText->SetTextColor(255, 255, 255);
	m_TimeText->SetFont("MiddleFont");

	// Skill & Item Frame
	CSharedPtr<CImageWidget> SkillFrame = CreateWidget<CImageWidget>("SkillFrame");

	SkillFrame->SetTexture("SkillFrame", TEXT("Texture/UI/SkillFrame.bmp"));
	SkillFrame->SetColorKey(255, 0, 255);

	SkillFrame->SetSize(294.f, 109.f);
	SkillFrame->SetPos(0.f, 31.f);

	// 초기 스킬 넣기. 
	if (m_Scene->GetPlayer()->GetSkillLevel("Garlic"))
		m_vecSkill.push_back("Garlic");
	if (m_Scene->GetPlayer()->GetSkillLevel("Bible"))
		m_vecSkill.push_back("Bible");
	if (m_Scene->GetPlayer()->GetSkillLevel("Lightning"))
		m_vecSkill.push_back("Lightning");
	if (m_Scene->GetPlayer()->GetSkillLevel("Whip"))
		m_vecSkill.push_back("Whip");

	CCharacterHUD::UpdateSkillAndItemIcon();

	return true;
}

void CCharacterHUD::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);

#ifdef _DEBUG

	float FPS = CGameManager::GetInst()->GetFPS();

	char	Text[256] = {};
	sprintf_s(Text, "FPS: %.5f", FPS);

	TCHAR	Unicode[256] = {};
	int Length = MultiByteToWideChar(CP_ACP, 0, Text, -1, 0, 0);
	MultiByteToWideChar(CP_ACP, 0, Text, -1, Unicode, Length);

	m_FPSText->SetText(Unicode);

#endif

	// Level
	TCHAR	FileName1[MAX_PATH] = {};
	wsprintf(FileName1, TEXT("LV %d"), m_Scene->GetPlayer()->GetPlayerLevel());

	m_LevelText->SetText(FileName1);

	// KillCount
	TCHAR	FileName2[MAX_PATH] = {};
	wsprintf(FileName2, TEXT("%d"), m_Scene->GetPlayer()->GetKillCount());

	m_KillCountText->SetText(FileName2);

	// 흐른 시간
	m_Time += DeltaTime;


	TCHAR	FileName3[MAX_PATH] = {};
	wsprintf(FileName3, TEXT("%d%d : %d%d"), (int)m_Time/600, (int)m_Time / 60, ((int)m_Time % 60) / 10, (int)m_Time % 10);

	m_TimeText->SetText(FileName3);
}

void CCharacterHUD::SetExp(float Exp)
{
	m_ExpPBar->SetValue(Exp);
}

void CCharacterHUD::AddItem(std::string Item)
{
	auto iter = m_vecItem.begin();
	auto iterEnd = m_vecItem.end();

	for (; iter != iterEnd; ++iter)
	{
		if (Item == (*iter))
		{
			return;
		}
	}

	m_vecItem.push_back(Item);
}

void CCharacterHUD::AddSkill(std::string Skill)
{
	auto iter = m_vecSkill.begin();
	auto iterEnd = m_vecSkill.end();

	for (; iter != iterEnd; ++iter)
	{
		if (Skill == (*iter))
		{
			return;
		}
	}

	m_vecSkill.push_back(Skill);
}


void CCharacterHUD::AddEvolvedBible()
{
	auto iter = m_vecSkill.begin();
	auto iterEnd = m_vecSkill.end();

	for (; iter != iterEnd; ++iter)
	{
		if ("Bible" == (*iter))
		{
			(*iter) = "EvolvedBible";
			return;
		}
	}
}

void CCharacterHUD::UpdateSkillAndItemIcon()
{
	{
		auto iter = m_vecSkill.begin();
		auto iterEnd = m_vecSkill.end();

		int SkillCount = 0;

		for (; iter != iterEnd; ++iter)
		{
			CSharedPtr<CImageWidget> SkillIcon = CreateWidget<CImageWidget>((*iter) + "HUDIcon");
		
			if ((*iter) == "Garlic")
			{
				SkillIcon->SetTexture((*iter) + "HUDIcon", TEXT("Texture/UI/GarlicIcon.bmp"));
			}

			else if ((*iter) == "Bible")
			{
				SkillIcon->SetTexture((*iter) + "HUDIcon", TEXT("Texture/UI/BibleIcon.bmp"));
			}

			else if ((*iter) == "Lightning")
			{
				SkillIcon->SetTexture((*iter) + "HUDIcon", TEXT("Texture/UI/LightningIcon.bmp"));
			}

			else if ((*iter) == "Whip")
			{
				SkillIcon->SetTexture((*iter) + "HUDIcon", TEXT("Texture/UI/WhipIcon.bmp"));
			}

			else if ((*iter) == "EvolvedBible")
			{
				SkillIcon->SetTexture((*iter) + "HUDIcon", TEXT("Texture/UI/EvolvedBibleIcon.bmp"));
			}

			SkillIcon->SetColorKey(255, 0, 255);

			SkillIcon->SetSize(37.f, 37.f);
			SkillIcon->SetPos(7.f + 48.f * SkillCount, 39.f);

			++SkillCount;
		}
	}

	{
		auto iter = m_vecItem.begin();
		auto iterEnd = m_vecItem.end();

		int ItemCount = 0;

		for (; iter != iterEnd; ++iter)
		{
			CSharedPtr<CImageWidget> ItemIcon = CreateWidget<CImageWidget>((*iter) + "HUDIcon");

			if ((*iter) == "AdditionalSkillDamage")
			{
				ItemIcon->SetTexture((*iter) + "HUDIcon", TEXT("Texture/UI/AdditionalSkillDamageIcon.bmp"));
			}

			else if ((*iter) == "AdditionalSkillDuration")
			{
				ItemIcon->SetTexture((*iter) + "HUDIcon", TEXT("Texture/UI/AdditionalSkillDurationIcon.bmp"));
			}

			else if ((*iter) == "AdditionalSkillSpeed")
			{
				ItemIcon->SetTexture((*iter) + "HUDIcon", TEXT("Texture/UI/AdditionalSkillSpeedIcon.bmp"));
			}

			else if ((*iter) == "AdditionalSkillProjectile")
			{
				ItemIcon->SetTexture((*iter) + "HUDIcon", TEXT("Texture/UI/AdditionalSkillProjectileIcon.bmp"));
			}

			ItemIcon->SetColorKey(255, 0, 255);

			ItemIcon->SetSize(37.f, 37.f);
			ItemIcon->SetPos(7.f + 48.f * ItemCount, 89.f);

			++ItemCount;
		}
	}
}
