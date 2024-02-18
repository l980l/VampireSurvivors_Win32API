#pragma once
#include "WidgetWindow.h"
class CTreasureBoxWindow :
    public CWidgetWindow
{
    friend class CScene;

protected:
    CTreasureBoxWindow();
    virtual ~CTreasureBoxWindow();

protected:
    CSharedPtr<class CImageWidget>  m_TreasureBoxFrame;
    CSharedPtr<class CImageWidget>  m_TreasureBox;
    CSharedPtr<class CImageWidget>  m_TreasureResult;
    CSharedPtr<class CButton>       m_TreasureBoxOpenButton;
    CSharedPtr<class CText>       m_TreasureBoxFrameText;
    CSharedPtr<class CText>       m_TreasureBoxButtonText;


public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

public:
    void TreasureBoxOpenButtonCallback();
    void TreasureBoxCloseButtonCallback();

};

