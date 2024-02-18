
#include "LevelUpWindow.h"
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
#include "CharacterHUD.h"

CLevelUpWindow::CLevelUpWindow()
{
}

CLevelUpWindow::~CLevelUpWindow()
{
}

bool CLevelUpWindow::Init()
{
	if (!CWidgetWindow::Init())
		return false;

	CGameManager::GetInst()->SetTimeScale(0.f);

	m_Scene->GetSceneResource()->SoundPlay("LevelUp");

	SetPos(0.f, 0.f);
	SetSize(1280.f, 720.f);

	// 프레임 생성
	m_LevelUpFrame = CreateWidget<CImageWidget>("TreasureBoxFrame");
	m_LevelUpFrame->SetZOrder(0);
	m_LevelUpFrame->SetTexture("TreasureBoxFrame", TEXT("Texture/UI/TreasureBoxFrame.bmp"));
	m_LevelUpFrame->SetColorKey(255, 0, 255);
	m_LevelUpFrame->SetSize(462.f, 619.f);
	m_LevelUpFrame->SetPos(409.f, 50.f);

	// 레벨업 텍스트 
	CText* LevelUpText = CreateWidget<CText>("Text");

	LevelUpText->SetText(TEXT("레벨 업!"));
	LevelUpText->SetPos(570.f, 80.f);
	LevelUpText->SetTextColor(255, 255, 255);
	LevelUpText->SetZOrder(3);


	// 레벨업 내용 얻기
	std::list<std::string> SelectList;

	SelectList = m_Scene->GetPlayer()->LevelUpRandom();

	auto iter = SelectList.begin();

	if (SelectList.size() >= 3)
	{
		m_Select1 = *iter;
		m_Select2 = *(++iter);
		m_Select3 = *(++iter);

		// 버튼 생성.
		m_LevelUpSelect1Button = CreateWidget<CButton>("LevelUpSelect1");
		m_LevelUpSelect1Button->SetTexture("LevelUpSelect1", TEXT("Texture/UI/LevelUpSelect.bmp"));
		m_LevelUpSelect1Button->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(457.f, 127.f));
		m_LevelUpSelect1Button->SetButtonStateData(EButton_State::MouseHovered, Vector2(0.f, 0.f), Vector2(457.f, 127.f));
		m_LevelUpSelect1Button->SetButtonStateData(EButton_State::Click, Vector2(0.f, 0.f), Vector2(457.f, 127.f));
		m_LevelUpSelect1Button->SetButtonStateData(EButton_State::Disable, Vector2(0.f, 0.f), Vector2(457.f, 127.f));
		m_LevelUpSelect1Button->SetColorKey(255, 0, 255);

		m_LevelUpSelect1Button->SetPos(413.f, 196.f);
		m_LevelUpSelect1Button->SetZOrder(1);

		m_LevelUpSelect1Button->SetCallback<CLevelUpWindow>(EButton_Sound_State::Click,
			this, &CLevelUpWindow::Select1ButtonCallback);

		// 아이콘 생성
		CLevelUpWindow::CreateIcon(m_Select1, Vector2(428.f, 211.f));

		// 버튼 생성.
		m_LevelUpSelect2Button = CreateWidget<CButton>("LevelUpSelect2");
		m_LevelUpSelect2Button->SetTexture("LevelUpSelect2", TEXT("Texture/UI/LevelUpSelect.bmp"));
		m_LevelUpSelect2Button->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(457.f, 127.f));
		m_LevelUpSelect2Button->SetButtonStateData(EButton_State::MouseHovered, Vector2(0.f, 0.f), Vector2(457.f, 127.f));
		m_LevelUpSelect2Button->SetButtonStateData(EButton_State::Click, Vector2(0.f, 0.f), Vector2(457.f, 127.f));
		m_LevelUpSelect2Button->SetButtonStateData(EButton_State::Disable, Vector2(0.f, 0.f), Vector2(457.f, 127.f));
		m_LevelUpSelect2Button->SetColorKey(255, 0, 255);

		m_LevelUpSelect2Button->SetPos(413.f, 323.f);
		m_LevelUpSelect2Button->SetZOrder(1);

		m_LevelUpSelect2Button->SetCallback<CLevelUpWindow>(EButton_Sound_State::Click,
			this, &CLevelUpWindow::Select2ButtonCallback);

		// 아이콘 생성
		CLevelUpWindow::CreateIcon(m_Select2, Vector2(428.f, 338.f));


		// 버튼 생성.
		m_LevelUpSelect3Button = CreateWidget<CButton>("LevelUpSelect3");
		m_LevelUpSelect3Button->SetTexture("LevelUpSelect3", TEXT("Texture/UI/LevelUpSelect.bmp"));
		m_LevelUpSelect3Button->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(457.f, 127.f));
		m_LevelUpSelect3Button->SetButtonStateData(EButton_State::MouseHovered, Vector2(0.f, 0.f), Vector2(457.f, 127.f));
		m_LevelUpSelect3Button->SetButtonStateData(EButton_State::Click, Vector2(0.f, 0.f), Vector2(457.f, 127.f));
		m_LevelUpSelect3Button->SetButtonStateData(EButton_State::Disable, Vector2(0.f, 0.f), Vector2(457.f, 127.f));
		m_LevelUpSelect3Button->SetColorKey(255, 0, 255);

		m_LevelUpSelect3Button->SetPos(413.f, 450.f);
		m_LevelUpSelect3Button->SetZOrder(1);

		m_LevelUpSelect3Button->SetCallback<CLevelUpWindow>(EButton_Sound_State::Click,
			this, &CLevelUpWindow::Select3ButtonCallback); 

		// 아이콘 생성
		CLevelUpWindow::CreateIcon(m_Select3, Vector2(428.f, 465.f));

	}

	else if (SelectList.size() == 2)
	{
		m_Select1 = *iter;
		m_Select2 = *(++iter);

		// 버튼 생성.
		m_LevelUpSelect1Button = CreateWidget<CButton>("LevelUpSelect1");
		m_LevelUpSelect1Button->SetTexture("LevelUpSelect1", TEXT("Texture/UI/LevelUpSelect.bmp"));
		m_LevelUpSelect1Button->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(457.f, 127.f));
		m_LevelUpSelect1Button->SetButtonStateData(EButton_State::MouseHovered, Vector2(0.f, 0.f), Vector2(457.f, 127.f));
		m_LevelUpSelect1Button->SetButtonStateData(EButton_State::Click, Vector2(0.f, 0.f), Vector2(457.f, 127.f));
		m_LevelUpSelect1Button->SetButtonStateData(EButton_State::Disable, Vector2(0.f, 0.f), Vector2(457.f, 127.f));
		m_LevelUpSelect1Button->SetColorKey(255, 0, 255);

		m_LevelUpSelect1Button->SetPos(413.f, 196.f);
		m_LevelUpSelect1Button->SetZOrder(1);

		m_LevelUpSelect1Button->SetCallback<CLevelUpWindow>(EButton_Sound_State::Click,
			this, &CLevelUpWindow::Select1ButtonCallback);

		// 아이콘 생성
		CLevelUpWindow::CreateIcon(m_Select1, Vector2(428.f, 211.f));

		// 버튼 생성.
		m_LevelUpSelect2Button = CreateWidget<CButton>("LevelUpSelect2");
		m_LevelUpSelect2Button->SetTexture("LevelUpSelect2", TEXT("Texture/UI/LevelUpSelect.bmp"));
		m_LevelUpSelect2Button->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(457.f, 127.f));
		m_LevelUpSelect2Button->SetButtonStateData(EButton_State::MouseHovered, Vector2(0.f, 0.f), Vector2(457.f, 127.f));
		m_LevelUpSelect2Button->SetButtonStateData(EButton_State::Click, Vector2(0.f, 0.f), Vector2(457.f, 127.f));
		m_LevelUpSelect2Button->SetButtonStateData(EButton_State::Disable, Vector2(0.f, 0.f), Vector2(457.f, 127.f));
		m_LevelUpSelect2Button->SetColorKey(255, 0, 255);

		m_LevelUpSelect2Button->SetPos(413.f, 323.f);
		m_LevelUpSelect2Button->SetZOrder(1);

		m_LevelUpSelect2Button->SetCallback<CLevelUpWindow>(EButton_Sound_State::Click,
			this, &CLevelUpWindow::Select2ButtonCallback);

		// 아이콘 생성
		CLevelUpWindow::CreateIcon(m_Select2, Vector2(428.f, 338.f));

	}

	else if (SelectList.size() == 1)
	{
		m_Select1 = *iter;

		// 버튼 생성.
		m_LevelUpSelect1Button = CreateWidget<CButton>("LevelUpSelect1");
		m_LevelUpSelect1Button->SetTexture("LevelUpSelect1", TEXT("Texture/UI/LevelUpSelect.bmp"));
		m_LevelUpSelect1Button->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(457.f, 127.f));
		m_LevelUpSelect1Button->SetButtonStateData(EButton_State::MouseHovered, Vector2(0.f, 0.f), Vector2(457.f, 127.f));
		m_LevelUpSelect1Button->SetButtonStateData(EButton_State::Click, Vector2(0.f, 0.f), Vector2(457.f, 127.f));
		m_LevelUpSelect1Button->SetButtonStateData(EButton_State::Disable, Vector2(0.f, 0.f), Vector2(457.f, 127.f));
		m_LevelUpSelect1Button->SetColorKey(255, 0, 255);

		m_LevelUpSelect1Button->SetPos(413.f, 196.f);
		m_LevelUpSelect1Button->SetZOrder(1);

		m_LevelUpSelect1Button->SetCallback<CLevelUpWindow>(EButton_Sound_State::Click,
			this, &CLevelUpWindow::Select1ButtonCallback);

		// 아이콘 생성
		CLevelUpWindow::CreateIcon(m_Select1, Vector2(428.f, 211.f));

	}

	return true;
}

void CLevelUpWindow::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
}

void CLevelUpWindow::Select1ButtonCallback()
{
	if (m_Select1 == "Garlic")
	{
		int SkillLevel = m_Scene->GetPlayer()->GetSkillLevel("Garlic");

		if (SkillLevel == 0)
		{
			m_Scene->GetPlayer()->CreateGarlicSkill();
			m_Scene->FindWidget<CCharacterHUD>("CharacterHUD")->AddSkill("Garlic");
		}
		else
			m_Scene->GetPlayer()->GarlicSkillLevelUp();
	}

	else if (m_Select1 == "Bible")
	{
		int SkillLevel = m_Scene->GetPlayer()->GetSkillLevel("Bible");

		if (SkillLevel == 0)
		{
			m_Scene->GetPlayer()->CreateBibleSkill();
			m_Scene->FindWidget<CCharacterHUD>("CharacterHUD")->AddSkill("Bible");
		}
		else
			m_Scene->GetPlayer()->BibleSkillLevelUp();
	}

	else if (m_Select1 == "Lightning")
	{
		int SkillLevel = m_Scene->GetPlayer()->GetSkillLevel("Lightning");

		if (SkillLevel == 0)
		{
			m_Scene->GetPlayer()->CreateLightningSkill();
			m_Scene->FindWidget<CCharacterHUD>("CharacterHUD")->AddSkill("Lightning");
		}
		else
			m_Scene->GetPlayer()->LightningSkillLevelUp();
	}

	else if (m_Select1 == "Whip")
	{
		int SkillLevel = m_Scene->GetPlayer()->GetSkillLevel("Whip");

		if (SkillLevel == 0)
		{
			m_Scene->GetPlayer()->CreateWhipSkill();
			m_Scene->FindWidget<CCharacterHUD>("CharacterHUD")->AddSkill("Whip");
		}
		else
			m_Scene->GetPlayer()->WhipSkillLevelUp();
	}


	else if (m_Select1 == "AdditionalSkillDamage")
	{
		m_Scene->GetPlayer()->SkillDamageUp();
		m_Scene->FindWidget<CCharacterHUD>("CharacterHUD")->AddItem("AdditionalSkillDamage");

	}

	else if (m_Select1 == "AdditionalSkillDuration")
	{
		m_Scene->GetPlayer()->SkillDurationUp();
		m_Scene->FindWidget<CCharacterHUD>("CharacterHUD")->AddItem("AdditionalSkillDuration");

	}

	else if (m_Select1 == "AdditionalSkillSpeed")
	{
		m_Scene->GetPlayer()->SkillSpeedUp();
		m_Scene->FindWidget<CCharacterHUD>("CharacterHUD")->AddItem("AdditionalSkillSpeed");

	}

	else if (m_Select1 == "AdditionalSkillProjectile")
	{
		m_Scene->GetPlayer()->SkillProjectileUp();
		m_Scene->FindWidget<CCharacterHUD>("CharacterHUD")->AddItem("AdditionalSkillProjectile");

	}

	// 체력 회복
	else if (m_Select1 == "Chicken")
	{
		m_Scene->GetPlayer()->HPUP(60);
		m_Scene->GetSceneResource()->SoundPlay("HPUP");
	}

	m_Scene->FindWidget<CCharacterHUD>("CharacterHUD")->UpdateSkillAndItemIcon();
	SetEnable(false);
	CGameManager::GetInst()->SetTimeScale(1.f);
}

void CLevelUpWindow::Select2ButtonCallback()
{
	if (m_Select2 == "Garlic")
	{
		int SkillLevel = m_Scene->GetPlayer()->GetSkillLevel("Garlic");

		if (SkillLevel == 0)
		{
			m_Scene->GetPlayer()->CreateGarlicSkill();
			m_Scene->FindWidget<CCharacterHUD>("CharacterHUD")->AddSkill("Garlic");
		}
		else
			m_Scene->GetPlayer()->GarlicSkillLevelUp();
	}

	else if (m_Select2 == "Bible")
	{
		int SkillLevel = m_Scene->GetPlayer()->GetSkillLevel("Bible");

		if (SkillLevel == 0)
		{
			m_Scene->GetPlayer()->CreateBibleSkill();
			m_Scene->FindWidget<CCharacterHUD>("CharacterHUD")->AddSkill("Bible");
		}
		else
			m_Scene->GetPlayer()->BibleSkillLevelUp();
	}

	else if (m_Select2 == "Lightning")
	{
		int SkillLevel = m_Scene->GetPlayer()->GetSkillLevel("Lightning");

		if (SkillLevel == 0)
		{
			m_Scene->GetPlayer()->CreateLightningSkill();
			m_Scene->FindWidget<CCharacterHUD>("CharacterHUD")->AddSkill("Lightning");
		}
		else
			m_Scene->GetPlayer()->LightningSkillLevelUp();
	}

	else if (m_Select2 == "Whip")
	{
		int SkillLevel = m_Scene->GetPlayer()->GetSkillLevel("Whip");

		if (SkillLevel == 0)
		{
			m_Scene->GetPlayer()->CreateWhipSkill();
			m_Scene->FindWidget<CCharacterHUD>("CharacterHUD")->AddSkill("Whip");
		}
		else
			m_Scene->GetPlayer()->WhipSkillLevelUp();
	}


	else if (m_Select2 == "AdditionalSkillDamage")
	{
		m_Scene->GetPlayer()->SkillDamageUp();
		m_Scene->FindWidget<CCharacterHUD>("CharacterHUD")->AddItem("AdditionalSkillDamage");

	}

	else if (m_Select2 == "AdditionalSkillDuration")
	{
		m_Scene->GetPlayer()->SkillDurationUp();
		m_Scene->FindWidget<CCharacterHUD>("CharacterHUD")->AddItem("AdditionalSkillDuration");

	}

	else if (m_Select2 == "AdditionalSkillSpeed")
	{
		m_Scene->GetPlayer()->SkillSpeedUp();
		m_Scene->FindWidget<CCharacterHUD>("CharacterHUD")->AddItem("AdditionalSkillSpeed");

	}

	else if (m_Select2 == "AdditionalSkillProjectile")
	{
		m_Scene->GetPlayer()->SkillProjectileUp();
		m_Scene->FindWidget<CCharacterHUD>("CharacterHUD")->AddItem("AdditionalSkillProjectile");
	}


	m_Scene->FindWidget<CCharacterHUD>("CharacterHUD")->UpdateSkillAndItemIcon();
	SetEnable(false);
	CGameManager::GetInst()->SetTimeScale(1.f);
}

void CLevelUpWindow::Select3ButtonCallback()
{
	if (m_Select3 == "Garlic")
	{
		int SkillLevel = m_Scene->GetPlayer()->GetSkillLevel("Garlic");

		if (SkillLevel == 0)
		{
			m_Scene->GetPlayer()->CreateGarlicSkill();
			m_Scene->FindWidget<CCharacterHUD>("CharacterHUD")->AddSkill("Garlic");
		}
		else
			m_Scene->GetPlayer()->GarlicSkillLevelUp();
	}

	else if (m_Select3 == "Bible")
	{
		int SkillLevel = m_Scene->GetPlayer()->GetSkillLevel("Bible");

		if (SkillLevel == 0)
		{
			m_Scene->GetPlayer()->CreateBibleSkill();
			m_Scene->FindWidget<CCharacterHUD>("CharacterHUD")->AddSkill("Bible");
		}
		else
			m_Scene->GetPlayer()->BibleSkillLevelUp();
	}

	else if (m_Select3 == "Lightning")
	{
		int SkillLevel = m_Scene->GetPlayer()->GetSkillLevel("Lightning");

		if (SkillLevel == 0)
		{
			m_Scene->GetPlayer()->CreateLightningSkill();
			m_Scene->FindWidget<CCharacterHUD>("CharacterHUD")->AddSkill("Lightning");
		}
		else
			m_Scene->GetPlayer()->LightningSkillLevelUp();
	}

	else if (m_Select3 == "Whip")
	{
		int SkillLevel = m_Scene->GetPlayer()->GetSkillLevel("Whip");

		if (SkillLevel == 0)
		{
			m_Scene->GetPlayer()->CreateWhipSkill();
			m_Scene->FindWidget<CCharacterHUD>("CharacterHUD")->AddSkill("Whip");
		}
		else
			m_Scene->GetPlayer()->WhipSkillLevelUp();
	}

	else if (m_Select3 == "AdditionalSkillDamage")
	{
		m_Scene->GetPlayer()->SkillDamageUp();
		m_Scene->FindWidget<CCharacterHUD>("CharacterHUD")->AddItem("AdditionalSkillDamage");

	}

	else if (m_Select3 == "AdditionalSkillDuration")
	{
		m_Scene->GetPlayer()->SkillDurationUp();
		m_Scene->FindWidget<CCharacterHUD>("CharacterHUD")->AddItem("AdditionalSkillDuration");

	}

	else if (m_Select3 == "AdditionalSkillSpeed")
	{
		m_Scene->GetPlayer()->SkillSpeedUp();
		m_Scene->FindWidget<CCharacterHUD>("CharacterHUD")->AddItem("AdditionalSkillSpeed");

	}

	else if (m_Select3 == "AdditionalSkillProjectile")
	{
		m_Scene->GetPlayer()->SkillProjectileUp();
		m_Scene->FindWidget<CCharacterHUD>("CharacterHUD")->AddItem("AdditionalSkillProjectile");

	}

	m_Scene->FindWidget<CCharacterHUD>("CharacterHUD")->UpdateSkillAndItemIcon();
	SetEnable(false);
	CGameManager::GetInst()->SetTimeScale(1.f);
}

void CLevelUpWindow::CreateIcon(std::string Icon,  Vector2 Pos)
{
	if (Icon == "Garlic")
	{
		// 이미지 생성
		CImageWidget* IconImage = CreateWidget<CImageWidget>(Icon.append("Icon"));
		IconImage->SetZOrder(2);
		IconImage->SetTexture(Icon, TEXT("Texture/UI/GarlicIcon.bmp"));
		IconImage->SetColorKey(255, 0, 255);
		IconImage->SetSize(37.f, 37.f);
		IconImage->SetPos(Pos);

		// IconName 
		CText* IconName = CreateWidget<CText>("IconName");

		IconName->SetText(TEXT("마늘"));
		IconName->SetPos(Pos + Vector2(70.f,0.f));
		IconName->SetTextColor(255, 255, 255);
		IconName->SetZOrder(3);
		IconName->SetFont("SmallFont");

		// Description
		CText* Description = CreateWidget<CText>("Description");

		Description->SetText(TEXT("범위 내의 적에게 피해를 줍니다."));
		Description->SetPos(Pos + Vector2(0.f, 50.f));
		Description->SetTextColor(255, 255, 255);
		Description->SetZOrder(3);
		Description->SetFont("SmallFont");

		// 스킬 레벨
		int SkillLevel = m_Scene->GetPlayer()->GetSkillLevel("Garlic");

		if (SkillLevel == 0)
		{
			CText* Level = CreateWidget<CText>("Text");
			Level->SetPos(Pos + Vector2(342.f, 0.f));
			Level->SetTextColor(255, 255, 0);
			Level->SetZOrder(3);
			Level->SetFont("SmallFont");
			Level->SetText(TEXT("신규"));
		}

		else
		{
			char	Text[256] = {};
			sprintf_s(Text, "레벨 : %d", SkillLevel + 1);

			TCHAR	Unicode[256] = {};
			int Length = MultiByteToWideChar(CP_ACP, 0, Text, -1, 0, 0);
			MultiByteToWideChar(CP_ACP, 0, Text, -1, Unicode, Length);

			CText* Level = CreateWidget<CText>("Text");
			Level->SetPos(Pos + Vector2(342.f, 0.f));
			Level->SetTextColor(255, 255, 255);
			Level->SetZOrder(3);
			Level->SetFont("SmallFont");
			Level->SetText(Unicode);
		}
	}

	else if (Icon == "Bible")
	{
		// 이미지 생성
		CImageWidget* IconImage = CreateWidget<CImageWidget>(Icon.append("Icon"));
		IconImage->SetZOrder(2);
		IconImage->SetTexture(Icon, TEXT("Texture/UI/BibleIcon.bmp"));
		IconImage->SetColorKey(255, 0, 255);
		IconImage->SetSize(37.f, 37.f);
		IconImage->SetPos(Pos);

		// IconName 
		CText* IconName = CreateWidget<CText>("IconName");

		IconName->SetText(TEXT("성경"));
		IconName->SetPos(Pos + Vector2(70.f, 0.f));
		IconName->SetTextColor(255, 255, 255);
		IconName->SetZOrder(3);
		IconName->SetFont("SmallFont");

		// Description
		CText* Description = CreateWidget<CText>("Description");

		Description->SetText(TEXT("주변을 회전하며 공격합니다. "));
		Description->SetPos(Pos + Vector2(0.f, 50.f));
		Description->SetTextColor(255, 255, 255);
		Description->SetZOrder(3);
		Description->SetFont("SmallFont");

		// 스킬 레벨
		int SkillLevel = m_Scene->GetPlayer()->GetSkillLevel("Bible");

		if (SkillLevel == 0)
		{
			CText* Level = CreateWidget<CText>("Text");
			Level->SetPos(Pos + Vector2(342.f, 0.f));
			Level->SetTextColor(255, 255, 0);
			Level->SetZOrder(3);
			Level->SetFont("SmallFont");
			Level->SetText(TEXT("신규"));
		}

		else
		{
			char	Text[256] = {};
			sprintf_s(Text, "레벨 : %d", SkillLevel + 1);

			TCHAR	Unicode[256] = {};
			int Length = MultiByteToWideChar(CP_ACP, 0, Text, -1, 0, 0);
			MultiByteToWideChar(CP_ACP, 0, Text, -1, Unicode, Length);

			CText* Level = CreateWidget<CText>("Text");
			Level->SetPos(Pos + Vector2(342.f, 0.f));
			Level->SetTextColor(255, 255, 255);
			Level->SetZOrder(3);
			Level->SetFont("SmallFont");
			Level->SetText(Unicode);
		}
	}
	
	else if (Icon == "Lightning")
	{
		// 이미지 생성
		CImageWidget* IconImage = CreateWidget<CImageWidget>(Icon.append("Icon"));
		IconImage->SetZOrder(2);
		IconImage->SetTexture(Icon, TEXT("Texture/UI/LightningIcon.bmp"));
		IconImage->SetColorKey(255, 0, 255);
		IconImage->SetSize(37.f, 37.f);
		IconImage->SetPos(Pos);

		// IconName 
		CText* IconName = CreateWidget<CText>("IconName");

		IconName->SetText(TEXT("번개 반지"));
		IconName->SetPos(Pos + Vector2(70.f, 0.f));
		IconName->SetTextColor(255, 255, 255);
		IconName->SetFont("SmallFont");
		IconName->SetZOrder(3);

		// Description
		CText* Description = CreateWidget<CText>("Description");

		Description->SetText(TEXT("무작위 적에게 번개를 내려칩니다."));
		Description->SetPos(Pos + Vector2(0.f, 50.f));
		Description->SetTextColor(255, 255, 255);
		Description->SetZOrder(3);
		Description->SetFont("SmallFont");

		// 스킬 레벨
		int SkillLevel = m_Scene->GetPlayer()->GetSkillLevel("Lightning");

		if (SkillLevel == 0)
		{
			CText* Level = CreateWidget<CText>("Text");
			Level->SetPos(Pos + Vector2(342.f, 0.f));
			Level->SetTextColor(255, 255, 0);
			Level->SetZOrder(3);
			Level->SetFont("SmallFont");
			Level->SetText(TEXT("신규"));
		}

		else
		{
			char	Text[256] = {};
			sprintf_s(Text, "레벨 : %d", SkillLevel + 1);

			TCHAR	Unicode[256] = {};
			int Length = MultiByteToWideChar(CP_ACP, 0, Text, -1, 0, 0);
			MultiByteToWideChar(CP_ACP, 0, Text, -1, Unicode, Length);

			CText* Level = CreateWidget<CText>("Text");
			Level->SetPos(Pos + Vector2(342.f, 0.f));
			Level->SetTextColor(255, 255, 255);
			Level->SetZOrder(3);
			Level->SetFont("SmallFont");
			Level->SetText(Unicode);
		}
	
	}

	else if (Icon == "Whip")
	{
		// 이미지 생성
		CImageWidget* IconImage = CreateWidget<CImageWidget>(Icon.append("Icon"));
		IconImage->SetZOrder(2);
		IconImage->SetTexture(Icon, TEXT("Texture/UI/WhipIcon.bmp"));
		IconImage->SetColorKey(255, 0, 255);
		IconImage->SetSize(37.f, 37.f);
		IconImage->SetPos(Pos);

		// IconName 
		CText* IconName = CreateWidget<CText>("IconName");

		IconName->SetText(TEXT("채찍"));
		IconName->SetPos(Pos + Vector2(70.f, 0.f));
		IconName->SetTextColor(255, 255, 255);
		IconName->SetZOrder(3);
		IconName->SetFont("SmallFont");

		// Description
		CText* Description = CreateWidget<CText>("Description");

		Description->SetText(TEXT("좌우로 적을 관통해 공격합니다."));
		Description->SetPos(Pos + Vector2(0.f, 50.f));
		Description->SetTextColor(255, 255, 255);
		Description->SetZOrder(3);
		Description->SetFont("SmallFont");

		// 스킬 레벨
		int SkillLevel = m_Scene->GetPlayer()->GetSkillLevel("Whip");

		if (SkillLevel == 0)
		{
			CText* Level = CreateWidget<CText>("Text");
			Level->SetPos(Pos + Vector2(342.f, 0.f));
			Level->SetTextColor(255, 255, 0);
			Level->SetZOrder(3);
			Level->SetFont("SmallFont");
			Level->SetText(TEXT("신규"));
		}

		else
		{
			char	Text[256] = {};
			sprintf_s(Text, "레벨 : %d", SkillLevel + 1);

			TCHAR	Unicode[256] = {};
			int Length = MultiByteToWideChar(CP_ACP, 0, Text, -1, 0, 0);
			MultiByteToWideChar(CP_ACP, 0, Text, -1, Unicode, Length);

			CText* Level = CreateWidget<CText>("Text");
			Level->SetPos(Pos + Vector2(342.f, 0.f));
			Level->SetTextColor(255, 255, 255);
			Level->SetZOrder(3);
			Level->SetFont("SmallFont");
			Level->SetText(Unicode);
		}
	}

	else if (Icon == "AdditionalSkillDamage")
	{
		// 이미지 생성
		CImageWidget* IconImage = CreateWidget<CImageWidget>(Icon.append("Icon"));
		IconImage->SetZOrder(2);
		IconImage->SetTexture(Icon, TEXT("Texture/UI/AdditionalSkillDamageIcon.bmp"));
		IconImage->SetColorKey(255, 0, 255);
		IconImage->SetSize(37.f, 37.f);
		IconImage->SetPos(Pos);

		// IconName 
		CText* IconName = CreateWidget<CText>("IconName");

		IconName->SetText(TEXT("시금치"));
		IconName->SetPos(Pos + Vector2(70.f, 0.f));
		IconName->SetTextColor(255, 255, 255);
		IconName->SetZOrder(3);
		IconName->SetFont("SmallFont");

		// Description
		CText* Description = CreateWidget<CText>("Description");

		Description->SetText(TEXT("피해량이 10% 증가합니다."));
		Description->SetPos(Pos + Vector2(0.f, 50.f));
		Description->SetTextColor(255, 255, 255);
		Description->SetZOrder(3);
		Description->SetFont("SmallFont");

		// 아이템 레벨
		int SkillLevel = (int)(m_Scene->GetPlayer()->GetAdditionSkillDamage() * 10.f - 10);

		if (SkillLevel == 0)
		{
			CText* Level = CreateWidget<CText>("Text");
			Level->SetPos(Pos + Vector2(342.f, 0.f));
			Level->SetTextColor(255, 255, 0);
			Level->SetZOrder(3);
			Level->SetFont("SmallFont");
			Level->SetText(TEXT("신규"));
		}

		else
		{
			char	Text[256] = {};
			sprintf_s(Text, "레벨 : %d", SkillLevel + 1);

			TCHAR	Unicode[256] = {};
			int Length = MultiByteToWideChar(CP_ACP, 0, Text, -1, 0, 0);
			MultiByteToWideChar(CP_ACP, 0, Text, -1, Unicode, Length);

			CText* Level = CreateWidget<CText>("Text");
			Level->SetPos(Pos + Vector2(342.f, 0.f));
			Level->SetTextColor(255, 255, 255);
			Level->SetZOrder(3);
			Level->SetFont("SmallFont");
			Level->SetText(Unicode);
		}
	}

	else if (Icon == "AdditionalSkillDuration")
	{
		// 이미지 생성
		CImageWidget* IconImage = CreateWidget<CImageWidget>(Icon.append("Icon"));
		IconImage->SetZOrder(2);
		IconImage->SetTexture(Icon, TEXT("Texture/UI/AdditionalSkillDurationIcon.bmp"));
		IconImage->SetColorKey(255, 0, 255);
		IconImage->SetSize(37.f, 37.f);
		IconImage->SetPos(Pos);

		// IconName 
		CText* IconName = CreateWidget<CText>("IconName");

		IconName->SetText(TEXT("주문속박기"));
		IconName->SetPos(Pos + Vector2(70.f, 0.f));
		IconName->SetTextColor(255, 255, 255);
		IconName->SetZOrder(3);
		IconName->SetFont("SmallFont");

		// Description
		CText* Description = CreateWidget<CText>("Description");

		Description->SetText(TEXT("지속시간이 10% 증가합니다."));
		Description->SetPos(Pos + Vector2(0.f, 50.f));
		Description->SetTextColor(255, 255, 255);
		Description->SetZOrder(3);
		Description->SetFont("SmallFont");

		// 아이템 레벨
		int SkillLevel = int(m_Scene->GetPlayer()->GetAdditionSkillDuration() * 10.f - 10);

		if (SkillLevel == 0)
		{
			CText* Level = CreateWidget<CText>("Text");
			Level->SetPos(Pos + Vector2(342.f, 0.f));
			Level->SetTextColor(255, 255, 0);
			Level->SetZOrder(3);
			Level->SetFont("SmallFont");
			Level->SetText(TEXT("신규"));
		}

		else
		{
			char	Text[256] = {};
			sprintf_s(Text, "레벨 : %d", SkillLevel + 1);

			TCHAR	Unicode[256] = {};
			int Length = MultiByteToWideChar(CP_ACP, 0, Text, -1, 0, 0);
			MultiByteToWideChar(CP_ACP, 0, Text, -1, Unicode, Length);

			CText* Level = CreateWidget<CText>("Text");
			Level->SetPos(Pos + Vector2(342.f, 0.f));
			Level->SetTextColor(255, 255, 255);
			Level->SetZOrder(3);
			Level->SetFont("SmallFont");
			Level->SetText(Unicode);
		}
		
	}

	else if (Icon == "AdditionalSkillSpeed")
	{
		// 이미지 생성
		CImageWidget* IconImage = CreateWidget<CImageWidget>(Icon.append("Icon"));
		IconImage->SetZOrder(2);
		IconImage->SetTexture(Icon, TEXT("Texture/UI/AdditionalSkillSpeedIcon.bmp"));
		IconImage->SetColorKey(255, 0, 255);
		IconImage->SetSize(37.f, 37.f);
		IconImage->SetPos(Pos);

		// IconName 
		CText* IconName = CreateWidget<CText>("IconName");

		IconName->SetText(TEXT("팔 보호대"));
		IconName->SetPos(Pos + Vector2(70.f, 0.f));
		IconName->SetTextColor(255, 255, 255);
		IconName->SetZOrder(3);
		IconName->SetFont("SmallFont");

		// Description
		CText* Description = CreateWidget<CText>("Description");

		Description->SetText(TEXT("투사체 속도가 10% 증가합니다."));
		Description->SetPos(Pos + Vector2(0.f, 50.f));
		Description->SetTextColor(255, 255, 255);
		Description->SetZOrder(3);
		Description->SetFont("SmallFont");

		// 아이템 레벨
		int SkillLevel = (int)(m_Scene->GetPlayer()->GetAdditionSkillSpeed() * 10.f - 10);

		if (SkillLevel == 0)
		{
			CText* Level = CreateWidget<CText>("Text");
			Level->SetPos(Pos + Vector2(342.f, 0.f));
			Level->SetTextColor(255, 255, 0);
			Level->SetZOrder(3);
			Level->SetFont("SmallFont");
			Level->SetText(TEXT("신규"));
		}

		else
		{
			char	Text[256] = {};
			sprintf_s(Text, "레벨 : %d", SkillLevel + 1);

			TCHAR	Unicode[256] = {};
			int Length = MultiByteToWideChar(CP_ACP, 0, Text, -1, 0, 0);
			MultiByteToWideChar(CP_ACP, 0, Text, -1, Unicode, Length);

			CText* Level = CreateWidget<CText>("Text");
			Level->SetPos(Pos + Vector2(342.f, 0.f));
			Level->SetTextColor(255, 255, 255);
			Level->SetZOrder(3);
			Level->SetFont("SmallFont");
			Level->SetText(Unicode);
		}
		
	}

	else if (Icon == "AdditionalSkillProjectile")
	{
		// 이미지 생성
		CImageWidget* IconImage = CreateWidget<CImageWidget>(Icon.append("Icon"));
		IconImage->SetZOrder(2);
		IconImage->SetTexture(Icon, TEXT("Texture/UI/AdditionalSkillProjectileIcon.bmp"));
		IconImage->SetColorKey(255, 0, 255);
		IconImage->SetSize(37.f, 37.f);
		IconImage->SetPos(Pos);

		// IconName 
		CText* IconName = CreateWidget<CText>("IconName");

		IconName->SetText(TEXT("복제 반지"));
		IconName->SetPos(Pos + Vector2(70.f, 0.f));
		IconName->SetTextColor(255, 255, 255);
		IconName->SetZOrder(3);
		IconName->SetFont("SmallFont");

		// Description
		CText* Description = CreateWidget<CText>("Description");

		Description->SetText(TEXT("추가 투사체를 획득합니다."));
		Description->SetPos(Pos + Vector2(0.f, 50.f));
		Description->SetTextColor(255, 255, 255);
		Description->SetZOrder(3);
		Description->SetFont("SmallFont");

		// 아이템 레벨
		int SkillLevel = m_Scene->GetPlayer()->GetAdditionSkillProjectile();

		if (SkillLevel == 0)
		{
			CText* Level = CreateWidget<CText>("Text");
			Level->SetPos(Pos + Vector2(342.f, 0.f));
			Level->SetTextColor(255, 255, 0);
			Level->SetZOrder(3);
			Level->SetFont("SmallFont");
			Level->SetText(TEXT("신규"));
		}

		else
		{
			char	Text[256] = {};
			sprintf_s(Text, "레벨 : %d", SkillLevel + 1);

			TCHAR	Unicode[256] = {};
			int Length = MultiByteToWideChar(CP_ACP, 0, Text, -1, 0, 0);
			MultiByteToWideChar(CP_ACP, 0, Text, -1, Unicode, Length);

			CText* Level = CreateWidget<CText>("Text");
			Level->SetPos(Pos + Vector2(342.f, 0.f));
			Level->SetTextColor(255, 255, 255);
			Level->SetZOrder(3);
			Level->SetFont("SmallFont");
			Level->SetText(Unicode);
		}
	}

	else if (Icon == "Chicken")
	{
		// 이미지 생성
		CImageWidget* IconImage = CreateWidget<CImageWidget>(Icon.append("Icon"));
		IconImage->SetZOrder(2);
		IconImage->SetTexture(Icon, TEXT("Texture/UI/ChickenIcon.bmp"));
		IconImage->SetColorKey(255, 0, 255);
		IconImage->SetSize(37.f, 37.f);
		IconImage->SetPos(Pos);

		// IconName 
		CText* IconName = CreateWidget<CText>("IconName");

		IconName->SetText(TEXT("치킨"));
		IconName->SetPos(Pos + Vector2(70.f, 0.f));
		IconName->SetTextColor(255, 255, 255);
		IconName->SetZOrder(3);
		IconName->SetFont("SmallFont");

		// Description
		CText* Description = CreateWidget<CText>("Description");

		Description->SetText(TEXT("체력을 회복합니다. "));
		Description->SetPos(Pos + Vector2(0.f, 50.f));
		Description->SetTextColor(255, 255, 255);
		Description->SetZOrder(3);
		Description->SetFont("SmallFont");
	}
}

