#pragma once

#include "Skill.h"

class CBibleBook :
    public CSkill
{
	friend class CScene;

protected:
	CBibleBook();
	CBibleBook(const CBibleBook& Obj);
	virtual ~CBibleBook();

private:
	class CBible*	m_Bible;	//BibleBook을 갖고 있는 Bible 객체를 갖고 있는다.
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
	void SetBible(class CBible* Bible)
	{
		m_Bible = Bible;
	}

private:
	void GetBibleLevel();

private:
	void CollisionBegin(CCollider* Src, CCollider* Dest);
	void CollisionEnd(CCollider* Src, CCollider* Dest);
	void InitEnd();
	void DestructEnd();
};

