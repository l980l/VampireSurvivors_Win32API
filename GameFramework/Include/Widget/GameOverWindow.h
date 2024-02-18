#pragma once
#include "WidgetWindow.h"
class CGameOverWindow :
    public CWidgetWindow
{
    friend class CScene;

protected:
    CGameOverWindow();
    virtual ~CGameOverWindow();

protected:
    CSharedPtr<class CImageWidget>      m_GameOverImage;
    CSharedPtr<class CButton>           m_GameOverExitButton;
    CSharedPtr<class CText>             m_GameOverExitText;

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

