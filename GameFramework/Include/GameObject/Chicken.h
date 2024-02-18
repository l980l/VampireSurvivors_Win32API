#pragma once
#include "GameObject.h"
class CChicken :
    public CGameObject
{
	friend class CScene;

protected:
	CChicken();
	CChicken(const CChicken& Obj);
	virtual ~CChicken();

private:
	int m_HPHaving;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);

private:
	void CollisionBegin(CCollider* Src, CCollider* Dest);
	void CollisionEnd(CCollider* Src, CCollider* Dest);
};

