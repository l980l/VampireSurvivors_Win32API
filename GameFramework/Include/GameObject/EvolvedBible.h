#pragma once
#include "Skill.h"
class CEvolvedBible :
	public CSkill
{
	friend class CScene;

protected:
	CEvolvedBible();
	CEvolvedBible(const CEvolvedBible& Obj);
	virtual ~CEvolvedBible();

private:
	float		m_Radius;
	int			m_EvolvedBibleCount;			// 생성할 바이블 개수
	float		m_EvolvedBibleDuration;			// 지속 시간
	float		m_EvolvedBibleCoolTime;			// 쿨타임
	float		m_SkillUseTime;			// 스킬 사용후 지난 시간.


public:
	// 이건 나중에 보물상자 만들때 필요할듯. 만렙이면 안뜨게 해야함.
	// 생각해보니 레벨업 할 때도 필요하네 
	int	GetSkillLevel()
	{
		return m_SkillLevel;
	}

	float GetBibleRadius()
	{
		return m_Radius;
	}

	float GetBibleDuration()
	{
		return m_EvolvedBibleDuration;
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
};