#pragma once

#include "Skill.h"

class CLightning :

    public CSkill
{
	friend class CScene;

protected:
	CLightning();
	CLightning(const CLightning& Obj);
	virtual ~CLightning();

private:
	// 투사체 속도, 지속시간 적용 안되는 스킬임.
	int			m_LightningCount;		// 생성할 번개 개수
	float		m_LightningCoolTime;	// 쿨타임
	float		m_SkillUseTime;			// 스킬 사용후 지난 시간.

public:
	// 이건 나중에 보물상자 만들때 필요할듯. 만렙이면 안뜨게 해야함.
	// 생각해보니 레벨업 할 때도 필요하네 
	int	GetSkillLevel()
	{
		return m_SkillLevel;
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
	virtual void SkillLevelUp();				

};