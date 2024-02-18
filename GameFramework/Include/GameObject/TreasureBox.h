#pragma once
#include "GameObject.h"
class CTreasureBox :
    public CGameObject
{
	friend class CScene;

protected:
	CTreasureBox();
	CTreasureBox(const CTreasureBox& Obj);
	virtual ~CTreasureBox();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);

private:
	void CollisionBegin(CCollider* Src, CCollider* Dest);
	void CollisionEnd(CCollider* Src, CCollider* Dest);

};

