
#include "GameOverWindow.h"
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

CGameOverWindow::CGameOverWindow()
{
}

CGameOverWindow::~CGameOverWindow()
{
}

bool CGameOverWindow::Init()
{
	if (!CWidgetWindow::Init())
		return false;
	
	//
	CInput::GetInst()->ClearCallback();

	m_Scene->GetSceneResource()->LoadSound("UI", "StartButton", false,
		"sfx_sounds_pause7_in.ogg");
	m_Scene->GetSceneResource()->LoadSound("UI", "OptionButton", false,
		"sfx_sounds_pause7_out.ogg");
	m_Scene->GetSceneResource()->LoadSound("UI", "GameOver", false, 
		"VS_GameOver_v02-01.ogg");

	SetSize(1280.f, 720.f);

	// 배경음악 일시적으로 끄기
	m_Scene->GetSceneResource()->SetVolume("BGM", 0);

	// GameOver Sound
	m_Scene->GetSceneResource()->SoundPlay("GameOver");

	// GameOver
	m_GameOverImage = CreateWidget<CImageWidget>("GameOver");

	m_GameOverImage->SetTexture("GameOver", TEXT("Texture/UI/GameOver.bmp"));
	m_GameOverImage->SetColorKey(255, 0, 255);
	m_GameOverImage->SetSize(332.f, 133.f);
	m_GameOverImage->SetPos(474.f, 140.f);
	m_GameOverImage->SetZOrder(0);

	// 나가기 버튼
	m_GameOverExitButton = CreateWidget<CButton>("GameExitButton");

	m_GameOverExitButton->SetTexture("GameExitButton", TEXT("Texture/UI/GameExitButton.bmp"));
	m_GameOverExitButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(226.f, 68.f));
	m_GameOverExitButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(0.f, 0.f), Vector2(226.f, 68.f));
	m_GameOverExitButton->SetButtonStateData(EButton_State::Click, Vector2(0.f, 0.f), Vector2(226.f, 68.f));
	m_GameOverExitButton->SetButtonStateData(EButton_State::Disable, Vector2(0.f, 0.f), Vector2(226.f, 68.f));
	m_GameOverExitButton->SetColorKey(255, 0, 255);

	m_GameOverExitButton->SetSound(EButton_Sound_State::Click, "OptionButton");

	m_GameOverExitButton->SetPos(527.f, 600.f);
	m_GameOverExitButton->SetZOrder(1);

	m_GameOverExitButton->SetCallback<CGameOverWindow>(EButton_Sound_State::Click,
		this, &CGameOverWindow::BattleExitButtonCallback);

	m_GameOverExitText = CreateWidget<CText>("GameOverExitText");

	m_GameOverExitText->SetText(TEXT("나가기"));
	m_GameOverExitText->SetPos(597.f, 612.f);
	m_GameOverExitText->SetTextColor(255, 255, 255);
	m_GameOverExitText->SetFont("MiddleFont");
	m_GameOverExitText->SetZOrder(2);


	return true;
}

void CGameOverWindow::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
}

void CGameOverWindow::BattleExitButtonCallback()
{
	CInput::GetInst()->ClearCallback();

	// 멈췄던 시간 다시 돌림
	CGameManager::GetInst()->SetTimeScale(1.f);

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

	m_ResultExitButton->SetCallback<CGameOverWindow>(EButton_Sound_State::Click,
		this, &CGameOverWindow::ResultExitButtonCallback);

	m_ResultExitButtonText = CreateWidget<CText>("ResultExitButtonText");

	m_ResultExitButtonText->SetText(TEXT("완료"));
	m_ResultExitButtonText->SetPos(600.5f, 630.5f);
	m_ResultExitButtonText->SetTextColor(255, 255, 255);
	m_ResultExitButtonText->SetZOrder(12);
};

void CGameOverWindow::ResultExitButtonCallback()
{
	CInput::GetInst()->ClearCallback();
	CSceneManager::GetInst()->CreateScene<CStartScene>();
}