

#include "StartWindow.h"
#include "Button.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../GameManager.h"
#include "../Scene/MainScene.h"
#include "../Scene/EditScene.h"
#include "../Scene/SceneManager.h"
#include "../Input.h"
#include "ImageWidget.h"
#include "CheckBox.h"
#include "IconDrag.h"
#include "Text.h"	
#include "Number.h"
#include "../GameManager.h"
#include "SoundControlBar.h"

CStartWindow::CStartWindow()
{
}

CStartWindow::~CStartWindow()
{
}


bool CStartWindow::Init()
{
	if (!CWidgetWindow::Init())
		return false;

	m_Scene->GetSceneResource()->LoadSound("UI", "StartButton", false,
		"sfx_sounds_pause7_in.ogg");
	m_Scene->GetSceneResource()->LoadSound("UI", "OptionButton", false,
		"sfx_sounds_pause7_out.ogg");

	m_Scene->GetSceneResource()->SetVolume(20);

	SetSize(1280.f, 720.f);

	// 기본 배경
	CImageWidget* Back = CreateWidget<CImageWidget>("Back");

	Back->SetTexture("StartBack", TEXT("Texture/intro2.bmp"));

	Back->SetSize(1280.f, 799.f);
	Back->SetPos(0.f, 0.f);

	// 스타트 버튼
	m_StartButton = CreateWidget<CButton>("StartButton");

	m_StartButton->SetTexture("StartButton", TEXT("Texture/UI/StartButton.bmp"));
	m_StartButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(226.f, 68.f));
	m_StartButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(0.f, 0.f), Vector2(226.f, 68.f));
	m_StartButton->SetButtonStateData(EButton_State::Click, Vector2(0.f, 0.f), Vector2(226.f, 68.f));
	m_StartButton->SetButtonStateData(EButton_State::Disable, Vector2(0.f, 0.f), Vector2(226.f, 68.f));
	m_StartButton->SetColorKey(255, 0, 255);

	m_StartButton->SetSound(EButton_Sound_State::Click, "StartButton");

	m_StartButton->SetPos(528.f, 475.f);
	m_StartButton->SetZOrder(1);

	m_StartButton->SetCallback<CStartWindow>(EButton_Sound_State::Click,
		this, &CStartWindow::StartButtonCallback);

	m_StartButtonText = CreateWidget<CText>("StartButtonText");

	m_StartButtonText->SetText(TEXT("시작"));
	m_StartButtonText->SetPos(595.f, 481.f);
	m_StartButtonText->SetTextColor(255, 255, 255);
	m_StartButtonText->SetZOrder(2);

#ifdef _DEBUG

	// Edit 버튼
	CButton* EditButton = CreateWidget<CButton>("EditButton");

	EditButton->SetTexture("EditButton", TEXT("Texture/UI/StartButton.bmp"));
	EditButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(226.f, 68.f));
	EditButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(0.f, 0.f), Vector2(226.f, 68.f));
	EditButton->SetButtonStateData(EButton_State::Click, Vector2(0.f, 0.f), Vector2(226.f, 68.f));
	EditButton->SetButtonStateData(EButton_State::Disable, Vector2(0.f, 0.f), Vector2(226.f, 68.f));
	EditButton->SetColorKey(255, 0, 255);

	EditButton->SetSound(EButton_Sound_State::Click, "OptionButton");

	EditButton->SetPos(240.f, 481.f);
	EditButton->SetZOrder(1);

	EditButton->SetCallback<CStartWindow>(EButton_Sound_State::Click,
		this, &CStartWindow::EditButtonCallback);

	CText* EditButtonText = CreateWidget<CText>("EditButtonText");

	EditButtonText->SetText(TEXT("Map Editor"));
	EditButtonText->SetPos(275.f, 491.f);
	EditButtonText->SetFont("MiddleFont");
	EditButtonText->SetTextColor(255, 255, 255);
	EditButtonText->SetZOrder(2);

#endif // _DEBUG

	// 나가기 버튼
	m_ExitButton = CreateWidget<CButton>("ExitButton");

	m_ExitButton->SetTexture("ExitButton", TEXT("Texture/UI/ExitButton.bmp"));
	m_ExitButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(113.f, 66.f));
	m_ExitButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(0.f, 0.f), Vector2(113.f, 66.f));
	m_ExitButton->SetButtonStateData(EButton_State::Click, Vector2(0.f, 0.f), Vector2(113.f, 66.f));
	m_ExitButton->SetButtonStateData(EButton_State::Disable, Vector2(0.f, 0.f), Vector2(113.f, 66.f));
	m_ExitButton->SetColorKey(255, 0, 255);

	m_ExitButton->SetSound(EButton_Sound_State::Click, "OptionButton");

	m_ExitButton->SetPos(346.f, 5.f);
	m_ExitButton->SetZOrder(1);

	m_ExitButton->SetCallback<CStartWindow>(EButton_Sound_State::Click,
		this, &CStartWindow::EndButtonCallback);

	m_ExitButtonText = CreateWidget<CText>("ExitButtonText");

	m_ExitButtonText->SetText(TEXT("나가기"));
	m_ExitButtonText->SetPos(373.f, 25.f);
	m_ExitButtonText->SetTextColor(255, 255, 255);
	m_ExitButtonText->SetFont("SmallFont");
	m_ExitButtonText->SetZOrder(2);

	// 옵션 버튼
	m_OptionButton = CreateWidget<CButton>("OptionButton");

	m_OptionButton->SetTexture("OptionButton", TEXT("Texture/UI/OptionButton.bmp"));
	m_OptionButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(113.f, 66.f));
	m_OptionButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(0.f, 0.f), Vector2(113.f, 66.f));
	m_OptionButton->SetButtonStateData(EButton_State::Click, Vector2(0.f, 0.f), Vector2(113.f, 66.f));
	m_OptionButton->SetButtonStateData(EButton_State::Disable, Vector2(0.f, 0.f), Vector2(113.f, 66.f));
	m_OptionButton->SetColorKey(255, 0, 255);

	m_OptionButton->SetSound(EButton_Sound_State::Click, "OptionButton");

	m_OptionButton->SetPos(820.f, 5.f);
	m_OptionButton->SetZOrder(1);

	m_OptionButton->SetCallback<CStartWindow>(EButton_Sound_State::Click,
		this, &CStartWindow::OptionButtonCallback);

	m_OptionButtonText = CreateWidget<CText>("OptionButtonText");

	m_OptionButtonText->SetText(TEXT("옵션"));
	m_OptionButtonText->SetPos(857.f, 25.f);
	m_OptionButtonText->SetTextColor(255, 255, 255);
	m_OptionButtonText->SetFont("SmallFont");
	m_OptionButtonText->SetZOrder(2);


	return true;
}

void CStartWindow::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
}

void CStartWindow::StartButtonCallback()
{
	/*CInput::GetInst()->ClearCallback();
	CSceneManager::GetInst()->CreateScene<CMainScene>();*/

	// 나가기 버튼 안보이게 하기.
	m_ExitButton->SetEnable(false);
	m_ExitButtonText->SetEnable(false);

	// 옵션 나가기 버튼
	m_CharacterSelectExitButton = CreateWidget<CButton>("OptionExitButton");

	m_CharacterSelectExitButton->SetTexture("OptionExitButton", TEXT("Texture/UI/ExitButton.bmp"));
	m_CharacterSelectExitButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(113.f, 66.f));
	m_CharacterSelectExitButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(0.f, 0.f), Vector2(113.f, 66.f));
	m_CharacterSelectExitButton->SetButtonStateData(EButton_State::Click, Vector2(0.f, 0.f), Vector2(113.f, 66.f));
	m_CharacterSelectExitButton->SetButtonStateData(EButton_State::Disable, Vector2(0.f, 0.f), Vector2(113.f, 66.f));
	m_CharacterSelectExitButton->SetColorKey(255, 0, 255);

	m_CharacterSelectExitButton->SetSound(EButton_Sound_State::Click, "OptionButton");

	m_CharacterSelectExitButton->SetPos(820.f, 5.f);
	m_CharacterSelectExitButton->SetZOrder(3);

	m_CharacterSelectExitButton->SetCallback<CStartWindow>(EButton_Sound_State::Click,
		this, &CStartWindow::CharacterSelectExitCallback);

	m_CharacterSelectExitButtonText = CreateWidget<CText>("OptionExitButtonText");

	m_CharacterSelectExitButtonText->SetText(TEXT("뒤로"));
	m_CharacterSelectExitButtonText->SetPos(857.f, 25.f);
	m_CharacterSelectExitButtonText->SetTextColor(255, 255, 255);
	m_CharacterSelectExitButtonText->SetFont("SmallFont");
	m_CharacterSelectExitButtonText->SetZOrder(4);

	// 캐릭터 선택창
	m_CharacterSelectFrame = CreateWidget<CImageWidget>("CharacterSelectFrame");

	m_CharacterSelectFrame->SetTexture("CharacterSelectFrame", TEXT("Texture/UI/OptionFrame.bmp"));
	m_CharacterSelectFrame->SetColorKey(255, 0, 255);
	m_CharacterSelectFrame->SetSize(599.f, 547.f);
	m_CharacterSelectFrame->SetPos(340.f, 75.f);
	m_CharacterSelectFrame->SetZOrder(3);

	m_CharacterSelectFrameText = CreateWidget<CText>("StartButtonText");

	m_CharacterSelectFrameText->SetText(TEXT("캐릭터 선택"));
	m_CharacterSelectFrameText->SetPos(545.f, 90.f);
	m_CharacterSelectFrameText->SetTextColor(255, 255, 255);
	m_CharacterSelectFrameText->SetZOrder(4);

	// 안토니오 
	m_AntonioSlot = CreateWidget<CButton>("AntonioSlot");

	m_AntonioSlot->SetTexture("AntonioSlot", TEXT("Texture/UI/AntonioSlot.bmp"));
	m_AntonioSlot->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(129.f, 129.f));
	m_AntonioSlot->SetButtonStateData(EButton_State::MouseHovered, Vector2(0.f, 0.f), Vector2(129.f, 129.f));
	m_AntonioSlot->SetButtonStateData(EButton_State::Click, Vector2(0.f, 0.f), Vector2(129.f, 129.f));
	m_AntonioSlot->SetButtonStateData(EButton_State::Disable, Vector2(0.f, 0.f), Vector2(129.f, 129.f));
	m_AntonioSlot->SetColorKey(255, 0, 255);
	m_AntonioSlot->SetSize(129.f, 129.f);
	m_AntonioSlot->SetPos(355.f, 158.f);
	m_AntonioSlot->SetZOrder(4);

	m_AntonioSlot->SetCallback<CStartWindow>(EButton_Sound_State::Click,
		this, &CStartWindow::AntonioButtonCallback);

	m_AntonioSlotText = CreateWidget<CText>("AntonioSlotText");

	m_AntonioSlotText->SetText(TEXT("안토니오"));
	m_AntonioSlotText->SetPos(360.f, 163.f);
	m_AntonioSlotText->SetTextColor(255, 255, 255);
	m_AntonioSlotText->SetFont("SmallFont");
	m_AntonioSlotText->SetZOrder(5);

	// 이멜다 
	m_ImeldaSlot = CreateWidget<CButton>("ImeldaSlot");

	m_ImeldaSlot->SetTexture("ImeldaSlot", TEXT("Texture/UI/ImeldaSlot.bmp"));
	m_ImeldaSlot->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(129.f, 129.f));
	m_ImeldaSlot->SetButtonStateData(EButton_State::MouseHovered, Vector2(0.f, 0.f), Vector2(129.f, 129.f));
	m_ImeldaSlot->SetButtonStateData(EButton_State::Click, Vector2(0.f, 0.f), Vector2(129.f, 129.f));
	m_ImeldaSlot->SetButtonStateData(EButton_State::Disable, Vector2(0.f, 0.f), Vector2(129.f, 129.f));
	m_ImeldaSlot->SetColorKey(255, 0, 255);
	m_ImeldaSlot->SetSize(129.f, 129.f);
	m_ImeldaSlot->SetPos(497.f, 158.f);
	m_ImeldaSlot->SetZOrder(4);

	m_ImeldaSlot->SetCallback<CStartWindow>(EButton_Sound_State::Click,
		this, &CStartWindow::ImeldaButtonCallback);

	m_ImeldaSlotText = CreateWidget<CText>("ImeldaSlot");

	m_ImeldaSlotText->SetText(TEXT("이멜다"));
	m_ImeldaSlotText->SetPos(502.f, 163.f);
	m_ImeldaSlotText->SetTextColor(255, 255, 255);
	m_ImeldaSlotText->SetFont("SmallFont");
	m_ImeldaSlotText->SetZOrder(5);


	// 캐릭터 설명
	m_CharacterDescription = CreateWidget<CImageWidget>("AntonioDescription");

	m_CharacterDescription->SetTexture("AntonioDescription", TEXT("Texture/UI/AntonioDescription.bmp"));
	m_CharacterDescription->SetColorKey(255, 0, 255);
	m_CharacterDescription->SetSize(576.f, 121.f);
	m_CharacterDescription->SetPos(351.f, 490.f);
	m_CharacterDescription->SetZOrder(5);

	m_CharacterDescriptionText1 = CreateWidget<CText>("AntonioDescriptionText");

	m_CharacterDescriptionText1->SetText(TEXT("안토니오 벨파에제"));
	m_CharacterDescriptionText1->SetPos(356.f, 494.f);
	m_CharacterDescriptionText1->SetTextColor(255, 255, 255);
	m_CharacterDescriptionText1->SetFont("SmallFont");
	m_CharacterDescriptionText1->SetZOrder(6);

	// 캐릭터 선택 버튼
	m_CharacterSelectButton = CreateWidget<CButton>("CharacterSelectButton");

	m_CharacterSelectButton->SetTexture("CharacterSelectButton", TEXT("Texture/UI/NextButton.bmp"));
	m_CharacterSelectButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(113.f, 66.f));
	m_CharacterSelectButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(0.f, 0.f), Vector2(113.f, 66.f));
	m_CharacterSelectButton->SetButtonStateData(EButton_State::Click, Vector2(0.f, 0.f), Vector2(113.f, 66.f));
	m_CharacterSelectButton->SetButtonStateData(EButton_State::Disable, Vector2(0.f, 0.f), Vector2(113.f, 66.f));
	m_CharacterSelectButton->SetColorKey(255, 0, 255);
	m_CharacterSelectButton->SetSize(113.f, 66.f);
	m_CharacterSelectButton->SetPos(800.f, 538.f);
	m_CharacterSelectButton->SetZOrder(6);

	m_CharacterSelectButton->SetCallback<CStartWindow>(EButton_Sound_State::Click,
		this, &CStartWindow::CharacterSelectCallback);

	m_CharacterSelectButtonText = CreateWidget<CText>("CharacterSelectButtonText");

	m_CharacterSelectButtonText->SetText(TEXT("시작"));
	m_CharacterSelectButtonText->SetPos(839.f, 558.f);
	m_CharacterSelectButtonText->SetTextColor(255, 255, 255);
	m_CharacterSelectButtonText->SetFont("SmallFont");
	m_CharacterSelectButtonText->SetZOrder(7);

	g_PlayerSelect = 0;

	// 캐릭터 능력 설명
	m_AbilityText1 = CreateWidget<CText>("AntonioAbilityText");

	m_AbilityText1->SetText(TEXT("매 10레벨마다 피해량이"));
	m_AbilityText1->SetPos(545.f, 510.f);
	m_AbilityText1->SetTextColor(255, 255, 255);
	m_AbilityText1->SetFont("SmallFont");
	m_AbilityText1->SetZOrder(6);

	m_AbilityText2 = CreateWidget<CText>("AntonioAbilityText");

	m_AbilityText2->SetText(TEXT("10% 증가합니다. (최대"));
	m_AbilityText2->SetPos(545.f, 530.f);
	m_AbilityText2->SetTextColor(255, 255, 255);
	m_AbilityText2->SetFont("SmallFont");
	m_AbilityText2->SetZOrder(6);

	m_AbilityText3 = CreateWidget<CText>("AntonioAbilityText");

	m_AbilityText3->SetText(TEXT("+50%)"));
	m_AbilityText3->SetPos(545.f, 550.f);
	m_AbilityText3->SetTextColor(255, 255, 255);
	m_AbilityText3->SetFont("SmallFont");
	m_AbilityText3->SetZOrder(6);
}

void CStartWindow::EndButtonCallback()
{
	CGameManager::GetInst()->Exit();
}

void CStartWindow::EditButtonCallback()
{
	CInput::GetInst()->ClearCallback();
	CSceneManager::GetInst()->CreateScene<CEditScene>();
}

void CStartWindow::OptionButtonCallback()
{
	// 나가기 버튼 안보이게 하기.
	m_ExitButton->SetEnable(false);
	m_ExitButtonText->SetEnable(false);

	// 옵션 나가기 버튼
	m_OptionExitButton = CreateWidget<CButton>("OptionExitButton");

	m_OptionExitButton->SetTexture("OptionExitButton", TEXT("Texture/UI/ExitButton.bmp"));
	m_OptionExitButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(113.f, 66.f));
	m_OptionExitButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(0.f, 0.f), Vector2(113.f, 66.f));
	m_OptionExitButton->SetButtonStateData(EButton_State::Click, Vector2(0.f, 0.f), Vector2(113.f, 66.f));
	m_OptionExitButton->SetButtonStateData(EButton_State::Disable, Vector2(0.f, 0.f), Vector2(113.f, 66.f));
	m_OptionExitButton->SetColorKey(255, 0, 255);

	m_OptionExitButton->SetSound(EButton_Sound_State::Click, "OptionButton");

	m_OptionExitButton->SetPos(820.f, 5.f);
	m_OptionExitButton->SetZOrder(3);

	m_OptionExitButton->SetCallback<CStartWindow>(EButton_Sound_State::Click,
		this, &CStartWindow::OptionExitButtonCallback);

	m_OptionExitButtonText = CreateWidget<CText>("OptionExitButtonText");

	m_OptionExitButtonText->SetText(TEXT("뒤로"));
	m_OptionExitButtonText->SetPos(857.f, 25.f);
	m_OptionExitButtonText->SetTextColor(255, 255, 255);
	m_OptionExitButtonText->SetFont("SmallFont");
	m_OptionExitButtonText->SetZOrder(4);


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

}

void CStartWindow::OptionExitButtonCallback()
{
	// 나가기 버튼 다시 보이게 하기.
	m_ExitButton->SetEnable(true);
	m_ExitButtonText->SetEnable(true);

	// 뒤로 버튼 지우기.
	m_OptionExitButton->SetActive(false);
	m_OptionExitButtonText->SetActive(false);

	// Sound 변동사항 적용하기
	m_Scene->GetSceneResource()->SetVolume("BGM", g_MusicVolume);
	m_Scene->GetSceneResource()->SetVolume("UI", g_SoundVolume);
	m_Scene->GetSceneResource()->SetVolume("Effect", g_SoundVolume);

	// 옵션창 지우기
	m_OptionFrame->SetActive(false);
	m_OptionFrameText->SetActive(false);
	m_SoundControlText->SetActive(false);
	m_MusicControlText->SetActive(false);
	m_SoundControlBar->SetActive(false);
	m_MusicControlBar->SetActive(false);
}

void CStartWindow::AntonioButtonCallback()
{
	if (m_CharacterDescription)
		m_CharacterDescription->SetActive(false);
	if (m_CharacterDescriptionText1)
		m_CharacterDescriptionText1->SetActive(false);
	if (m_AbilityText1)
		m_AbilityText1->SetActive(false);
	if (m_AbilityText2)
		m_AbilityText2->SetActive(false);
	if (m_AbilityText3)
		m_AbilityText3->SetActive(false);

	m_CharacterDescription = CreateWidget<CImageWidget>("AntonioDescription");

	m_CharacterDescription->SetTexture("AntonioDescription", TEXT("Texture/UI/AntonioDescription.bmp"));
	m_CharacterDescription->SetColorKey(255, 0, 255);
	m_CharacterDescription->SetSize(576.f, 121.f);
	m_CharacterDescription->SetPos(351.f, 490.f);
	m_CharacterDescription->SetZOrder(4);

	m_CharacterDescriptionText1 = CreateWidget<CText>("AntonioDescriptionText");

	m_CharacterDescriptionText1->SetText(TEXT("안토니오 벨파에제"));
	m_CharacterDescriptionText1->SetPos(356.f, 494.f);
	m_CharacterDescriptionText1->SetTextColor(255, 255, 255);
	m_CharacterDescriptionText1->SetFont("SmallFont");
	m_CharacterDescriptionText1->SetZOrder(5);

	m_AbilityText1 = CreateWidget<CText>("AntonioAbilityText");

	m_AbilityText1->SetText(TEXT("매 10레벨마다 피해량이"));
	m_AbilityText1->SetPos(545.f, 510.f);
	m_AbilityText1->SetTextColor(255, 255, 255);
	m_AbilityText1->SetFont("SmallFont");
	m_AbilityText1->SetZOrder(6);

	m_AbilityText2 = CreateWidget<CText>("AntonioAbilityText");

	m_AbilityText2->SetText(TEXT("10% 증가합니다. (최대"));
	m_AbilityText2->SetPos(545.f, 530.f);
	m_AbilityText2->SetTextColor(255, 255, 255);
	m_AbilityText2->SetFont("SmallFont");
	m_AbilityText2->SetZOrder(6);

	m_AbilityText3 = CreateWidget<CText>("AntonioAbilityText");

	m_AbilityText3->SetText(TEXT("+50%)"));
	m_AbilityText3->SetPos(545.f, 550.f);
	m_AbilityText3->SetTextColor(255, 255, 255);
	m_AbilityText3->SetFont("SmallFont");
	m_AbilityText3->SetZOrder(6);

	//
	g_PlayerSelect = 0;
}

void CStartWindow::ImeldaButtonCallback()
{
	if (m_CharacterDescription)
		m_CharacterDescription->SetActive(false);
	if (m_CharacterDescriptionText1)
		m_CharacterDescriptionText1->SetActive(false);
	if (m_AbilityText1)
		m_AbilityText1->SetActive(false);
	if (m_AbilityText2)
		m_AbilityText2->SetActive(false);
	if (m_AbilityText3)
		m_AbilityText3->SetActive(false);

	m_CharacterDescription = CreateWidget<CImageWidget>("ImeldaDescription");

	m_CharacterDescription->SetTexture("ImeldaDescription", TEXT("Texture/UI/ImeldaDescription.bmp"));
	m_CharacterDescription->SetColorKey(255, 0, 255);
	m_CharacterDescription->SetSize(576.f, 121.f);
	m_CharacterDescription->SetPos(351.f, 490.f);
	m_CharacterDescription->SetZOrder(4);

	m_CharacterDescriptionText1 = CreateWidget<CText>("AntonioDescriptionText");

	m_CharacterDescriptionText1->SetText(TEXT("이멜다 벨파에제"));
	m_CharacterDescriptionText1->SetPos(356.f, 494.f);
	m_CharacterDescriptionText1->SetTextColor(255, 255, 255);
	m_CharacterDescriptionText1->SetFont("SmallFont");
	m_CharacterDescriptionText1->SetZOrder(5);

	m_AbilityText1 = CreateWidget<CText>("AntonioAbilityText");

	m_AbilityText1->SetText(TEXT("매 5레벨마다 10%의"));
	m_AbilityText1->SetPos(545.f, 510.f);
	m_AbilityText1->SetTextColor(255, 255, 255);
	m_AbilityText1->SetFont("SmallFont");
	m_AbilityText1->SetZOrder(5);

	m_AbilityText2 = CreateWidget<CText>("AntonioAbilityText");

	m_AbilityText2->SetText(TEXT("경험치를 추가"));
	m_AbilityText2->SetPos(545.f, 530.f);
	m_AbilityText2->SetTextColor(255, 255, 255);
	m_AbilityText2->SetFont("SmallFont");
	m_AbilityText2->SetZOrder(5);

	m_AbilityText3 = CreateWidget<CText>("AntonioAbilityText");

	m_AbilityText3->SetText(TEXT("획득합니다. (최대 +30%)"));
	m_AbilityText3->SetPos(545.f, 550.f);
	m_AbilityText3->SetTextColor(255, 255, 255);
	m_AbilityText3->SetFont("SmallFont");
	m_AbilityText3->SetZOrder(5);

	//
	g_PlayerSelect = 1;
}

void CStartWindow::CharacterSelectExitCallback()
{
	// 나가기 버튼 다시 보이게 하기.
	m_ExitButton->SetEnable(true);
	m_ExitButtonText->SetEnable(true);

	// 뒤로 버튼 지우기.
	m_CharacterSelectExitButton->SetActive(false);
	m_CharacterSelectExitButtonText->SetActive(false);

	// 캐릭터 선택창 지우기
	if (m_CharacterSelectFrame)
		m_CharacterSelectFrame->SetActive(false);
	if (m_CharacterSelectFrameText)
		m_CharacterSelectFrameText->SetActive(false);
	if (m_AntonioSlot)
		m_AntonioSlot->SetActive(false);
	if (m_ImeldaSlot)
		m_ImeldaSlot->SetActive(false);
	if (m_AntonioSlotText)
		m_AntonioSlotText->SetActive(false);
	if (m_ImeldaSlotText)
		m_ImeldaSlotText->SetActive(false);
	if (m_CharacterDescription)
		m_CharacterDescription->SetActive(false);
	if (m_CharacterDescriptionText1)
		m_CharacterDescriptionText1->SetActive(false);
	if (m_AbilityText1)
		m_AbilityText1->SetActive(false);
	if (m_AbilityText2)
		m_AbilityText2->SetActive(false);
	if (m_AbilityText3)
		m_AbilityText3->SetActive(false);
	if (m_CharacterSelectButton)
		m_CharacterSelectButton->SetActive(false);
	if (m_CharacterSelectButtonText)
		m_CharacterSelectButtonText->SetActive(false);
}

void CStartWindow::CharacterSelectCallback()
{
	CInput::GetInst()->ClearCallback();
	CSceneManager::GetInst()->CreateScene<CMainScene>();
}
