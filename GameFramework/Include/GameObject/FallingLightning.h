#pragma once
#include "Skill.h"
class CFallingLightning :
	public CSkill
{
	friend class CScene;

protected:
	CFallingLightning();
	CFallingLightning(const CFallingLightning& Obj);
	virtual ~CFallingLightning();

private:
	class CLightning*	m_Lightning;	
	float	m_LightningTimePassed;


	std::vector<std::string>	m_vecSequenceKey[1];

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);

public:
	void SetLightning(class CLightning* Lightning)
	{
		m_Lightning = Lightning;
	}

private:
	void GetLightning();

private:
	void CollisionBegin(CCollider* Src, CCollider* Dest);
	void CollisionEnd(CCollider* Src, CCollider* Dest);
	void LightningEnd();
};

