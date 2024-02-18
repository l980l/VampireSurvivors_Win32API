#pragma once
#include "Scene.h"
class CMainScene :
    public CScene
{
	friend class CSceneManager;

protected:
	CMainScene();
	virtual ~CMainScene();

private:
	float			m_Time;				// 게임 시간
	float			m_SmallTime;		// 주기적으로 사용하는 시간
	float			m_SpawnTime;			// 상시로 몬스터 생성하는 시간
	bool			m_WhiteBatSpawn;				// WhiteBat 생성여부
	bool			m_FlowerBundleSpawn;	// 꽃 뭉치 소환 됐나 안됐나.
	bool			m_FlowerBundleDelete;	// 꽃 뭉치 삭제 이력.
	bool			m_SkeletonBundleSpawn;	// 스켈레톤 뭉치 소환 됐나 안됐나.
	bool			m_GhostBundleSpawn;	// Ghost 뭉치 소환 됐나 안됐나.
	bool			m_ReaperSpawn;

	EPlayer_Select	m_PlayerSelect;			

	// 무한맵을 위한 BackObj 멤버변수들
	CSharedPtr<class CBackObj>	m_Back1;
	CSharedPtr<class CBackObj>	m_Back2;
	CSharedPtr<class CBackObj>	m_Back3;
	CSharedPtr<class CBackObj>	m_Back4;
	CSharedPtr<class CBackObj>	m_Back5;
	CSharedPtr<class CBackObj>	m_Back6;
	CSharedPtr<class CBackObj>	m_Back7;
	CSharedPtr<class CBackObj>	m_Back8;
	CSharedPtr<class CBackObj>	m_Back9;

	CSharedPtr<class CGamePauseWindow>	m_GamePauseWindow;

public:
	bool Init();
	virtual void Update(float DeltaTime);

private:
	void CreateAnimationSequence();
	Vector2 SetSpawnPosition();

private:
	void CircleFlowerBundle();
	void SquareSkeletonBundle();
	void SquareGhostBundle();
	void GamePause();
};

