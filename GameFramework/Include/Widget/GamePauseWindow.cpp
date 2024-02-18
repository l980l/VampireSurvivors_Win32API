
#include "GamePauseWindow.h"
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
#include "SoundControlBar.h"
#include "../Scene/StartScene.h"
#include "CharacterHUD.h"

CGamePauseWindow::CGamePauseWindow()
{
}

CGamePauseWindow::~CGamePauseWindow()
{
}

bool CGamePauseWindow::Init()
{
	if (!CWidgetWindow::Init())
		return false;

	
	m_Scene->GetSceneResource()->LoadSound("UI", "StartButton", false,
		"sfx_sounds_pause7_in.ogg");
	m_Scene->GetSceneResource()->LoadSound("UI", "OptionButton", false,
		"sfx_sounds_pause7_out.ogg");

	SetSize(1280.f, 720.f);

	// 옵션 창
	m_OptionFrame = CreateWidget<CImageWidget>("OptionFrame");

	m_OptionFrame->SetTexture("OptionFrame", TEXT("Texture/UI/OptionFrame.bmp"));
	m_OptionFrame->SetColorKey(255, 0, 255);
	m_OptionFrame->SetSize(599.f, 547.f);
	m_OptionFrame->SetPos(340.f, 75.f);
	m_OptionFrame->SetZOrder(3);

	m_OptionFrameText = CreateWidget<CText>("OptionFrameText");

	m_OptionFrameText->SetText(TEXT("옵션"));
	m_OptionFrameText->SetPos(595.f, 90.f);
	m_OptionFrameText->SetTextColor(255, 255, 255);
	m_OptionFrameText->SetZOrder(4);

	m_SoundControlText = CreateWidget<CText>("SoundControlText");

	m_SoundControlText->SetText(TEXT("사운드"));
	m_SoundControlText->SetPos(375.f, 243.f);
	m_SoundControlText->SetTextColor(255, 255, 255);
	m_SoundControlText->SetFont("MiddleFont");
	m_SoundControlText->SetZOrder(4);

	m_MusicControlText = CreateWidget<CText>("MusicControlText");

	m_MusicControlText->SetText(TEXT("음악"));
	m_MusicControlText->SetPos(375.f, 431.f);
	m_MusicControlText->SetTextColor(255, 255, 255);
	m_MusicControlText->SetFont("MiddleFont");
	m_MusicControlText->SetZOrder(4);

	m_SoundControlBar = CreateWidget<CSoundControlBar>("SoundControlBar");

	m_SoundControlBar->SetSize(55.f, 56.f);
	m_SoundControlBar->SetTexture("SoudControlButton", TEXT("Texture/UI/DragButton.bmp"));

	m_SoundControlBar->SetPos(675.f, 243.f);
	m_SoundControlBar->SetSoundType("Sound");
	m_SoundControlBar->SetZOrder(4);

	m_MusicControlBar = CreateWidget<CSoundControlBar>("MusicControlBar");

	m_MusicControlBar->SetSize(55.f, 56.f);
	m_MusicControlBar->SetTexture("MusicControlButton", TEXT("Texture/UI/DragButton.bmp"));

	m_MusicControlBar->SetPos(675.f, 431.f);
	m_MusicControlBar->SetSoundType("Music");
	m_MusicControlBar->SetZOrder(4);
	
	// 일시정지 나가기 버튼
	m_BattleExitButton = CreateWidget<CButton>("BattleExitButton");

	m_BattleExitButton->SetTexture("BattleExitButton", TEXT("Texture/UI/ExitButton.bmp"));
	m_BattleExitButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(113.f, 66.f));
	m_BattleExitButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(0.f, 0.f), Vector2(113.f, 66.f));
	m_BattleExitButton->SetButtonStateData(EButton_State::Click, Vector2(0.f, 0.f), Vector2(113.f, 66.f));
	m_BattleExitButton->SetButtonStateData(EButton_State::Disable, Vector2(0.f, 0.f), Vector2(113.f, 66.f));
	m_BattleExitButton->SetColorKey(255, 0, 255);

	m_BattleExitButton->SetSound(EButton_Sound_State::Click, "OptionButton");

	m_BattleExitButton->SetPos(590.f, 635.f);
	m_BattleExitButton->SetZOrder(4);

	m_BattleExitButton->SetCallback<CGamePauseWindow>(EButton_Sound_State::Click,
		this, &CGamePauseWindow::BattleExitButtonCallback);

	m_BattleExitButtonText = CreateWidget<CText>("BattleExitButtonText");

	m_BattleExitButtonText->SetText(TEXT("종료"));
	m_BattleExitButtonText->SetPos(618.f, 645.f);
	m_BattleExitButtonText->SetTextColor(255, 255, 255);
	m_BattleExitButtonText->SetFont("MiddleFont");
	m_BattleExitButtonText->SetZOrder(5);

	// 스킬 레벨 창
	m_SkillLevelFrame = CreateWidget<CImageWidget>("SkillLevelFrame");

	m_SkillLevelFrame->SetTexture("SkillLevelFrame", TEXT("Texture/UI/SkillFrame2.bmp"));
	m_SkillLevelFrame->SetColorKey(255, 0, 255);

	m_SkillLevelFrame->SetSize(294.f, 187.f);
	m_SkillLevelFrame->SetPos(0.f, 31.f);

	m_vecItem = m_Scene->FindWidget<CCharacterHUD>("CharacterHUD")->GetVecItem();
	m_vecSkill = m_Scene->FindWidget<CCharacterHUD>("CharacterHUD")->GetVecSkill();

	{
		auto iter = m_vecSkill.begin();
		auto iterEnd = m_vecSkill.end();

		int SkillCount = 0;

		for (; iter != iterEnd; ++iter)
		{
			CSharedPtr<CImageWidget> SkillIcon = CreateWidget<CImageWidget>((*iter) + "HUDIcon");
			int SkillLevel = 0;

			if ((*iter) == "Garlic")
			{
				SkillIcon->SetTexture((*iter) + "HUDIcon", TEXT("Texture/UI/GarlicIcon.bmp"));
				SkillLevel = m_Scene->GetPlayer()->GetGarlicLevel();
			}

			else if ((*iter) == "Bible")
			{
				SkillIcon->SetTexture((*iter) + "HUDIcon", TEXT("Texture/UI/BibleIcon.bmp"));
				SkillLevel = m_Scene->GetPlayer()->GetBibleLevel();
			}

			else if ((*iter) == "Lightning")
			{
				SkillIcon->SetTexture((*iter) + "HUDIcon", TEXT("Texture/UI/LightningIcon.bmp"));
				SkillLevel = m_Scene->GetPlayer()->GetLightningLevel();
			}

			else if ((*iter) == "Whip")
			{
				SkillIcon->SetTexture((*iter) + "HUDIcon", TEXT("Texture/UI/WhipIcon.bmp"));
				SkillLevel = m_Scene->GetPlayer()->GetWhipLevel();
			}

			else if ((*iter) == "EvolvedBible")
			{
				SkillIcon->SetTexture((*iter) + "HUDIcon", TEXT("Texture/UI/EvolvedBibleIcon.bmp"));
				SkillLevel = 0;
			}

			SkillIcon->SetColorKey(255, 0, 255);

			SkillIcon->SetSize(37.f, 37.f);
			SkillIcon->SetPos(7.f + 48.f * SkillCount, 39.f);


			TCHAR	FileName[MAX_PATH] = {};
			wsprintf(FileName, TEXT("Texture/UI/SkillLevel%d.bmp"), SkillLevel);

			//
			char	TextureName[MAX_PATH] = {};
			sprintf_s(TextureName, "SkillLevel%d.bmp", SkillLevel);

			CSharedPtr<CImageWidget> SkillLevelIcon = CreateWidget<CImageWidget>(TextureName);
			SkillLevelIcon->SetTexture(TextureName, FileName);
			SkillLevelIcon->SetColorKey(255, 0, 255);

			SkillLevelIcon->SetSize(37.f, 36.f);
			SkillLevelIcon->SetPos(7.f + 48.f * SkillCount, 76.f);

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
			int ItemLevel = 0;

			if ((*iter) == "AdditionalSkillDamage")
			{
				ItemIcon->SetTexture((*iter) + "HUDIcon", TEXT("Texture/UI/AdditionalSkillDamageIcon.bmp"));
				ItemLevel = (int)((m_Scene->GetPlayer()->GetAdditionSkillDamage() - 1.f) * 10);
			}

			else if ((*iter) == "AdditionalSkillDuration")
			{
				ItemIcon->SetTexture((*iter) + "HUDIcon", TEXT("Texture/UI/AdditionalSkillDurationIcon.bmp"));
				ItemLevel = (int)((m_Scene->GetPlayer()->GetAdditionSkillDuration() - 1.f) * 10);
			}

			else if ((*iter) == "AdditionalSkillSpeed")
			{
				ItemIcon->SetTexture((*iter) + "HUDIcon", TEXT("Texture/UI/AdditionalSkillSpeedIcon.bmp"));
				ItemLevel = (int)((m_Scene->GetPlayer()->GetAdditionSkillSpeed() - 1.f) * 10);
			}

			else if ((*iter) == "AdditionalSkillProjectile")
			{
				ItemIcon->SetTexture((*iter) + "HUDIcon", TEXT("Texture/UI/AdditionalSkillProjectileIcon.bmp"));
				ItemLevel = m_Scene->GetPlayer()->GetAdditionSkillProjectile();
				
				if (ItemLevel == 1)
					ItemLevel = 21;
				else
					ItemLevel = 22;
			}

			ItemIcon->SetColorKey(255, 0, 255);

			ItemIcon->SetSize(37.f, 37.f);
			ItemIcon->SetPos(7.f + 48.f * ItemCount, 128.f);


			TCHAR	FileName[MAX_PATH] = {};
			wsprintf(FileName, TEXT("Texture/UI/ItemLevel%d.bmp"), ItemLevel);

			//
			char	TextureName[MAX_PATH] = {};
			sprintf_s(TextureName, "ItemLevel%d.bmp", ItemLevel);

			CSharedPtr<CImageWidget> ItemLevelIcon = CreateWidget<CImageWidget>(TextureName);
			ItemLevelIcon->SetTexture(TextureName, FileName);
			ItemLevelIcon->SetColorKey(255, 0, 255);

			ItemLevelIcon->SetSize(37.f, 36.f);
			ItemLevelIcon->SetPos(7.f + 48.f * ItemCount, 165.f);

			++ItemCount;
		}
	}

	return true;
}

void CGamePauseWindow::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);

	// Sound 변동사항 적용하기
	m_Scene->GetSceneResource()->SetVolume("BGM", g_MusicVolume);
	m_Scene->GetSceneResource()->SetVolume("UI", g_SoundVolume);
	m_Scene->GetSceneResource()->SetVolume("Effect", g_SoundVolume);
}

void CGamePauseWindow::BattleExitButtonCallback()
{
	CInput::GetInst()->ClearCallback();

	// Sound 일시적으로 끄기
	m_Scene->GetSceneResource()->SetVolume(0);

	// 배경
	m_Back = CreateWidget<CImageWidget>("Back");

	m_Back->SetTexture("Back", TEXT("Texture/Intro.bmp"));
	m_Back->SetColorKey(255, 0, 255);
	m_Back->SetSize(1280.f, 720.f);
	m_Back->SetZOrder(10);

	// 결과창
	m_ResultFrame = CreateWidget<CImageWidget>("ResultFrame");

	m_ResultFrame->SetTexture("ResultFrame", TEXT("Texture/UI/ResultFrame.bmp"));
	m_ResultFrame->SetColorKey(255, 0, 255);
	m_ResultFrame->SetSize(1034.f, 580.f);
	m_ResultFrame->SetPos(123.f, 35.5f);
	m_ResultFrame->SetZOrder(11);

	m_ResultFrameText = CreateWidget<CText>("ResultFrameText");

	m_ResultFrameText->SetText(TEXT("결과"));
	m_ResultFrameText->SetPos(600, 60.f);
	m_ResultFrameText->SetTextColor(255, 255, 255);
	m_ResultFrameText->SetZOrder(12);


	// 플레이어 
	CText* PlayerTypeText = CreateWidget<CText>("PlayerTypeText");

	if (g_PlayerSelect == 0)
	{
		PlayerTypeText->SetText(TEXT("안토네오 벨파에제"));

		CImageWidget* PlayerImage = CreateWidget<CImageWidget>("AntonioImage");

		PlayerImage->SetTexture("AntonioImage", TEXT("Texture/UI/Antonio.bmp"));
		PlayerImage->SetColorKey(255, 0, 255);
		PlayerImage->SetSize(35.f, 40.f);
		PlayerImage->SetPos(550.f, 160.f);
		PlayerImage->SetZOrder(12);
	}

	else if (g_PlayerSelect == 1)
	{
		PlayerTypeText->SetText(TEXT("이멜다 벨파에제"));

		CImageWidget* PlayerImage = CreateWidget<CImageWidget>("ImeldaImage");

		PlayerImage->SetTexture("ImeldaImage", TEXT("Texture/UI/Imelda.bmp"));
		PlayerImage->SetColorKey(255, 0, 255);
		PlayerImage->SetSize(35.f, 40.f);
		PlayerImage->SetPos(550.f, 160.f);
		PlayerImage->SetZOrder(12);
	}

	PlayerTypeText->SetPos(600, 170.f);
	PlayerTypeText->SetTextColor(255, 255, 0);
	PlayerTypeText->SetFont("SmallFont");
	PlayerTypeText->SetZOrder(12);

	// 생존 시간
	m_SurvivalTimeText = CreateWidget<CText>("SurvivalTime");

	m_SurvivalTimeText->SetText(TEXT("생존 시간: "));
	m_SurvivalTimeText->SetPos(200.5f, 260.f);
	m_SurvivalTimeText->SetTextColor(255, 255, 255);
	m_SurvivalTimeText->SetFont("SmallFont");
	m_SurvivalTimeText->SetZOrder(12);

	CText* SurvivalTimeText = CreateWidget<CText>("SurvivalTimeText");

	float SurvivalTime = m_Scene->GetPassedTime();

	TCHAR	FileName3[MAX_PATH] = {};
	wsprintf(FileName3, TEXT("%d%d : %d%d"), (int)SurvivalTime / 600, (int)SurvivalTime / 60, ((int)SurvivalTime % 60) / 10, (int)SurvivalTime % 10);

	SurvivalTimeText->SetText(FileName3);
	SurvivalTimeText->SetPos(800.f, 260.f);
	SurvivalTimeText->SetTextColor(255, 255, 255);
	SurvivalTimeText->SetFont("SmallFont");
	SurvivalTimeText->SetZOrder(12);

	// 도달 레벨
	m_ReachedLevelText = CreateWidget<CText>("ReachedLevel");

	m_ReachedLevelText->SetText(TEXT("도달한 레벨: "));
	m_ReachedLevelText->SetPos(200.5f, 380.f);
	m_ReachedLevelText->SetTextColor(255, 255, 255);
	m_ReachedLevelText->SetFont("SmallFont");
	m_ReachedLevelText->SetZOrder(12);

	CText* ReachedLevelText = CreateWidget<CText>("ReachedLevelText");

	TCHAR	FileName1[MAX_PATH] = {};
	wsprintf(FileName1, TEXT("%d"), m_Scene->GetPlayer()->GetPlayerLevel());

	ReachedLevelText->SetText(FileName1);
	ReachedLevelText->SetPos(800.f, 380.f);
	ReachedLevelText->SetTextColor(255, 255, 255);
	ReachedLevelText->SetFont("SmallFont");
	ReachedLevelText->SetZOrder(12);

	// 몬스터 처치 수
	m_MonsterKillCountText = CreateWidget<CText>("SurvivalTime");

	m_MonsterKillCountText->SetText(TEXT("처치한 적: "));
	m_MonsterKillCountText->SetPos(200.5f, 500.f);
	m_MonsterKillCountText->SetTextColor(255, 255, 255);
	m_MonsterKillCountText->SetFont("SmallFont");
	m_MonsterKillCountText->SetZOrder(12);

	CText* MonsterKillCountText = CreateWidget<CText>("MonsterKillCountText");

	TCHAR	FileName2[MAX_PATH] = {};
	wsprintf(FileName2, TEXT("%d"), m_Scene->GetPlayer()->GetKillCount());

	MonsterKillCountText->SetText(FileName2);
	MonsterKillCountText->SetPos(800.f, 500.f);
	MonsterKillCountText->SetTextColor(255, 255, 255);
	MonsterKillCountText->SetFont("SmallFont");
	MonsterKillCountText->SetZOrder(12);

	// 결과창 나가기 버튼
	m_ResultExitButton = CreateWidget<CButton>("ResultExitButton");

	m_ResultExitButton->SetTexture("ResultExitButton", TEXT("Texture/UI/StartButton.bmp"));
	m_ResultExitButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(226.f, 68.f));
	m_ResultExitButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(0.f, 0.f), Vector2(226.f, 68.f));
	m_ResultExitButton->SetButtonStateData(EButton_State::Click, Vector2(0.f, 0.f), Vector2(226.f, 68.f));
	m_ResultExitButton->SetButtonStateData(EButton_State::Disable, Vector2(0.f, 0.f), Vector2(226.f, 68.f));
	m_ResultExitButton->SetColorKey(255, 0, 255);

	m_ResultExitButton->SetSound(EButton_Sound_State::Click, "OptionButton");

	m_ResultExitButton->SetPos(528.f, 624.5f);
	m_ResultExitButton->SetZOrder(11);

	m_ResultExitButton->SetCallback<CGamePauseWindow>(EButton_Sound_State::Click,
		this, &CGamePauseWindow::ResultExitButtonCallback);

	m_ResultExitButtonText = CreateWidget<CText>("ResultExitButtonText");

	m_ResultExitButtonText->SetText(TEXT("완료"));
	m_ResultExitButtonText->SetPos(600.5f, 630.5f);
	m_ResultExitButtonText->SetTextColor(255, 255, 255);
	m_ResultExitButtonText->SetZOrder(12);
};

void CGamePauseWindow::ResultExitButtonCallback()
{
	// 멈췄던 시간 다시 돌림
	CGameManager::GetInst()->SetTimeScale(1.f);

	CInput::GetInst()->ClearCallback();
	CSceneManager::GetInst()->CreateScene<CStartScene>();
}