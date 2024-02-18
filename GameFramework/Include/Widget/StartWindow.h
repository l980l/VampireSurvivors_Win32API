#pragma once

#include "WidgetWindow.h"

class CStartWindow :
    public CWidgetWindow
{
    friend class CScene;

protected:
    CStartWindow();
    virtual ~CStartWindow();

private:
    CSharedPtr<class CText>             m_Text;
    TCHAR                               m_AddText[32];
    float                               m_TextTime;
    int                                 m_AddCount;
    CSharedPtr<class CNumber>           m_Hour;
    CSharedPtr<class CNumber>           m_Minute;
    CSharedPtr<class CNumber>           m_Second;
    CSharedPtr<class CText>             m_FPSText;

    CSharedPtr<class CButton>           m_StartButton;
    CSharedPtr<class CButton>           m_OptionButton;
    CSharedPtr<class CButton>           m_ExitButton;
    CSharedPtr<class CText>             m_StartButtonText;
    CSharedPtr<class CText>             m_OptionButtonText;
    CSharedPtr<class CText>             m_ExitButtonText;

    CSharedPtr<class CButton>           m_OptionExitButton;
    CSharedPtr<class CText>             m_OptionExitButtonText;

    CSharedPtr<class CImageWidget>      m_CharacterSelectFrame;
    CSharedPtr<class CText>             m_CharacterSelectFrameText;
    CSharedPtr<class CButton>           m_AntonioSlot;
    CSharedPtr<class CText>             m_AntonioSlotText;
    CSharedPtr<class CButton>           m_ImeldaSlot;
    CSharedPtr<class CText>             m_ImeldaSlotText;
    CSharedPtr<class CImageWidget>      m_CharacterDescription;
    CSharedPtr<class CText>             m_CharacterDescriptionText1;
    CSharedPtr<class CText>             m_AbilityText1;
    CSharedPtr<class CText>             m_AbilityText2;
    CSharedPtr<class CText>             m_AbilityText3;


    CSharedPtr<class CButton>           m_CharacterSelectExitButton;
    CSharedPtr<class CText>             m_CharacterSelectExitButtonText;
    CSharedPtr<class CButton>           m_CharacterSelectButton;
    CSharedPtr<class CText>             m_CharacterSelectButtonText;

    CSharedPtr<class CImageWidget>      m_OptionFrame;
    CSharedPtr<class CText>             m_OptionFrameText;
    CSharedPtr<class CText>             m_SoundControlText;
    CSharedPtr<class CText>             m_MusicControlText;
    CSharedPtr<class CSoundControlBar>  m_SoundControlBar;
    CSharedPtr<class CSoundControlBar>  m_MusicControlBar;



public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

public:
    void StartButtonCallback();
    void EndButtonCallback();
    void EditButtonCallback();
    void OptionButtonCallback();
    void OptionExitButtonCallback();
    void AntonioButtonCallback();
    void ImeldaButtonCallback();
    void CharacterSelectExitCallback();
    void CharacterSelectCallback();
};

