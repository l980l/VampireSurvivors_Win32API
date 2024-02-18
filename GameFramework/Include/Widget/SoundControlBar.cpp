
#include "SoundControlBar.h"
#include "../Resource/Texture/Texture.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "WidgetWindow.h"
#include "../Input.h"
#include "../GameManager.h"

CSoundControlBar::CSoundControlBar() :
	m_ButtonState(EButton_State::Normal)
{
}

CSoundControlBar::CSoundControlBar(const CSoundControlBar& widget) :
	CWidget(widget)
{
}

CSoundControlBar::~CSoundControlBar()
{
}

void CSoundControlBar::SetTexture(const std::string& Name, const TCHAR* FileName,
	const std::string& PathName)
{
	m_Scene->GetSceneResource()->LoadTexture(Name, FileName, PathName);
	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);
}

void CSoundControlBar::SetTextureFullPath(const std::string& Name, const TCHAR* FullPath)
{
	m_Scene->GetSceneResource()->LoadTextureFullPath(Name, FullPath);
	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);
}

#ifdef UNICODE


void CSoundControlBar::SetTexture(const std::string& Name, const std::vector<std::wstring>& vecFileName, const std::string& PathName)
{
	m_Scene->GetSceneResource()->LoadTexture(Name, vecFileName, PathName);
	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);
}

void CSoundControlBar::SetTextureFullPath(const std::string& Name, const std::vector<std::wstring>& vecFullPath)
{
	m_Scene->GetSceneResource()->LoadTextureFullPath(Name, vecFullPath);
	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);
}

#else

void CSoundControlBar::SetTexture(const std::string& Name, const std::vector<std::string>& vecFileName, const std::string& PathName)
{
	m_Scene->GetSceneResource()->LoadTexture(Name, vecFileName, PathName);
	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);
}

void CSoundControlBar::SetTextureFullPath(const std::string& Name, const std::vector<std::string>& vecFullPath)
{
	m_Scene->GetSceneResource()->LoadTextureFullPath(Name, vecFullPath);
	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);
}

#endif // UNICODE

void CSoundControlBar::SetColorKey(
	unsigned char r, unsigned char g, unsigned char b)
{
	if (m_Texture)
		m_Texture->SetColorKey(255, 0, 255);
}

bool CSoundControlBar::Init()
{
	/*m_ZeroPos = m_Pos;
	m_EndPos = m_ZeroPos + Vector2(400.f, 0);*/
	
	return true;
}


void CSoundControlBar::Update(float DeltaTime)
{
	if (CInput::GetInst()->GetMousePos().x < m_Pos.x + m_Size.x  &&
		CInput::GetInst()->GetMousePos().x > m_Pos.x &&
		CInput::GetInst()->GetMousePos().y < m_Pos.y + m_Size.y &&
		CInput::GetInst()->GetMousePos().y > m_Pos.y ||
		m_ButtonState == EButton_State::Click)
	{

		if (CInput::GetInst()->GetMouseLDown())
		{
			m_ButtonState = EButton_State::Click;
			m_PosOnWidget = CInput::GetInst()->GetMousePos() - m_Pos;
		}

		// 버튼 기능 동작.
		else if (m_ButtonState == EButton_State::Click &&
			CInput::GetInst()->GetMouseLUp())
		{
			m_ButtonState = EButton_State::MouseHovered;
		}

		else if (m_ButtonState == EButton_State::Click &&
			CInput::GetInst()->GetMouseLPush())
		{
			m_ButtonState = EButton_State::Click;
			if (CInput::GetInst()->GetMousePos().x - m_PosOnWidget.x >= m_ZeroPos.x &&
				CInput::GetInst()->GetMousePos().x - m_PosOnWidget.x <= m_EndPos.x)
			{
				m_Pos.x = CInput::GetInst()->GetMousePos().x - m_PosOnWidget.x;

				if (m_Type == "Sound")
				{
					g_SoundVolume = (int)(((m_Pos.x - m_ZeroPos.x) / (m_EndPos.x - m_ZeroPos.x)) * 100);
				}

				else if (m_Type == "Music")
				{
					g_MusicVolume = (int)(((m_Pos.x - m_ZeroPos.x) / (m_EndPos.x - m_ZeroPos.x)) * 100);
				}

			}
		}

		else
		{
			m_ButtonState = EButton_State::MouseHovered;
		}

	}

	else
	{
		m_ButtonState = EButton_State::Normal;
	}

}

void CSoundControlBar::PostUpdate(float DeltaTime)
{
}

void CSoundControlBar::Render(HDC hDC, float DeltaTime)
{
	Vector2	RenderPos = m_Pos + m_Owner->GetPos();

	// 선그리기.
	HPEN	Pen = CGameManager::GetInst()->GetPen(EBrush_Type::Black);

	MoveToEx(hDC, (long)(m_ZeroPos.x + 28.f), (long)m_ZeroPos.y, nullptr);
	LineTo(hDC, (long)(m_EndPos.x + 28.f), (long)m_EndPos.y);

	if (m_Texture)
	{
		if (m_Texture->GetTextureType() == ETexture_Type::Sprite)
		{
			if (m_Texture->GetEnableColorKey())
			{
				TransparentBlt(hDC, (int)RenderPos.x, (int)RenderPos.y,
					(int)m_Size.x, (int)m_Size.y,
					m_Texture->GetDC(),
					0, 0, (int)m_Size.x, (int)m_Size.y,
					m_Texture->GetColorKey());
			}

			else
			{
				BitBlt(hDC, (int)RenderPos.x, (int)RenderPos.y,
					(int)m_Size.x, (int)m_Size.y,
					m_Texture->GetDC(),
					0, 0, SRCCOPY);
			}
		}

		else
		{
		}
	}
	
}

void CSoundControlBar::Render(HDC hDC, const Vector2& Pos, float DeltaTime)
{
}

void CSoundControlBar::CollisionMouseHoveredCallback(const Vector2& Pos)
{
	CWidget::CollisionMouseHoveredCallback(Pos);
}

void CSoundControlBar::CollisionMouseReleaseCallback()
{
	CWidget::CollisionMouseReleaseCallback();
}