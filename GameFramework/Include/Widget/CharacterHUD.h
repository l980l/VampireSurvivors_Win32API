#pragma once
#include "WidgetWindow.h"
class CCharacterHUD :
    public CWidgetWindow
{
    friend class CScene;

protected:
    CCharacterHUD();
    virtual ~CCharacterHUD();

protected:
    CSharedPtr<class CProgressBar>  m_ExpPBar;
    CSharedPtr<class CImageWidget>  m_ExpBarFrame;
    CSharedPtr<class CText>     m_LevelText;
    CSharedPtr<class CText>     m_KillCountText;
    CSharedPtr<class CText>     m_FPSText;
    CSharedPtr<class CText>     m_TimeText;
    float                       m_Time;

    std::vector<std::string>   m_vecItem;
    std::vector<std::string>   m_vecSkill;

public:
    std::vector<std::string> GetVecItem()
    {
        return m_vecItem;
    }

    std::vector<std::string> GetVecSkill()
    {
        return m_vecSkill;
    }

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

public:
    void SetExp(float Exp);
    void AddItem(std::string Item);
    void AddSkill(std::string Skill);
    void AddEvolvedBible();

public:
    void UpdateSkillAndItemIcon();
};

