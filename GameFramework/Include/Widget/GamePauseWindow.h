#pragma once
#include "WidgetWindow.h"
class CGamePauseWindow :
    public CWidgetWindow
{
    friend class CScene;

protected:
    CGamePauseWindow();
    virtual ~CGamePauseWindow();

protected:
    CSharedPtr<class CImageWidget>      m_OptionFrame;
    CSharedPtr<class CText>             m_OptionFrameText;
    CSharedPtr<class CText>             m_SoundControlText;
    CSharedPtr<class CText>             m_MusicControlText;

    CSharedPtr<class CSoundControlBar>  m_SoundControlBar;
    CSharedPtr<class CSoundControlBar>  m_MusicControlBar;

    CSharedPtr<class CButton>           m_BattleExitButton;
    CSharedPtr<class CText>             m_BattleExitButtonText;

    CSharedPtr<class CImageWidget>      m_SkillLevelFrame;

    std::vector<std::string>            m_vecItem;
    std::vector<std::string>            m_vecSkill;

    // Result
    CSharedPtr<class CImageWidget>      m_Back;
    CSharedPtr<class CImageWidget>      m_ResultFrame;
    CSharedPtr<class CText>             m_ResultFrameText;

    CSharedPtr<class CButton>           m_ResultExitButton;
    CSharedPtr<class CText>             m_ResultExitButtonText;

    CSharedPtr<class CText>             m_SurvivalTimeText;
    CSharedPtr<class CText>             m_ReachedLevelText;
    CSharedPtr<class CText>             m_MonsterKillCountText;


public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

public:
    void BattleExitButtonCallback();
    void ResultExitButtonCallback();

};

