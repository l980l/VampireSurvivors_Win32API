#pragma once
#include "WidgetWindow.h"
class CLevelUpWindow :
    public CWidgetWindow
{
    friend class CScene;

protected:
    CLevelUpWindow();
    virtual ~CLevelUpWindow();

protected:
    CSharedPtr<class CImageWidget>  m_LevelUpFrame;
    CSharedPtr<class CButton>  m_LevelUpSelect1Button;
    CSharedPtr<class CButton>  m_LevelUpSelect2Button;
    CSharedPtr<class CButton>  m_LevelUpSelect3Button;

    std::string     m_Select1;
    std::string     m_Select2;
    std::string     m_Select3;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

public:
    void Select1ButtonCallback();
    void Select2ButtonCallback();
    void Select3ButtonCallback();

private:
    void CreateIcon(std::string Icon, Vector2 Pos);
};

