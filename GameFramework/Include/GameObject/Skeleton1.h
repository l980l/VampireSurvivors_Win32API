#pragma once
#include "Monster.h"
class CSkeleton1 :
    public CMonster
{
	friend class CScene;

protected:
	CSkeleton1();
	CSkeleton1(const CSkeleton1& Obj);
	virtual ~CSkeleton1();

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

