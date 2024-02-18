#pragma once

#include "Skill.h"

class CGarlic :
    public CSkill
{
	friend class CScene;

protected:
	CGarlic();
	CGarlic(const CGarlic& Obj);
	virtual ~CGarlic();

private:
	float		m_Radius;
	std::list<CSharedPtr<class CGameObject>>	m_ColliderOwnerList;
	float		m_DamageTime;

public:
	// 이건 나중에 보물상자 만들때 필요할듯. 만렙이면 안뜨게 해야함.
	// 생각해보니 레벨업 할 때도 필요하네 
	int	GetSkillLevel()		const
	{
		return m_SkillLevel;
	}


public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
	virtual void SkillLevelUp();				// 레벨업을 위한 함수. 충돌체 여기서 다시 생성.

private:
	void CollisionBegin(CCollider* Src, CCollider* Dest);
	void CollisionEnd(CCollider* Src, CCollider* Dest);
};

