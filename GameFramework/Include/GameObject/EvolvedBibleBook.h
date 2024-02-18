#pragma once
#include "Skill.h"
class CEvolvedBibleBook :
    public CSkill
{
	friend class CScene;

protected:
	CEvolvedBibleBook();
	CEvolvedBibleBook(const CEvolvedBibleBook& Obj);
	virtual ~CEvolvedBibleBook();

private:
	class CEvolvedBible* m_EvolvedBible;	//CEvolveBibleBook을 갖고 있는 Bible 객체를 갖고 있는다.
	float	m_BibleTimePassed;
	float	m_PaperTimePassed;

	float	m_Angle;

	std::vector<std::string>	m_vecSequenceKey[1];

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);

public:
	void SetEvolvedBible(class CEvolvedBible* EvolvedBible)
	{
		m_EvolvedBible = EvolvedBible;
	}

private:
	void CollisionBegin(CCollider* Src, CCollider* Dest);
	void CollisionEnd(CCollider* Src, CCollider* Dest);
	void InitEnd();
	void DestructEnd();
};

