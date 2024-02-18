#pragma once

#include "../GameInfo.h"
#include "../Widget/WidgetWindow.h"
#include "../Widget/WidgetComponent.h"
#include "../GameObject/Monster.h"
#include "../GameObject/Player.h"

class CScene
{
	friend class CSceneManager;

protected:
	CScene();
	virtual ~CScene();

private:
	class CSceneResource* m_Resource;
	class CCamera* m_Camera;
	class CSceneCollision* m_Collision;

protected:
	std::list<CSharedPtr<class CGameObject>>	m_ObjList[(int)ERender_Layer::Max];
	std::list<CSharedPtr<CWidgetComponent>>		m_WidgetComponentList;
	CSharedPtr<CPlayer>							m_Player;
	CSharedPtr<class CTileMap>					m_TileMap;

	std::list<CSharedPtr<CMonster>>				m_MonsterList;		
	std::list<CSharedPtr<CMonster>>				m_MonsterBundle;		// 한꺼번에 제거돼야할 몬스터 뭉치들.

	std::vector<CSharedPtr<CWidgetWindow>>		m_vecWidgetWindow;

	float										m_Time;					// 흐른 시간.

public:
	class CSceneCollision* GetCollision()	const
	{
		return m_Collision;
	}

	class CCamera* GetCamera()	const
	{
		return m_Camera;
	}

	class CSceneResource* GetSceneResource()	const
	{
		return m_Resource;
	}

	class CPlayer* GetPlayer()	const
	{
		return m_Player;
	}

	class CTileMap* GetTileMap()	const
	{
		return m_TileMap;
	}

	std::list<CSharedPtr<CMonster>> GetMonsterList()
	{
		return m_MonsterList;
	}

	float GetPassedTime()
	{
		return m_Time;
	}

	void SetTileMap(class CTileMap* TileMap);
	void SetPlayer(class CPlayer* Player);
	void AddWidgetComponent(CWidgetComponent* Widget)
	{
		m_WidgetComponentList.push_back(Widget);
	}

	void AddMonster(CMonster* Monster)
	{
		m_MonsterList.push_back(Monster);
	}

	void AddMonsterBundle(CMonster* Monster)
	{
		m_MonsterBundle.push_back(Monster);
	}

	// 몬스터 번들을 비우는 함수. 내가 만듬.
	void ClearMonsterBundle()
	{
		auto iter = m_MonsterBundle.begin();
		auto iterEnd = m_MonsterBundle.end();
		
		for (; iter != iterEnd;)
		{
			(*iter)->InflictDamage(FLT_MAX);
			iter = m_MonsterBundle.erase(iter);
			iterEnd = m_MonsterBundle.end();
		}
	}

	
public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);

public:
	template <typename T>
	T* CreateObject(const std::string& Name = "GameObject")
	{
		T* Obj = new T;

		Obj->SetName(Name);
		Obj->m_Scene = this;

		if (!Obj->Init())
		{
			SAFE_DELETE(Obj);
			return nullptr;
		}

		m_ObjList[(int)Obj->GetRenderLayer()].push_back((CGameObject*)Obj);

		return Obj;
	}

	// 정해진 위치로 생성하기. 내가 만듬.
	template <typename T>
	T* CreateObject(const std::string& Name, const Vector2& Vector)
	{
		T* Obj = new T;

		Obj->SetName(Name);
		Obj->m_Scene = this;
		Obj->m_Pos = Vector;

		if (!Obj->Init())
		{
			SAFE_DELETE(Obj);
			return nullptr;
		}

		m_ObjList[(int)Obj->GetRenderLayer()].push_back((CGameObject*)Obj);

		return Obj;
	}

	template <typename T>
	T* CreateWidgetWindow(const std::string& Name = "Window")
	{
		T* Window = new T;

		Window->SetName(Name);
		Window->m_Scene = this;

		if (!Window->Init())
		{
			SAFE_DELETE(Window);
			return nullptr;
		}

		m_vecWidgetWindow.push_back(Window);

		return (T*)Window;
	}

	template <typename T>
	T* FindWidget(const std::string& Name)
	{
		size_t	Size = m_vecWidgetWindow.size();

		for (size_t i = 0; i < Size; ++i)
		{
			if (m_vecWidgetWindow[i]->GetName() == Name)
				return (T*)m_vecWidgetWindow[i].Get();
		}

		return nullptr;
	}

private:
	static bool SortY(const CSharedPtr<class CGameObject>& Src, const CSharedPtr<class CGameObject>& Dest);
	// ZOrder부터 비교하도록 내가 수정했음.
	static bool SortYWidgetComponent(const CSharedPtr<class CWidgetComponent>& Src, const CSharedPtr<class CWidgetComponent>& Dest);
	static bool SortWidget(const CSharedPtr<CWidgetWindow>& Src, const CSharedPtr<CWidgetWindow>& Dest);
};

