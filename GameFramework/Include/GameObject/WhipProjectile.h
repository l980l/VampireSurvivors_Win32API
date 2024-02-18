#pragma once
#include "Skill.h"
class CWhipProjectile :
    public CSkill
{
	friend class CScene;

protected:
	CWhipProjectile();
	CWhipProjectile(const CWhipProjectile& Obj);
	virtual ~CWhipProjectile();

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



