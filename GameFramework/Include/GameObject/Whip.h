#pragma once
#include "Skill.h"
class CWhip :
    public CSkill
{
	friend class CScene;

protected:
	CWhip();
	CWhip(const CWhip& Obj);
	virtual ~CWhip();

private:
	int			m_WhipCount;			// 생성할 채찍 개수
	float		m_WhipCoolTime;			// 쿨타임
	float		m_SkillUseTime;			// 스킬 사용후 지난 시간.
	float		m_SkillElementUseTime;	// 한 스킬 내의 채찍간의 시간 간격을 위한 변수.
	int			m_WhipSpawnCount;		// 채찍 생성수

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
	virtual void SkillLevelUp();				// 레벨업을 위한 함수. 충돌체 여기서 다시 생성.

};

