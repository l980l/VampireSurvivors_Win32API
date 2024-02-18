#pragma once
#include "GameObject.h"
class CSkill :
    public CGameObject
{
	friend class CScene;

protected:
	CSkill();
	CSkill(const CSkill& Obj);
	virtual ~CSkill();

protected:
	int			m_SkillLevel;
	float		m_Damage;

	// 투사체 속도 증가, 데미지 증가, 지속 시간 아이템을 위한 변수들.
	float		m_AdditionalSkillSpeed;
	float		m_AdditionalSkillDamage;
	float		m_AdditionalSkillDuration;
	int			m_AdditionalSkillProjectile;

public:
	// 이건 나중에 보물상자 만들때 필요할듯. 만렙이면 안뜨게 해야함.
	// 생각해보니 레벨업 할 때도 필요하네 
	int	GetSkillLevel()		const
	{
		return m_SkillLevel;
	}

	float GetAdditionSkillSpeed()
	{
		return m_AdditionalSkillSpeed;
	}

	float GetAdditionSkillDamage()
	{
		return m_AdditionalSkillDamage;
	}

	float GetAdditionSkillDuration()
	{
		return m_AdditionalSkillDuration;
	}

	int GetAdditionSkillProjectile()
	{
		return m_AdditionalSkillProjectile;
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
	virtual void SkillLevelUp();				// 레벨업을 위한 함수.


private:
	void CollisionBegin(CCollider* Src, CCollider* Dest);
	void CollisionEnd(CCollider* Src, CCollider* Dest);
};

