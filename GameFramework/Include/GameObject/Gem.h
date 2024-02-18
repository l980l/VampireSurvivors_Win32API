#pragma once
#include "GameObject.h"
class CGem :
	public CGameObject
{
	friend class CScene;

protected:
	CGem();
	CGem(const CGem& Obj);
	virtual ~CGem();

private:
	int m_ExpHaving;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);

private:
	void CollisionBegin(CCollider* Src, CCollider* Dest);
	void CollisionEnd(CCollider* Src, CCollider* Dest);
};


