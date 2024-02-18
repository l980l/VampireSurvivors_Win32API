#pragma once

#include "Player.h"

class CPlayer2 :
	public CPlayer
{
	friend class CScene;

protected:
	CPlayer2();
	CPlayer2(const CPlayer2& Obj);
	virtual ~CPlayer2();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
	virtual float InflictDamage(float Damage);

	virtual void ExpUp(int Exp);

private:
	void MoveUp();
	void MoveDown();
	void MoveRight();
	void MoveLeft();

private:
	void CollisionBegin(CCollider* Src, CCollider* Dest);
	void CollisionEnd(CCollider* Src, CCollider* Dest);
};

