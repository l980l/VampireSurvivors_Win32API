#pragma once

#include "Character.h"

class CMonster :
	public CCharacter
{
	friend class CScene;

protected:
	CMonster();
	CMonster(const CMonster& Obj);
	virtual ~CMonster();

protected:
	Vector2	m_Dir;
	int		m_HP;
	int		m_Damage;
	int		m_MonsterDir;
	bool	m_Death;
	int		m_Damaged;
	bool	m_PlayerOverlap;
	
	std::vector<std::string>			m_vecSequenceKey[2];

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
	float InflictDamage(float Damage);


private:
	void CollisionBegin(CCollider* Src, CCollider* Dest);
	void CollisionEnd(CCollider* Src, CCollider* Dest);
	void CollisionMouseBegin(CCollider* Src, const Vector2& MousePos);
	void CollisionMouseEnd(CCollider* Src, const Vector2& MousePos);
	void Death();
	void Damaged();
};

