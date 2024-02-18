#pragma once

#include "Character.h"

struct SkillCoolDownInfo
{
	float	CoolDown;
	bool	CoolDownEnable;
};

class CPlayer :
    public CCharacter
{
	friend class CScene;

protected:
	CPlayer();
	CPlayer(const CPlayer& Obj);
	virtual ~CPlayer();

protected:
	int		m_PlayerDir;
	std::vector<std::string>	m_vecSequenceKey[2];
	std::vector<CSharedPtr<class CSkill>>	m_vecSkill;

	int		m_HP;
	int		m_HPMax;

	int		m_Level;			// 레벨
	int		m_Exp;				// Exp 보유량
	int		m_ExpMax;			// 레벨업에 필요한 Exp량

	int		m_KillCount;			// 죽인 몬스터 수


	CSharedPtr<class CWidgetComponent>	m_HPBar;
	CSharedPtr<class CWidgetComponent>	m_NameBar;

	bool	m_Damaged;
	float	m_DamagedTime;

	// 투사체 속도 증가, 데미지 증가, 지속 시간 아이템, 투사체 증가를 위한 변수들.
	float		m_AdditionalSkillSpeed;
	float		m_AdditionalSkillDamage;
	float		m_AdditionalSkillDuration;
	int			m_AdditionalSkillProjectile;

public:
	int GetPlayerDir()
	{
		return m_PlayerDir;
	}

	int GetPlayerLevel()
	{
		return m_Level;
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

	int GetKillCount()
	{
		return m_KillCount;
	}

	void KillCountUp()
	{
		m_KillCount++;
	}

	int GetGarlicLevel();
	int GetBibleLevel();
	int GetLightningLevel();
	int GetWhipLevel();

	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
	virtual float InflictDamage(float Damage);
	// 스킬마다 레벨업 함수를 따로 지정한다.
	void GarlicSkillLevelUp();
	void BibleSkillLevelUp();
	void LightningSkillLevelUp();
	void WhipSkillLevelUp();
	void BibleSkillEvolution();

	void SkillSpeedUp();
	void SkillDamageUp();
	void SkillDurationUp();
	void SkillProjectileUp();

	void CreateGarlicSkill();
	void CreateBibleSkill();
	void CreateLightningSkill();
	void CreateWhipSkill();

	virtual void ExpUp(int Exp);
	void HPUP(int HP);

	// 스킬 레벨 반환해주는 함수.
	int GetSkillLevel(std::string SkillName);

	ETreasure_Result TreasureRandom();
	std::list<std::string> LevelUpRandom();

private:
	void MoveUp();
	void MoveDown();
	void MoveRight();
	void MoveLeft();

private:
	void CollisionBegin(CCollider* Src, CCollider* Dest);
	void CollisionEnd(CCollider* Src, CCollider* Dest);
};

