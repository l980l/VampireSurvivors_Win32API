#pragma once
#include "Widget.h"
class CSoundControlBar :
    public CWidget
{
    friend class CWidgetComponent;
    friend class CWidgetWindow;

protected:
    CSoundControlBar();
    CSoundControlBar(const CSoundControlBar& widget);
    virtual ~CSoundControlBar();

protected:
    EButton_State           m_ButtonState;
    CSharedPtr<class CTexture>  m_Texture;
    Vector2		        m_PosOnWidget;
    Vector2		        m_ZeroPos;
    Vector2		        m_EndPos;
    std::string         m_Type;

public:
    void SetSoundType(std::string Type)
    {
        m_Type = Type;
        m_ZeroPos = m_Pos + Vector2(0.f, 28.f);
        m_EndPos = m_ZeroPos + Vector2(150.f, 0.f);

        if (m_Type == "Sound")
        {
            m_Pos.x += (m_EndPos.x - m_ZeroPos.x) * (g_SoundVolume / 100.f);
        }

        else if (m_Type == "Music")
        {
            m_Pos.x += (m_EndPos.x - m_ZeroPos.x) * (g_MusicVolume / 100.f);
        }
    }

public:
    void SetTexture(const std::string& Name, const TCHAR* FileName,
        const std::string& PathName = TEXTURE_PATH);
    void SetTextureFullPath(const std::string& Name, const TCHAR* FullPath);

#ifdef UNICODE

    void SetTexture(const std::string& Name, const std::vector<std::wstring>& vecFileName,
        const std::string& PathName = TEXTURE_PATH);
    void SetTextureFullPath(const std::string& Name, const std::vector<std::wstring>& vecFullPath);

#else

    void SetTexture(const std::string& Name, const std::vector<std::string>& vecFileName,
        const std::string& PathName = TEXTURE_PATH);
    void SetTextureFullPath(const std::string& Name, const std::vector<std::string>& vecFullPath);

#endif
    void SetColorKey(unsigned char r, unsigned char g, unsigned char b);

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render(HDC hDC, float DeltaTime);
    virtual void Render(HDC hDC, const Vector2& Pos, float DeltaTime);

public:
    virtual void CollisionMouseHoveredCallback(const Vector2& Pos);
    virtual void CollisionMouseReleaseCallback();
};

