
#include "TreasureBoxWindow.h"
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

CTreasureBoxWindow::CTreasureBoxWindow()
{
}

CTreasureBoxWindow::~CTreasureBoxWindow()
{
}

bool CTreasureBoxWindow::Init()
{
	if (!CWidgetWindow::Init())
		return false;

	CGameManager::GetInst()->SetTimeScale(0.f);

	SetPos(0.f, 0.f);
	SetSize(1280.f, 720.f);

	// 프레임 생성
	m_TreasureBoxFrame = CreateWidget<CImageWidget>("TreasureBoxFrame");
	m_TreasureBoxFrame->SetZOrder(0);
	m_TreasureBoxFrame->SetTexture("TreasureBoxFrame", TEXT("Texture/UI/TreasureBoxFrame.bmp"));
	m_TreasureBoxFrame->SetColorKey(255, 0, 255);
	m_TreasureBoxFrame->SetSize(462.f, 619.f);
	m_TreasureBoxFrame->SetPos(409.f, 50.f);

	// 프레임 텍스트 
	m_TreasureBoxButtonText = CreateWidget<CText>("Text");

	m_TreasureBoxButtonText->SetText(TEXT("보물 발견!"));
	m_TreasureBoxButtonText->SetPos(550.f, 80.f);
	m_TreasureBoxButtonText->SetTextColor(255, 255, 255);
	m_TreasureBoxButtonText->SetZOrder(3);

	// 보물상자 생성.
	m_TreasureBox = CreateWidget<CImageWidget>("TreasureBoxIdle");
	m_TreasureBox->SetZOrder(1);
	m_TreasureBox->SetTexture("TreasureBoxIdle", TEXT("Texture/UI/TreasureBoxIdle.bmp"));
	m_TreasureBox->SetColorKey(255, 0, 255);
	m_TreasureBox->SetSize(182.f, 122.f);
	m_TreasureBox->SetPos(549.f, 380.f);

	// 버튼 생성.
	m_TreasureBoxOpenButton = CreateWidget<CButton>("TreasureBoxOpenButton");
	m_TreasureBoxOpenButton->SetTexture("TreasureBoxOpenButton", TEXT("Texture/UI/TreasureBoxButton.bmp"));
	m_TreasureBoxOpenButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(225.f, 73.f));
	m_TreasureBoxOpenButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(0.f, 0.f), Vector2(225.f, 73.f));
	m_TreasureBoxOpenButton->SetButtonStateData(EButton_State::Click, Vector2(0.f, 0.f), Vector2(225.f, 73.f));
	m_TreasureBoxOpenButton->SetButtonStateData(EButton_State::Disable, Vector2(0.f, 0.f), Vector2(225.f, 73.f));
	m_TreasureBoxOpenButton->SetColorKey(255, 0, 255);

	m_TreasureBoxOpenButton->SetPos(528.f, 520.f);
	m_TreasureBoxOpenButton->SetZOrder(2);

	m_TreasureBoxOpenButton->SetCallback<CTreasureBoxWindow>(EButton_Sound_State::Click,
			this, &CTreasureBoxWindow::TreasureBoxOpenButtonCallback);


	m_TreasureBoxButtonText = CreateWidget<CText>("Text");
	
	m_TreasureBoxButtonText->SetText(TEXT("열기"));
	m_TreasureBoxButtonText->SetPos(600.f, 530.f);
	m_TreasureBoxButtonText->SetTextColor(255, 255, 255);
	m_TreasureBoxButtonText->SetZOrder(3);

	return true;
}

void CTreasureBoxWindow::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
}

void CTreasureBoxWindow::TreasureBoxOpenButtonCallback()
{
	m_TreasureBox->SetZOrder(-1);

	// 보상 동그라미
	CSharedPtr<CImageWidget> BackCircle = CreateWidget<CImageWidget>("BackCircle");
	BackCircle->SetZOrder(2);
	BackCircle->SetTexture("BackCircle", TEXT("Texture/UI/BackCircle.bmp"));
	BackCircle->SetColorKey(255, 0, 255);
	BackCircle->SetSize(67.f, 63.f);
	BackCircle->SetPos(608.5f, 200.f);

	// 보상 출력
	switch (m_Scene->GetPlayer()->TreasureRandom())
	{
	case ETreasure_Result::Garlic:
		m_TreasureResult = CreateWidget<CImageWidget>("GarlicIcon");
		m_TreasureResult->SetZOrder(3);
		m_TreasureResult->SetTexture("GarlicIcon", TEXT("Texture/UI/GarlicIcon.bmp"));
		m_TreasureResult->SetColorKey(255, 0, 255);
		m_TreasureResult->SetSize(37.f, 37.f);
		m_TreasureResult->SetPos(622.f, 210.f);
		break;
	case ETreasure_Result::Bible:
		m_TreasureResult = CreateWidget<CImageWidget>("BibleIcon");
		m_TreasureResult->SetZOrder(3);
		m_TreasureResult->SetTexture("BibleIcon", TEXT("Texture/UI/BibleIcon.bmp"));
		m_TreasureResult->SetColorKey(255, 0, 255);
		m_TreasureResult->SetSize(37.f, 37.f);
		m_TreasureResult->SetPos(622.f, 210.f);
		break;
	case ETreasure_Result::Lightning:
		m_TreasureResult = CreateWidget<CImageWidget>("LightningIcon");
		m_TreasureResult->SetZOrder(3);
		m_TreasureResult->SetTexture("LightningIcon", TEXT("Texture/UI/LightningIcon.bmp"));
		m_TreasureResult->SetColorKey(255, 0, 255);
		m_TreasureResult->SetSize(37.f, 37.f);
		m_TreasureResult->SetPos(622.f, 210.f);
		break;
	case ETreasure_Result::Whip:
		m_TreasureResult = CreateWidget<CImageWidget>("WhipIcon");
		m_TreasureResult->SetZOrder(3);
		m_TreasureResult->SetTexture("WhipIcon", TEXT("Texture/UI/WhipIcon.bmp"));
		m_TreasureResult->SetColorKey(255, 0, 255);
		m_TreasureResult->SetSize(37.f, 37.f);
		m_TreasureResult->SetPos(622.f, 210.f);
		break;
	case ETreasure_Result::EvolvedBible:
		m_TreasureResult = CreateWidget<CImageWidget>("EvolvedBibleIcon");
		m_TreasureResult->SetZOrder(3);
		m_TreasureResult->SetTexture("EvolvedBibleIcon", TEXT("Texture/UI/EvolvedBibleIcon.bmp"));
		m_TreasureResult->SetColorKey(255, 0, 255);
		m_TreasureResult->SetSize(37.f, 37.f);
		m_TreasureResult->SetPos(622.f, 210.f);
		break;
	case ETreasure_Result::AdditionalSkillSpeed:
		m_TreasureResult = CreateWidget<CImageWidget>("AdditionalSkillSpeedIcon");
		m_TreasureResult->SetZOrder(3);
		m_TreasureResult->SetTexture("AdditionalSkillSpeedIcon", TEXT("Texture/UI/AdditionalSkillSpeedIcon.bmp"));
		m_TreasureResult->SetColorKey(255, 0, 255);
		m_TreasureResult->SetSize(37.f, 37.f);
		m_TreasureResult->SetPos(622.f, 210.f);
		break;
	case ETreasure_Result::AdditionalSkillDamage:
		m_TreasureResult = CreateWidget<CImageWidget>("AdditionalSkillDamageIcon");
		m_TreasureResult->SetZOrder(3);
		m_TreasureResult->SetTexture("AdditionalSkillDamageIcon", TEXT("Texture/UI/AdditionalSkillDamageIcon.bmp"));
		m_TreasureResult->SetColorKey(255, 0, 255);
		m_TreasureResult->SetSize(37.f, 37.f);
		m_TreasureResult->SetPos(622.f, 210.f);
		break;
	case ETreasure_Result::AdditionalSkillDuration:
		m_TreasureResult = CreateWidget<CImageWidget>("AdditionalSkillDurationIcon");
		m_TreasureResult->SetZOrder(3);
		m_TreasureResult->SetTexture("AdditionalSkillDurationIcon", TEXT("Texture/UI/AdditionalSkillDurationIcon.bmp"));
		m_TreasureResult->SetColorKey(255, 0, 255);
		m_TreasureResult->SetSize(37.f, 37.f);
		m_TreasureResult->SetPos(622.f, 210.f);
		break;
	case ETreasure_Result::AdditionalSkillProjectile:
		m_TreasureResult = CreateWidget<CImageWidget>("AdditionalSkillProjectileIcon");
		m_TreasureResult->SetZOrder(3);
		m_TreasureResult->SetTexture("AdditionalSkillProjectileIcon", TEXT("Texture/UI/AdditionalSkillProjectileIcon.bmp"));
		m_TreasureResult->SetColorKey(255, 0, 255);
		m_TreasureResult->SetSize(37.f, 37.f);
		m_TreasureResult->SetPos(622.f, 210.f);
		break;
	case ETreasure_Result::Chicken:
		m_TreasureResult = CreateWidget<CImageWidget>("ChickenIcon");
		m_TreasureResult->SetZOrder(3);
		m_TreasureResult->SetTexture("ChickenIcon", TEXT("Texture/UI/ChickenIcon.bmp"));
		m_TreasureResult->SetColorKey(255, 0, 255);
		m_TreasureResult->SetSize(37.f, 37.f);
		m_TreasureResult->SetPos(622.f, 210.f);
		break;
	}

	// 보물상자 생성.
	m_TreasureBox = CreateWidget<CImageWidget>("TreasureBoxOpened");
	m_TreasureBox->SetZOrder(1);
	m_TreasureBox->SetTexture("TreasureBoxOpened", TEXT("Texture/UI/TreasureBoxOpened.bmp"));
	m_TreasureBox->SetColorKey(255, 0, 255);
	m_TreasureBox->SetSize(195.f, 132.f);
	m_TreasureBox->SetPos(549.f, 380.f);

	m_TreasureBoxOpenButton->SetCallback<CTreasureBoxWindow>(EButton_Sound_State::Click,
		this, &CTreasureBoxWindow::TreasureBoxCloseButtonCallback);

	m_TreasureBoxButtonText->SetText(TEXT("완료"));

}

void CTreasureBoxWindow::TreasureBoxCloseButtonCallback()
{
	CGameManager::GetInst()->SetTimeScale(1.f);

	SetEnable(false);
}

