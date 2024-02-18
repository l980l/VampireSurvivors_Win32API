#pragma once
#include "Skill.h"
class CBible :
	public CSkill
{
	friend class CScene;

protected:
	CBible();
	CBible(const CBible& Obj);
	virtual ~CBible();

private:
	float		m_Radius;
	int			m_BibleCount;			// 생성할 바이블 개수
	float		m_BibleDuration;		// 지속 시간
	float		m_BibleCoolTime;		// 쿨타임
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
		return m_BibleDuration;
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
	virtual void SkillLevelUp();				// 레벨업을 위한 함수. 충돌체 여기서 다시 생성.

};