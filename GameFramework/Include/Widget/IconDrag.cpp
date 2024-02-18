
#include "IconDrag.h"
#include "../Resource/Texture/Texture.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "WidgetWindow.h"
#include "../Input.h"

CIconDrag::CIconDrag() :
	m_ButtonState(EButton_State::Normal)
{
}

CIconDrag::CIconDrag(const CIconDrag& widget) :
	CWidget(widget)
{
}

CIconDrag::~CIconDrag()
{
}

void CIconDrag::SetTexture(const std::string& Name, const TCHAR* FileName,
	const std::string& PathName)
{
	m_Scene->GetSceneResource()->LoadTexture(Name, FileName, PathName);
	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);
}

void CIconDrag::SetTextureFullPath(const std::string& Name, const TCHAR* FullPath)
{
	m_Scene->GetSceneResource()->LoadTextureFullPath(Name, FullPath);
	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);
}

#ifdef UNICODE


void CIconDrag::SetTexture(const std::string& Name, const std::vector<std::wstring>& vecFileName, const std::string& PathName)
{
	m_Scene->GetSceneResource()->LoadTexture(Name, vecFileName, PathName);
	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);
}

void CIconDrag::SetTextureFullPath(const std::string& Name, const std::vector<std::wstring>& vecFullPath)
{
	m_Scene->GetSceneResource()->LoadTextureFullPath(Name, vecFullPath);
	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);
}

#else

void CIconDrag::SetTexture(const std::string& Name, const std::vector<std::string>& vecFileName, const std::string& PathName)
{
	m_Scene->GetSceneResource()->LoadTexture(Name, vecFileName, PathName);
	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);
}

void CIconDrag::SetTextureFullPath(const std::string& Name, const std::vector<std::string>& vecFullPath)
{
	m_Scene->GetSceneResource()->LoadTextureFullPath(Name, vecFullPath);
	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);
}

#endif // UNICODE

void CIconDrag::SetColorKey(
	unsigned char r, unsigned char g, unsigned char b)
{
	if (m_Texture)
		m_Texture->SetColorKey(r, g, b);
}

bool CIconDrag::Init()
{
	return true;
}


void CIconDrag::Update(float DeltaTime)
{
	if (m_MouseHovered)
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
			m_Pos = CInput::GetInst()->GetMousePos() - m_PosOnWidget;
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

void CIconDrag::PostUpdate(float DeltaTime)
{
}

void CIconDrag::Render(HDC hDC, float DeltaTime)
{
	Vector2	RenderPos = m_Pos + m_Owner->GetPos();

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

	else
	{
		Rectangle(hDC, (int)RenderPos.x, (int)RenderPos.y,
			(int)(RenderPos.x + m_Size.x), (int)(RenderPos.y + m_Size.y));
	}
}

void CIconDrag::Render(HDC hDC, const Vector2& Pos, float DeltaTime)
{
}

void CIconDrag::CollisionMouseHoveredCallback(const Vector2& Pos)
{
	CWidget::CollisionMouseHoveredCallback(Pos);
}

void CIconDrag::CollisionMouseReleaseCallback()
{
	CWidget::CollisionMouseReleaseCallback();
}