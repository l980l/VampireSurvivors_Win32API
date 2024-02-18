#pragma once
#include "GameObject.h"
class CFirePot :
    public CGameObject
{
	friend class CScene;

protected:
	CFirePot();
	CFirePot(const CFirePot& Obj);
	virtual ~CFirePot();


public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);

private:
	void CollisionBegin(CCollider* Src, CCollider* Dest);
	void CollisionEnd(CCollider* Src, CCollider* Dest);
};

