#pragma once
#include "Skill.h"
class CWhipProjectile2 :
    public CSkill
{
	friend class CScene;

protected:
	CWhipProjectile2();
	CWhipProjectile2(const CWhipProjectile2& Obj);
	virtual ~CWhipProjectile2();

private:
	class CWhip* m_Whip;
	float	m_WhipTimePassed;

	int		m_WhipDir;
	float	m_YOffset;

	std::vector<std::string>	m_vecSequenceKey[1];

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);

public:
	void SetWhip(class CWhip* Whip)
	{
		m_Whip = Whip;
	}

private:
	void GetWhipLevel();

private:
	void CollisionBegin(CCollider* Src, CCollider* Dest);
	void CollisionEnd(CCollider* Src, CCollider* Dest);
	void InitEnd();
};