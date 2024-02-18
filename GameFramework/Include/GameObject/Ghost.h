#pragma once
#include "Monster.h"
class CGhost :
    public CMonster
{
	friend class CScene;

protected:
	CGhost();
	CGhost(const CGhost& Obj);
	virtual ~CGhost();

private:
	Vector2	m_Dir;
	int		m_HP;
	int		m_Damage;
	int		m_MonsterDir;
	float	m_PushBackSpeed;
	bool	m_Death;
	bool	m_Damaged;

	std::vector<std::string>	m_vecSequenceKey[2];

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
	virtual float InflictDamage(float Damage);


private:
	void CollisionBegin(CCollider* Src, CCollider* Dest);
	void CollisionEnd(CCollider* Src, CCollider* Dest);
	void CollisionMouseBegin(CCollider* Src, const Vector2& MousePos);
	void CollisionMouseEnd(CCollider* Src, const Vector2& MousePos);
	void Death();
	void Damaged();
};

