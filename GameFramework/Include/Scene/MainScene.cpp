
#include "MainScene.h"
#include "SceneResource.h"
#include "Camera.h"
#include "../Input.h"
#include "../Widget/CharacterHUD.h"
#include "../Widget/TreasureBoxWindow.h"
#include "../Widget/GamePauseWindow.h"
#include "../GameObject/Player.h"
#include "../GameObject/Player2.h"
#include "../GameObject/Monster.h"
#include "../GameObject/BackObj.h"
#include "../GameObject/TileMap.h"
#include "../GameObject/Bat1.h"
#include "../GameObject/Bat2.h"
#include "../GameObject/Ghost.h"
#include "../GameObject/WhiteBat.h"
#include "../GameObject/LargeBat.h"
#include "../GameObject/Flower1.h"
#include "../GameObject/Flower2.h"
#include "../GameObject/Skeleton1.h"
#include "../GameObject/Skeleton2.h"
#include "../GameObject/Reaper.h"
#include "../GameObject/FirePot.h"
#include "../GameObject/TreasureBox.h"
#include "../GameManager.h"

CMainScene::CMainScene() :
	m_Time(0),
	m_SmallTime(0),
	m_SpawnTime(0.5f),
	m_FlowerBundleSpawn(false),
	m_FlowerBundleDelete(false),
	m_SkeletonBundleSpawn(false),
	m_GhostBundleSpawn(false)
{
}

CMainScene::~CMainScene()
{
}


bool CMainScene::Init()
{
	m_PlayerSelect = (EPlayer_Select)g_PlayerSelect;
	
	CreateAnimationSequence();

	GetSceneResource()->LoadSound("BGM", "MainBGM", true, "VS_Music_v04-01.ogg");
	GetSceneResource()->LoadSound("Effect", "MonsterHit", false, "VS_EnemyHit_v06-02.ogg");
	GetSceneResource()->LoadSound("Effect", "PlayerHit", false, "sfx_whistle.mp3");
	GetSceneResource()->LoadSound("Effect", "Gem", false, "VS_Gem_v04-01-B.ogg");
	GetSceneResource()->LoadSound("Effect", "LevelUp", false, "VS_LevelUp_v02-02.ogg");
	GetSceneResource()->LoadSound("Effect", "HPUP", false, "sfx_sounds_powerup2.ogg");
	GetSceneResource()->LoadSound("Effect", "Lightning", false, "sfx_lightningimpact.ogg");
	GetSceneResource()->LoadSound("Effect", "Whip", false, "sfx_sounds_impact15_2.ogg");
	GetSceneResource()->LoadSound("UI", "GameOver", false, "VS_GameOver_v02-01.ogg");

	GetSceneResource()->SoundPlay("MainBGM");

	GetSceneResource()->SetVolume(20);
	//
	GetSceneResource()->SetVolume("BGM", g_MusicVolume);
	GetSceneResource()->SetVolume("Effect", g_SoundVolume);
	GetSceneResource()->SetVolume("UI", g_SoundVolume);

	GetCamera()->SetResolution(1280.f, 720.f);
	GetCamera()->SetWorldResolution(2560.f, 2560.f);
	GetCamera()->SetTargetPivot(0.5f, 0.5f);

	//CreateObject<CBackObj>("BackObj");

	m_Back1 = CreateObject<CBackObj>("BackObj1", Vector2(-2560.f, -2560.f));
	m_Back2 = CreateObject<CBackObj>("BackObj2", Vector2(0.f, -2560.f));
	m_Back3 = CreateObject<CBackObj>("BackObj3", Vector2(2560.f, -2560.f));
	m_Back4 = CreateObject<CBackObj>("BackObj4", Vector2(-2560.f, 0.f));
	m_Back5 = CreateObject<CBackObj>("BackObj5", Vector2(0.f, 0.f));
	m_Back6 = CreateObject<CBackObj>("BackObj6", Vector2(2560.f, 0.f));
	m_Back7 = CreateObject<CBackObj>("BackObj7", Vector2(-2560.f, 2560.f));
	m_Back8 = CreateObject<CBackObj>("BackObj8", Vector2(0.f, 2560.f));
	m_Back9 = CreateObject<CBackObj>("BackObj9", Vector2(2560.f, 2560.f));

	if (m_PlayerSelect == EPlayer_Select::Player1)
	{
		CPlayer* Player = CreateObject<CPlayer>("Player");

		SetPlayer(Player);

		GetCamera()->SetTarget(Player);

	}

	else if (m_PlayerSelect == EPlayer_Select::Player2)
	{
		CPlayer2* Player = CreateObject<CPlayer2>("Player");

		SetPlayer(Player);

		GetCamera()->SetTarget(Player);
	}

	CTileMap* TileMap = CreateObject<CTileMap>("TileMap");

	TileMap->LoadFileName("MainMap2.tmp", MAP_PATH);

	CreateWidgetWindow<CCharacterHUD>("CharacterHUD");


	// 몬스터 생성을 위한 랜덤.
	srand((unsigned int)time(0));

	int Random = rand();

	// 일시정지 키 설정
	CInput::GetInst()->AddBindFunction<CMainScene>("esc",
		Input_Type::Down, this, &CMainScene::GamePause);

	return true;
}

void CMainScene::Update(float DeltaTime)
{
	// 4번으로 간 경우
	if (m_Player->GetPos().x < m_Back5->GetPos().x)
	{
		m_Back3->SetPos(m_Back3->GetPos() - Vector2(2560.f *3, 0));
		m_Back6->SetPos(m_Back6->GetPos() - Vector2(2560.f *3, 0));
		m_Back9->SetPos(m_Back9->GetPos() - Vector2(2560.f *3, 0));

		CBackObj* temp1 = m_Back1;
		CBackObj* temp2 = m_Back2;
		CBackObj* temp3 = m_Back3;
		CBackObj* temp4 = m_Back4;
		CBackObj* temp5 = m_Back5;
		CBackObj* temp6 = m_Back6;
		CBackObj* temp7 = m_Back7;
		CBackObj* temp8 = m_Back8;
		CBackObj* temp9 = m_Back9;

		m_Back1 = m_Back3;
		m_Back4 = m_Back6;
		m_Back7 = m_Back9;

		m_Back2 = temp1;
		m_Back5 = temp4;
		m_Back8 = temp7;

		m_Back3 = temp2;
		m_Back6 = temp5;
		m_Back9 = temp8;
	}

	// 6번으로 간 경우
	else if (m_Player->GetPos().x > (m_Back5->GetPos().x + m_Back5->GetSize().x))
	{
		m_Back1->SetPos(m_Back1->GetPos() + Vector2(2560.f * 3, 0));
		m_Back4->SetPos(m_Back4->GetPos() + Vector2(2560.f * 3, 0));
		m_Back7->SetPos(m_Back7->GetPos() + Vector2(2560.f * 3, 0));

		CBackObj* temp1 = m_Back1;
		CBackObj* temp2 = m_Back2;
		CBackObj* temp3 = m_Back3;
		CBackObj* temp4 = m_Back4;
		CBackObj* temp5 = m_Back5;
		CBackObj* temp6 = m_Back6;
		CBackObj* temp7 = m_Back7;
		CBackObj* temp8 = m_Back8;
		CBackObj* temp9 = m_Back9;

		m_Back3 = m_Back1;
		m_Back6 = m_Back4;
		m_Back9 = m_Back7;

		m_Back2 = temp3;
		m_Back5 = temp6;
		m_Back8 = temp9;

		m_Back1 = temp2;
		m_Back4 = temp5;
		m_Back7 = temp8;
	}

	// 2번으로 간 경우
	else if (m_Player->GetPos().y < m_Back5->GetPos().y)
	{
		m_Back7->SetPos(m_Back7->GetPos() - Vector2(0.f, 2560.f * 3));
		m_Back8->SetPos(m_Back8->GetPos() - Vector2(0.f, 2560.f * 3));
		m_Back9->SetPos(m_Back9->GetPos() - Vector2(0.f, 2560.f * 3));

		CBackObj* temp1 = m_Back1;
		CBackObj* temp2 = m_Back2;
		CBackObj* temp3 = m_Back3;
		CBackObj* temp4 = m_Back4;
		CBackObj* temp5 = m_Back5;
		CBackObj* temp6 = m_Back6;
		CBackObj* temp7 = m_Back7;
		CBackObj* temp8 = m_Back8;
		CBackObj* temp9 = m_Back9;

		m_Back1 = m_Back7;
		m_Back2 = m_Back8;
		m_Back3 = m_Back9;

		m_Back4 = temp1;
		m_Back5 = temp2;
		m_Back6 = temp3;

		m_Back7 = temp4;
		m_Back8 = temp5;
		m_Back9 = temp6;
	}

	// 8번으로 간 경우
	else if (m_Player->GetPos().y > (m_Back5->GetPos().y + m_Back5->GetSize().y))
	{
		m_Back1->SetPos(m_Back1->GetPos() + Vector2(0.f, 2560.f * 3));
		m_Back2->SetPos(m_Back2->GetPos() + Vector2(0.f, 2560.f * 3));
		m_Back3->SetPos(m_Back3->GetPos() + Vector2(0.f, 2560.f * 3));

		CBackObj* temp1 = m_Back1;
		CBackObj* temp2 = m_Back2;
		CBackObj* temp3 = m_Back3;
		CBackObj* temp4 = m_Back4;
		CBackObj* temp5 = m_Back5;
		CBackObj* temp6 = m_Back6;
		CBackObj* temp7 = m_Back7;
		CBackObj* temp8 = m_Back8;
		CBackObj* temp9 = m_Back9;

		m_Back7 = m_Back1;
		m_Back8 = m_Back2;
		m_Back9 = m_Back3;

		m_Back4 = temp7;
		m_Back5 = temp8;
		m_Back6 = temp9;

		m_Back1 = temp4;
		m_Back2 = temp5;
		m_Back3 = temp6;
	}

	m_Time += DeltaTime;
	m_SmallTime += DeltaTime;

	// 이벤트
	{
		// WhiteBat 소환
		if (m_Time >= 40 && !m_WhiteBatSpawn)
		{
			m_WhiteBatSpawn = true;
			CFirePot* FirePot1 = CreateObject<CFirePot>("FirePot", SetSpawnPosition());
			CFirePot* FirePot2 = CreateObject<CFirePot>("FirePot", SetSpawnPosition());
			
			CWhiteBat* WhiteBat = CreateObject<CWhiteBat>("WhiteBat", SetSpawnPosition());
			AddMonster(WhiteBat);
		}

		// 꽃 무리 생성
		if (m_Time >= 80 && !m_FlowerBundleSpawn && !m_FlowerBundleDelete)
		{
			CircleFlowerBundle();
			m_FlowerBundleSpawn = true;
			CFirePot* FirePot1 = CreateObject<CFirePot>("FirePot", SetSpawnPosition());
			CFirePot* FirePot2 = CreateObject<CFirePot>("FirePot", SetSpawnPosition());
		}

		// 꽃 무리 Kill
		if (m_Time >= 120 && m_FlowerBundleSpawn && !m_FlowerBundleDelete)
		{
			ClearMonsterBundle();
			m_FlowerBundleSpawn = false;
			m_FlowerBundleDelete = true;
			CFirePot* FirePot1 = CreateObject<CFirePot>("FirePot", SetSpawnPosition());
			CFirePot* FirePot2 = CreateObject<CFirePot>("FirePot", SetSpawnPosition());

			CWhiteBat* WhiteBat = CreateObject<CWhiteBat>("WhiteBat", SetSpawnPosition());
			AddMonster(WhiteBat);
		}

		// 스켈레톤 무리 생성
		if (m_Time >= 160 && !m_SkeletonBundleSpawn)
		{
			SquareSkeletonBundle();

			m_SkeletonBundleSpawn = true;
			CFirePot* FirePot1 = CreateObject<CFirePot>("FirePot", SetSpawnPosition());
			CFirePot* FirePot2 = CreateObject<CFirePot>("FirePot", SetSpawnPosition());

			CWhiteBat* WhiteBat = CreateObject<CWhiteBat>("WhiteBat", SetSpawnPosition());
			AddMonster(WhiteBat);
		}

		// 유령 무리 생성
		if (m_Time >= 200 && !m_GhostBundleSpawn)
		{
			SquareGhostBundle();

			m_GhostBundleSpawn = true;
			CFirePot* FirePot1 = CreateObject<CFirePot>("FirePot", SetSpawnPosition());
			CFirePot* FirePot2 = CreateObject<CFirePot>("FirePot", SetSpawnPosition());

			CWhiteBat* WhiteBat = CreateObject<CWhiteBat>("WhiteBat", SetSpawnPosition());
			AddMonster(WhiteBat);
		}

		// 사신 생성
		if (m_Time >= 240 && !m_ReaperSpawn)
		{
			CReaper* Reaper = CreateObject<CReaper>("Reaper", SetSpawnPosition());
			AddMonster(Reaper);

			m_ReaperSpawn = true;
			CFirePot* FirePot1 = CreateObject<CFirePot>("FirePot", SetSpawnPosition());
			CFirePot* FirePot2 = CreateObject<CFirePot>("FirePot", SetSpawnPosition());
		}
	}

	// 상시 생성

	if (m_SmallTime >= m_SpawnTime)
	{
		/*CTreasureBox* Box = CreateObject<CTreasureBox>("TreasureBox", SetSpawnPosition());
		CFirePot* FirePot = CreateObject<CFirePot>("FirePot", SetSpawnPosition());*/

		if (m_Time >= 0 && m_Time <= 100)
		{
			CBat1* Bat1 = CreateObject<CBat1>("Bat1", SetSpawnPosition());
			AddMonster(Bat1);
		}

		if (m_Time >= 50 && m_Time <= 150)
		{
			CBat2* Bat2 = CreateObject<CBat2>("Bat2", SetSpawnPosition());
			AddMonster(Bat2);
		}

		if (m_Time >= 100 && m_Time <= 200)
		{
			CSkeleton1* Skeleton1 = CreateObject<CSkeleton1>("Skeleton1", SetSpawnPosition());
			AddMonster(Skeleton1);
		}

		if (m_Time >= 150 && m_Time <= 250)
		{
			CLargeBat* LargeBat = CreateObject<CLargeBat>("LargeBat", SetSpawnPosition());
			AddMonster(LargeBat);
		}

		if (m_Time >= 200 && m_Time <= 300)
		{
			CGhost* Ghost = CreateObject<CGhost>("Ghost", SetSpawnPosition());
			AddMonster(Ghost);
		}
		
		m_SmallTime -= m_SpawnTime;
	}

	CScene::Update(DeltaTime);
}

void CMainScene::CreateAnimationSequence()
{
	if (m_PlayerSelect == EPlayer_Select::Player1)
	{
		// 일반 걷기
		GetSceneResource()->CreateAnimationSequence("PlayerRightWalk",
			"PlayerRightWalk", TEXT("Texture/Player/PlayerRightWalk.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("PlayerRightWalk", 65.f * i, 0.f,
				65.f, 74.f);
		}

		GetSceneResource()->SetColorKey("PlayerRightWalk", 255, 0, 255);


		GetSceneResource()->CreateAnimationSequence("PlayerLeftWalk",
			"PlayerLeftWalk", TEXT("Texture/Player/PlayerLeftWalk.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("PlayerLeftWalk", 65.f * i, 0.f,
				65.f, 74.f);
		}

		GetSceneResource()->SetColorKey("PlayerLeftWalk", 255, 0, 255);

		// 피격
		GetSceneResource()->CreateAnimationSequence("DamagedPlayerRightWalk",
			"DamagedPlayerRightWalk", TEXT("Texture/Player/DamagedPlayerRightWalk.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("DamagedPlayerRightWalk", 65.f * i, 0.f,
				65.f, 74.f);
		}

		GetSceneResource()->SetColorKey("DamagedPlayerRightWalk", 255, 0, 255);


		GetSceneResource()->CreateAnimationSequence("DamagedPlayerLeftWalk",
			"DamagedPlayerLeftWalk", TEXT("Texture/Player/DamagedPlayerLeftWalk.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("DamagedPlayerLeftWalk", 65.f * i, 0.f,
				65.f, 74.f);
		}

		GetSceneResource()->SetColorKey("DamagedPlayerLeftWalk", 255, 0, 255);


		// 걷기 잔상
		GetSceneResource()->CreateAnimationSequence("PlayerRightWalk2",
			"PlayerRightWalk2", TEXT("Texture/Player/PlayerRightWalk2.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("PlayerRightWalk2", 69.f * i, 0.f,
				69.f, 74.f);
		}

		GetSceneResource()->SetColorKey("PlayerRightWalk2", 255, 0, 255);


		GetSceneResource()->CreateAnimationSequence("PlayerLeftWalk2",
			"PlayerLeftWalk2", TEXT("Texture/Player/PlayerLeftWalk2.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("PlayerLeftWalk2", 69.f * i, 0.f,
				69.f, 74.f);
		}

		GetSceneResource()->SetColorKey("PlayerLeftWalk2", 255, 0, 255);

	}

	else if (m_PlayerSelect == EPlayer_Select::Player2)
	{
		// 일반 걷기
		GetSceneResource()->CreateAnimationSequence("Player2RightWalk",
			"Player2RightWalk", TEXT("Texture/Player/Player2RightWalk.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("Player2RightWalk", 74.f * i, 0.f,
				74.f, 82.f);
		}

		GetSceneResource()->SetColorKey("Player2RightWalk", 255, 0, 255);


		GetSceneResource()->CreateAnimationSequence("Player2LeftWalk",
			"Player2LeftWalk", TEXT("Texture/Player/Player2LeftWalk.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("Player2LeftWalk", 74.f * i, 0.f,
				74.f, 82.f);
		}

		GetSceneResource()->SetColorKey("Player2LeftWalk", 255, 0, 255);

		// 피격
		GetSceneResource()->CreateAnimationSequence("DamagedPlayer2RightWalk",
			"DamagedPlayer2RightWalk", TEXT("Texture/Player/DamagedPlayer2RightWalk.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("DamagedPlayer2RightWalk", 74.f * i, 0.f,
				74.f, 82.f);
		}

		GetSceneResource()->SetColorKey("DamagedPlayer2RightWalk", 255, 0, 255);


		GetSceneResource()->CreateAnimationSequence("DamagedPlayer2LeftWalk",
			"DamagedPlayer2LeftWalk", TEXT("Texture/Player/DamagedPlayer2LeftWalk.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("DamagedPlayer2LeftWalk", 74.f * i, 0.f,
				74.f, 82.f);
		}

		GetSceneResource()->SetColorKey("DamagedPlayer2LeftWalk", 255, 0, 255);

		// 걷기 잔상
		GetSceneResource()->CreateAnimationSequence("Player2RightWalk2",
			"Player2RightWalk2", TEXT("Texture/Player/Player2RightWalk2.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("Player2RightWalk2", 65.f * i, 0.f,
				65.f, 74.f);
		}

		GetSceneResource()->SetColorKey("Player2RightWalk2", 255, 0, 255);


		GetSceneResource()->CreateAnimationSequence("Player2LeftWalk2",
			"Player2LeftWalk2", TEXT("Texture/Player/Player2LeftWalk2.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("Player2LeftWalk2", 65.f * i, 0.f,
				65.f, 74.f);
		}

		GetSceneResource()->SetColorKey("Player2LeftWalk2", 255, 0, 255);

	}

	// 박쥐 몬스터 1
	{
		// 기본 right
		GetSceneResource()->CreateAnimationSequence("Bat1Right",
			"Bat1Right", TEXT("Texture/Monster/Bat1/Bat1Right.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("Bat1Right", 47.5f * i, 0.f,
				47.5f, 52.f);
		}

		GetSceneResource()->SetColorKey("Bat1Right", 255, 0, 255);

		// 기본 left
		GetSceneResource()->CreateAnimationSequence("Bat1",
			"Bat1", TEXT("Texture/Monster/Bat1/Bat1.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("Bat1", 47.5f * i, 0.f,
				47.5f, 52.f);
		}

		GetSceneResource()->SetColorKey("Bat1", 255, 0, 255);

		// 사망 right
		GetSceneResource()->CreateAnimationSequence("Bat1DeathRight",
			"Bat1DeathRight", TEXT("Texture/Monster/Bat1/Bat1DeathRight.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 10; ++i)
		{
			GetSceneResource()->AddAnimationFrame("Bat1DeathRight", 1530 - 142.8f * (1 + i), 0.f,
				142.8f, 83.f);
		}

		GetSceneResource()->SetColorKey("Bat1DeathRight", 255, 0, 255);

		// 사망 left
		GetSceneResource()->CreateAnimationSequence("Bat1Death",
			"Bat1Death", TEXT("Texture/Monster/Bat1/Bat1Death.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 10; ++i)
		{
			GetSceneResource()->AddAnimationFrame("Bat1Death", 142.8f * i, 0.f,
				142.8f, 83.f);
		}

		GetSceneResource()->SetColorKey("Bat1Death", 255, 0, 255);

		// 피격 right
		GetSceneResource()->CreateAnimationSequence("DamagedBat1Right",
			"DamagedBat1Right", TEXT("Texture/Monster/Bat1/DamagedBat1Right.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("DamagedBat1Right", 47.5f * i, 0.f,
				47.5f, 52.f);
		}

		GetSceneResource()->SetColorKey("DamagedBat1Right", 255, 0, 255);

		// 피격 left
		GetSceneResource()->CreateAnimationSequence("DamagedBat1",
			"DamagedBat1", TEXT("Texture/Monster/Bat1/DamagedBat1.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("DamagedBat1", 47.5f * i, 0.f,
				47.5f, 52.f);
		}

		GetSceneResource()->SetColorKey("DamagedBat1", 255, 0, 255);
	}

	// 박쥐 몬스터 2
	{
		// 기본 right
		GetSceneResource()->CreateAnimationSequence("Bat2Right",
			"Bat2Right", TEXT("Texture/Monster/Bat2/Bat2Right.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("Bat2Right", 70.5f * i, 0.f,
				70.5f, 62.f);
		}

		GetSceneResource()->SetColorKey("Bat2Right", 255, 0, 255);

		// 기본 left
		GetSceneResource()->CreateAnimationSequence("Bat2",
			"Bat2", TEXT("Texture/Monster/Bat2/Bat2.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("Bat2", 70.5f * i, 0.f,
				70.5f, 62.f);
		}

		GetSceneResource()->SetColorKey("Bat2", 255, 0, 255);

		// 사망 right
		GetSceneResource()->CreateAnimationSequence("Bat2DeathRight",
			"Bat2DeathRight", TEXT("Texture/Monster/Bat2/Bat2DeathRight.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 12; ++i)
		{
			GetSceneResource()->AddAnimationFrame("Bat2DeathRight", 1112 - 92.6f * (1 + i), 0.f,
				92.6f, 102.f);
		}

		GetSceneResource()->SetColorKey("Bat2DeathRight", 255, 0, 255);

		// 사망 left
		GetSceneResource()->CreateAnimationSequence("Bat2Death",
			"Bat2Death", TEXT("Texture/Monster/Bat2/Bat2Death.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 12; ++i)
		{
			GetSceneResource()->AddAnimationFrame("Bat2Death", 92.6f * i, 0.f,
				92.6f, 102.f);
		}

		GetSceneResource()->SetColorKey("Bat2Death", 255, 0, 255);

		// 피격 right
		GetSceneResource()->CreateAnimationSequence("DamagedBat2Right",
			"DamagedBat2Right", TEXT("Texture/Monster/Bat2/DamagedBat2Right.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("DamagedBat2Right", 70.5f * i, 0.f,
				70.5f, 62.f);
		}

		GetSceneResource()->SetColorKey("DamagedBat2Right", 255, 0, 255);

		// 피격 left
		GetSceneResource()->CreateAnimationSequence("DamagedBat2",
			"DamagedBat2", TEXT("Texture/Monster/Bat2/DamagedBat2.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("DamagedBat2", 70.5f * i, 0.f,
				70.5f, 62.f);
		}

		GetSceneResource()->SetColorKey("DamagedBat2", 255, 0, 255);
	}

	// White Bat
	{
		// 기본 right
		GetSceneResource()->CreateAnimationSequence("WhiteBatRight",
			"WhiteBatRight", TEXT("Texture/Monster/WhiteBat/WhiteBatRight.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("WhiteBatRight", 66.75f * i, 0.f,
				66.75f, 67.f);
		}

		GetSceneResource()->SetColorKey("WhiteBatRight", 255, 0, 255);

		// 기본 left
		GetSceneResource()->CreateAnimationSequence("WhiteBat",
			"WhiteBat", TEXT("Texture/Monster/WhiteBat/WhiteBat.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("WhiteBat", 66.75f * i, 0.f,
				66.75f, 67.f);
		}

		GetSceneResource()->SetColorKey("WhiteBat", 255, 0, 255);

		// 사망 right
		GetSceneResource()->CreateAnimationSequence("WhiteBatDeathRight",
			"WhiteBatDeathRight", TEXT("Texture/Monster/WhiteBat/WhiteBatDeathRight.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 12; ++i)
		{
			GetSceneResource()->AddAnimationFrame("WhiteBatDeathRight", 1213 - 101.08f * (1 + i), 0.f,
				101.08f, 79.f);
		}

		GetSceneResource()->SetColorKey("WhiteBatDeathRight", 255, 0, 255);

		// 사망 left
		GetSceneResource()->CreateAnimationSequence("WhiteBatDeath",
			"WhiteBatDeath", TEXT("Texture/Monster/WhiteBat/WhiteBatDeath.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 12; ++i)
		{
			GetSceneResource()->AddAnimationFrame("WhiteBatDeath", 101.08f * i, 0.f,
				101.08f, 79.f);
		}

		GetSceneResource()->SetColorKey("WhiteBatDeath", 255, 0, 255);
	}

	// Large 박쥐
	{
		// 기본 right
		GetSceneResource()->CreateAnimationSequence("LargeBatRight",
			"LargeBatRight", TEXT("Texture/Monster/LargeBat/LargeBatRight.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("LargeBatRight", 199.25f * i, 0.f,
				199.25f, 102.f);
		}

		GetSceneResource()->SetColorKey("LargeBatRight", 255, 0, 255);

		// 기본 left
		GetSceneResource()->CreateAnimationSequence("LargeBat",
			"LargeBat", TEXT("Texture/Monster/LargeBat/LargeBat.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("LargeBat", 199.25f * i, 0.f,
				199.25f, 102.f);
		}

		GetSceneResource()->SetColorKey("LargeBat", 255, 0, 255);

		// 사망 right
		GetSceneResource()->CreateAnimationSequence("LargeBatDeathRight",
			"LargeBatDeathRight", TEXT("Texture/Monster/LargeBat/LargeBatDeathRight.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 12; ++i)
		{
			GetSceneResource()->AddAnimationFrame("LargeBatDeathRight", 2402 - 200.1f * (1 + i), 0.f,
				200.1f, 167.f);
		}

		GetSceneResource()->SetColorKey("LargeBatDeathRight", 255, 0, 255);

		// 사망 left
		GetSceneResource()->CreateAnimationSequence("LargeBatDeath",
			"LargeBatDeath", TEXT("Texture/Monster/LargeBat/LargeBatDeath.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 12; ++i)
		{
			GetSceneResource()->AddAnimationFrame("LargeBatDeath", 200.1f * i, 0.f,
				200.1f, 167.f);
		}

		GetSceneResource()->SetColorKey("LargeBatDeath", 255, 0, 255);

		// 피격 right
		GetSceneResource()->CreateAnimationSequence("DamagedLargeBatRight",
			"DamagedLargeBatRight", TEXT("Texture/Monster/LargeBat/DamagedLargeBatRight.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("DamagedLargeBatRight", 199.25f * i, 0.f,
				199.25f, 102.f);
		}

		GetSceneResource()->SetColorKey("DamagedLargeBatRight", 255, 0, 255);

		// 피격 left
		GetSceneResource()->CreateAnimationSequence("DamagedLargeBat",
			"DamagedLargeBat", TEXT("Texture/Monster/LargeBat/DamagedLargeBat.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("DamagedLargeBat", 199.25f * i, 0.f,
				199.25f, 102.f);
		}

		GetSceneResource()->SetColorKey("DamagedLargeBat", 255, 0, 255);
	}

	// Flower1
	{
		// 기본 right
		GetSceneResource()->CreateAnimationSequence("Flower1Right",
			"Flower1Right", TEXT("Texture/Monster/Flower1/Flower1Right.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("Flower1Right", 91.75f * i, 0.f,
				91.75f, 70.f);
		}

		GetSceneResource()->SetColorKey("Flower1Right", 255, 0, 255);

		// 기본 left
		GetSceneResource()->CreateAnimationSequence("Flower1",
			"Flower1", TEXT("Texture/Monster/Flower1/Flower1.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("Flower1", 91.75f * i, 0.f,
				91.75f, 70.f);
		}

		GetSceneResource()->SetColorKey("Flower1", 255, 0, 255);

		// 사망 right
		GetSceneResource()->CreateAnimationSequence("Flower1DeathRight",
			"Flower1DeathRight", TEXT("Texture/Monster/Flower1/Flower1DeathRight.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 12; ++i)
		{
			GetSceneResource()->AddAnimationFrame("Flower1DeathRight", 1380 - 115.f * (1 + i), 0.f,
				115.f, 102.f);
		}

		GetSceneResource()->SetColorKey("Flower1DeathRight", 255, 0, 255);

		// 사망 left
		GetSceneResource()->CreateAnimationSequence("Flower1Death",
			"Flower1Death", TEXT("Texture/Monster/Flower1/Flower1Death.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 12; ++i)
		{
			GetSceneResource()->AddAnimationFrame("Flower1Death", 115.f * i, 0.f,
				115.f, 102.f);
		}

		GetSceneResource()->SetColorKey("Flower1Death", 255, 0, 255);

		// 피격 right
		GetSceneResource()->CreateAnimationSequence("DamagedFlower1Right",
			"DamagedFlower1Right", TEXT("Texture/Monster/Flower1/DamagedFlower1Right.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("DamagedFlower1Right", 91.75f * i, 0.f,
				91.75f, 70.f);
		}

		GetSceneResource()->SetColorKey("DamagedFlower1Right", 255, 0, 255);

		// 피격 left
		GetSceneResource()->CreateAnimationSequence("DamagedFlower1",
			"DamagedFlower1", TEXT("Texture/Monster/Flower1/DamagedFlower1.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("DamagedFlower1", 91.75f * i, 0.f,
				91.75f, 70.f);
		}

		GetSceneResource()->SetColorKey("DamagedFlower1", 255, 0, 255);
	}

	// Flower2
	{
		// 기본 right
		GetSceneResource()->CreateAnimationSequence("Flower2Right",
			"Flower2Right", TEXT("Texture/Monster/Flower2/Flower2Right.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("Flower2Right", 91.75f * i, 0.f,
				91.75f, 70.f);
		}

		GetSceneResource()->SetColorKey("Flower2Right", 255, 0, 255);

		// 기본 left
		GetSceneResource()->CreateAnimationSequence("Flower2",
			"Flower2", TEXT("Texture/Monster/Flower2/Flower2.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("Flower2", 91.75f * i, 0.f,
				91.75f, 70.f);
		}

		GetSceneResource()->SetColorKey("Flower2", 255, 0, 255);

		// 사망 right
		GetSceneResource()->CreateAnimationSequence("Flower2DeathRight",
			"Flower2DeathRight", TEXT("Texture/Monster/Flower2/Flower2DeathRight.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 12; ++i)
		{
			GetSceneResource()->AddAnimationFrame("Flower2DeathRight", 1380 - 115.f * (1 + i), 0.f,
				115.f, 102.f);
		}

		GetSceneResource()->SetColorKey("Flower2DeathRight", 255, 0, 255);

		// 사망 left
		GetSceneResource()->CreateAnimationSequence("Flower2Death",
			"Flower2Death", TEXT("Texture/Monster/Flower2/Flower2Death.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 12; ++i)
		{
			GetSceneResource()->AddAnimationFrame("Flower2Death", 115.f * i, 0.f,
				115.f, 102.f);
		}

		GetSceneResource()->SetColorKey("Flower2Death", 255, 0, 255);

		// 피격 right
		GetSceneResource()->CreateAnimationSequence("DamagedFlower2Right",
			"DamagedFlower2Right", TEXT("Texture/Monster/Flower2/DamagedFlower2Right.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("DamagedFlower2Right", 91.75f * i, 0.f,
				91.75f, 70.f);
		}

		GetSceneResource()->SetColorKey("DamagedFlower2Right", 255, 0, 255);

		// 피격 left
		GetSceneResource()->CreateAnimationSequence("DamagedFlower2",
			"DamagedFlower2", TEXT("Texture/Monster/Flower2/DamagedFlower2.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("DamagedFlower2", 91.75f * i, 0.f,
				91.75f, 70.f);
		}

		GetSceneResource()->SetColorKey("DamagedFlower2", 255, 0, 255);
	}

	// Skeleton1
	{
		// 기본 right
		GetSceneResource()->CreateAnimationSequence("Skeleton1Right",
			"Skeleton1Right", TEXT("Texture/Monster/Skeleton1/Skeleton1Right.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("Skeleton1Right", 119.25f * i, 0.f,
				119.25f, 85.f);
		}

		GetSceneResource()->SetColorKey("Skeleton1Right", 255, 0, 255);

		// 기본 left
		GetSceneResource()->CreateAnimationSequence("Skeleton1",
			"Skeleton1", TEXT("Texture/Monster/Skeleton1/Skeleton1.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("Skeleton1", 119.25f * i, 0.f,
				119.25f, 85.f);
		}

		GetSceneResource()->SetColorKey("Skeleton1", 255, 0, 255);

		// 사망 right
		GetSceneResource()->CreateAnimationSequence("Skeleton1DeathRight",
			"Skeleton1DeathRight", TEXT("Texture/Monster/Skeleton1/Skeleton1DeathRight.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 10; ++i)
		{
			GetSceneResource()->AddAnimationFrame("Skeleton1DeathRight", 1165 - 116.5f * (1 + i), 0.f,
				116.5f, 115.f);
		}

		GetSceneResource()->SetColorKey("Skeleton1DeathRight", 255, 0, 255);

		// 사망 left
		GetSceneResource()->CreateAnimationSequence("Skeleton1Death",
			"Skeleton1Death", TEXT("Texture/Monster/Skeleton1/Skeleton1Death.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 10; ++i)
		{
			GetSceneResource()->AddAnimationFrame("Skeleton1Death", 116.5f * i, 0.f,
				116.5f, 115.f);
		}

		GetSceneResource()->SetColorKey("Skeleton1Death", 255, 0, 255);

		// 피격 right
		GetSceneResource()->CreateAnimationSequence("DamagedSkeleton1Right",
			"DamagedSkeleton1Right", TEXT("Texture/Monster/Skeleton1/DamagedSkeleton1Right.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("DamagedSkeleton1Right", 119.25f * i, 0.f,
				119.25f, 85.f);
		}

		GetSceneResource()->SetColorKey("DamagedSkeleton1Right", 255, 0, 255);

		// 피격 left
		GetSceneResource()->CreateAnimationSequence("DamagedSkeleton1",
			"DamagedSkeleton1", TEXT("Texture/Monster/Skeleton1/DamagedSkeleton1.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("DamagedSkeleton1", 119.25f * i, 0.f,
				119.25f, 85.f);
		}

		GetSceneResource()->SetColorKey("DamagedSkeleton1", 255, 0, 255);
	}

	// Skeleton2
	{
		// 기본 right
		GetSceneResource()->CreateAnimationSequence("Skeleton2Right",
			"Skeleton2Right", TEXT("Texture/Monster/Skeleton2/Skeleton2Right.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("Skeleton2Right", 105.5f * i, 0.f,
				105.5f, 90.f);
		}

		GetSceneResource()->SetColorKey("Skeleton2Right", 255, 0, 255);

		// 기본 left
		GetSceneResource()->CreateAnimationSequence("Skeleton2",
			"Skeleton2", TEXT("Texture/Monster/Skeleton2/Skeleton2.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("Skeleton2", 105.5f * i, 0.f,
				105.5f, 90.f);
		}

		GetSceneResource()->SetColorKey("Skeleton2", 255, 0, 255);

		// 사망 right
		GetSceneResource()->CreateAnimationSequence("Skeleton2DeathRight",
			"Skeleton2DeathRight", TEXT("Texture/Monster/Skeleton2/Skeleton2DeathRight.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 10; ++i)
		{
			GetSceneResource()->AddAnimationFrame("Skeleton2DeathRight", 1530 - 153.f * (1 + i), 0.f,
				153.f, 160.f);
		}

		GetSceneResource()->SetColorKey("Skeleton2DeathRight", 255, 0, 255);

		// 사망 left
		GetSceneResource()->CreateAnimationSequence("Skeleton2Death",
			"Skeleton2Death", TEXT("Texture/Monster/Skeleton2/Skeleton2Death.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 10; ++i)
		{
			GetSceneResource()->AddAnimationFrame("Skeleton2Death", 153.f * i, 0.f,
				153.f, 160.f);
		}

		GetSceneResource()->SetColorKey("Skeleton2Death", 255, 0, 255);

		// 피격 right
		GetSceneResource()->CreateAnimationSequence("DamagedSkeleton2Right",
			"DamagedSkeleton2Right", TEXT("Texture/Monster/Skeleton2/DamagedSkeleton2Right.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("DamagedSkeleton2Right", 105.5f * i, 0.f,
				105.5f, 90.f);
		}

		GetSceneResource()->SetColorKey("DamagedSkeleton2Right", 255, 0, 255);

		// 피격 left
		GetSceneResource()->CreateAnimationSequence("DamagedSkeleton2",
			"DamagedSkeleton2", TEXT("Texture/Monster/Skeleton2/DamagedSkeleton2.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("DamagedSkeleton2", 105.5f * i, 0.f,
				105.5f, 90.f);
		}

		GetSceneResource()->SetColorKey("DamagedSkeleton2", 255, 0, 255);
	}

	// 유령
	{
		// 기본 right
		GetSceneResource()->CreateAnimationSequence("GhostRight",
			"GhostRight", TEXT("Texture/Monster/Ghost/GhostRight.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("GhostRight", 80.f * i, 0.f,
				80.f, 80.f);
		}

		GetSceneResource()->SetColorKey("GhostRight", 255, 0, 255);

		// 기본 left
		GetSceneResource()->CreateAnimationSequence("Ghost",
			"Ghost", TEXT("Texture/Monster/Ghost/Ghost.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("Ghost", 80.f * i, 0.f,
				80.f, 80.f);
		}

		GetSceneResource()->SetColorKey("Ghost", 255, 0, 255);

		// 사망 right
		GetSceneResource()->CreateAnimationSequence("GhostDeathRight",
			"GhostDeathRight", TEXT("Texture/Monster/Ghost/GhostDeathRight.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 10; ++i)
		{
			GetSceneResource()->AddAnimationFrame("GhostDeathRight", 750 - 75.f * (1 + i), 0.f,
				75.f, 80.f);
		}

		GetSceneResource()->SetColorKey("GhostDeathRight", 255, 0, 255);

		// 사망 left
		GetSceneResource()->CreateAnimationSequence("GhostDeath",
			"GhostDeath", TEXT("Texture/Monster/Ghost/GhostDeath.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 10; ++i)
		{
			GetSceneResource()->AddAnimationFrame("GhostDeath", 75.f * i, 0.f,
				75.f, 80.f);
		}

		GetSceneResource()->SetColorKey("GhostDeath", 255, 0, 255);

		// 피격 right
		GetSceneResource()->CreateAnimationSequence("DamagedGhostRight",
			"DamagedGhostRight", TEXT("Texture/Monster/Ghost/DamagedGhostRight.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("DamagedGhostRight", 80.f * i, 0.f,
				80.f, 80.f);
		}

		GetSceneResource()->SetColorKey("DamagedGhostRight", 255, 0, 255);

		// 피격 left
		GetSceneResource()->CreateAnimationSequence("DamagedGhost",
			"DamagedGhost", TEXT("Texture/Monster/Ghost/DamagedGhost.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("DamagedGhost", 80.f * i, 0.f,
				80.f, 80.f);
		}

		GetSceneResource()->SetColorKey("DamagedGhost", 255, 0, 255);
	}

	// Reaper
	{
		// 기본 right
		GetSceneResource()->CreateAnimationSequence("ReaperRight",
			"ReaperRight", TEXT("Texture/Monster/Reaper/ReaperRight.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("ReaperRight", 179.25f * i, 0.f,
				179.25f, 123.f);
		}

		GetSceneResource()->SetColorKey("ReaperRight", 255, 0, 255);

		// 기본 left
		GetSceneResource()->CreateAnimationSequence("Reaper",
			"Reaper", TEXT("Texture/Monster/Reaper/Reaper.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("Reaper", 179.25f * i, 0.f,
				179.25f, 123.f);
		}

		GetSceneResource()->SetColorKey("Reaper", 255, 0, 255);

		// 피격 right
		GetSceneResource()->CreateAnimationSequence("DamagedReaperRight",
			"DamagedReaperRight", TEXT("Texture/Monster/Reaper/DamagedReaperRight.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("DamagedReaperRight", 178.75f * i, 0.f,
				178.75f, 123.f);
		}

		GetSceneResource()->SetColorKey("DamagedReaperRight", 255, 0, 255);

		// 피격 left
		GetSceneResource()->CreateAnimationSequence("DamagedReaper",
			"DamagedReaper", TEXT("Texture/Monster/Reaper/DamagedReaper.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("DamagedReaper", 178.75f * i, 0.f,
				178.75f, 123.f);
		}

		GetSceneResource()->SetColorKey("DamagedReaper", 255, 0, 255);
	}

	// Hit Effect
	{
		GetSceneResource()->CreateAnimationSequence("Hit1",
			"Hit1", TEXT("Texture/Effect/Hit1.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 2; ++i)
		{
			GetSceneResource()->AddAnimationFrame("Hit1", 182.5f * i, 0.f,
				182.5f, 82.f);
		}

		GetSceneResource()->SetColorKey("Hit1", 255, 0, 255);
	}

	// Slash
	{
		GetSceneResource()->CreateAnimationSequence("Slash",
			"Slash", TEXT("Texture/Effect/Slash.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 2; ++i)
		{
			GetSceneResource()->AddAnimationFrame("Slash", 181.f * i, 0.f,
				181.f, 97.f);
		}

		GetSceneResource()->SetColorKey("Slash", 255, 0, 255);
	}

	// ShockWave
	{
		GetSceneResource()->CreateAnimationSequence("ShockWave",
			"ShockWave", TEXT("Texture/Effect/ShockWave.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 3; ++i)
		{
			GetSceneResource()->AddAnimationFrame("ShockWave", 182.33f * i, 0.f,
				182.33f, 80.f);
		}

		GetSceneResource()->SetColorKey("ShockWave", 255, 0, 255);
	}

	// Bible
	{
		// 기본
		GetSceneResource()->CreateAnimationSequence("Bible",
			"Bible", TEXT("Texture/Effect/Bible/Bible.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 1; ++i)
		{
			GetSceneResource()->AddAnimationFrame("Bible", 57.f * i, 0.f,
				57.f, 40.f);
		}

		GetSceneResource()->SetColorKey("Bible", 255, 0, 255);


		// 나타나기
		GetSceneResource()->CreateAnimationSequence("InitBible",
			"InitBible", TEXT("Texture/Effect/Bible/InitBible.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 8; ++i)
		{
			GetSceneResource()->AddAnimationFrame("InitBible", 71.875f * i, 0.f,
				71.875f, 44.f);
		}

		GetSceneResource()->SetColorKey("InitBible", 255, 0, 255);

		// 사라지기
		GetSceneResource()->CreateAnimationSequence("DestructBible",
			"DestructBible", TEXT("Texture/Effect/Bible/InitBible.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 8; ++i)
		{
			GetSceneResource()->AddAnimationFrame("DestructBible", 575 - 71.875f * (1 + i), 0.f,
				71.875f, 44.f);
		}

		GetSceneResource()->SetColorKey("DestructBible", 255, 0, 255);

		// 페이퍼
		GetSceneResource()->CreateAnimationSequence("BiblePaper",
			"BiblePaper", TEXT("Texture/Effect/Bible/BiblePaper.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 8; ++i)
		{
			GetSceneResource()->AddAnimationFrame("BiblePaper", 76.5f * i, 0.f,
				76.5f, 77.f);
		}

		GetSceneResource()->SetColorKey("BiblePaper", 255, 0, 255);
	}

	// EvolvedBible
	{
		// 기본
		GetSceneResource()->CreateAnimationSequence("EvolvedBible",
			"EvolvedBible", TEXT("Texture/Effect/EvolvedBible/EvolvedBible.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("EvolvedBible", 70.f * i, 0.f,
				70.f, 40.f);
		}

		GetSceneResource()->SetColorKey("EvolvedBible", 255, 0, 255);


		// 나타나기
		GetSceneResource()->CreateAnimationSequence("InitEvolvedBible",
			"InitEvolvedBible", TEXT("Texture/Effect/EvolvedBible/InitEvolvedBible.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 6; ++i)
		{
			GetSceneResource()->AddAnimationFrame("InitEvolvedBible", 72.16f * i, 0.f,
				72.16f, 38.f);
		}

		GetSceneResource()->SetColorKey("InitEvolvedBible", 255, 0, 255);

		// 사라지기
		GetSceneResource()->CreateAnimationSequence("DestructEvolvedBible",
			"DestructEvolvedBible", TEXT("Texture/Effect/EvolvedBible/InitEvolvedBible.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 6; ++i)
		{
			GetSceneResource()->AddAnimationFrame("DestructEvolvedBible", 433 - 72.16f * (1 + i), 0.f,
				72.16f, 38.f);
		}

		GetSceneResource()->SetColorKey("DestructEvolvedBible", 255, 0, 255);

		// 페이퍼
		GetSceneResource()->CreateAnimationSequence("EvolvedBiblePaper",
			"EvolvedBiblePaper", TEXT("Texture/Effect/EvolvedBible/EvolvedBiblePaper.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 8; ++i)
		{
			GetSceneResource()->AddAnimationFrame("EvolvedBiblePaper", 74.5f * i, 0.f,
				74.5f, 76.f);
		}

		GetSceneResource()->SetColorKey("EvolvedBiblePaper", 255, 0, 255);
	}

	// Lightning
	{
		GetSceneResource()->CreateAnimationSequence("Lightning",
			"Lightning", TEXT("Texture/Effect/Lightning/Lightning.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("Lightning", 42.5f * i, 0.f,
				42.5f, 2332.f);
		}

		GetSceneResource()->SetColorKey("Lightning", 255, 0, 255);
	}

	
	// Whip
	{
		// InitWhipLU
		{
			GetSceneResource()->CreateAnimationSequence("InitWhipLU",
				"InitWhipLU", TEXT("Texture/Effect/Whip/InitWhipLU.bmp"), TEXTURE_PATH);

			for (int i = 0; i < 6; ++i)
			{
				GetSceneResource()->AddAnimationFrame("InitWhipLU", 497.5f * i, 0.f,
					497.5f, 60.f);
			}

			GetSceneResource()->SetColorKey("InitWhipLU", 255, 0, 255);
		}

		// InitWhipRU
		{
			GetSceneResource()->CreateAnimationSequence("InitWhipRU",
				"InitWhipRU", TEXT("Texture/Effect/Whip/InitWhipRU.bmp"), TEXTURE_PATH);

			for (int i = 0; i < 6; ++i)
			{
				GetSceneResource()->AddAnimationFrame("InitWhipRU", 2980 - 497.5f * (1 + i), 0.f,
					497.5f, 60.f);
			}

			GetSceneResource()->SetColorKey("InitWhipRU", 255, 0, 255);
		}

		// InitWhipLD
		{
			GetSceneResource()->CreateAnimationSequence("InitWhipLD",
				"InitWhipLD", TEXT("Texture/Effect/Whip/InitWhipLD.bmp"), TEXTURE_PATH);

			for (int i = 0; i < 6; ++i)
			{
				GetSceneResource()->AddAnimationFrame("InitWhipLD", 497.5f * i, 0.f,
					497.5f, 60.f);
			}

			GetSceneResource()->SetColorKey("InitWhipLD", 255, 0, 255);
		}

		// InitWhipRD
		{
			GetSceneResource()->CreateAnimationSequence("InitWhipRD",
				"InitWhipRD", TEXT("Texture/Effect/Whip/InitWhipRD.bmp"), TEXTURE_PATH);

			for (int i = 0; i < 6; ++i)
			{
				GetSceneResource()->AddAnimationFrame("InitWhipRD", 2980 - 497.5f * (1 + i), 0.f,
					497.5f, 60.f);
			}

			GetSceneResource()->SetColorKey("InitWhipRD", 255, 0, 255);
		}
	}

	// Gem
	{
		GetSceneResource()->CreateAnimationSequence("Gem",
			"Gem", TEXT("Texture/Item/Gem.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 1; ++i)
		{
			GetSceneResource()->AddAnimationFrame("Gem", 19.f * i, 0.f,
				19.f, 25.f);
		}

		GetSceneResource()->SetColorKey("Gem", 255, 0, 255);
	}

	// FieldTreasureBox
	{
		GetSceneResource()->CreateAnimationSequence("FieldTreasureBox",
			"FieldTreasureBox", TEXT("Texture/Item/FieldTreasureBox.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 1; ++i)
		{
			GetSceneResource()->AddAnimationFrame("FieldTreasureBox", 33.f * i, 0.f,
				33.f, 29.f);
		}

		GetSceneResource()->SetColorKey("FieldTreasureBox", 255, 0, 255);
	}

	// FirePot
	{
		GetSceneResource()->CreateAnimationSequence("FirePot",
			"FirePot", TEXT("Texture/Item/FirePot.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 3; ++i)
		{
			GetSceneResource()->AddAnimationFrame("FirePot", 41.f * i, 0.f,
				41.f, 60.f);
		}

		GetSceneResource()->SetColorKey("FirePot", 255, 0, 255);
	}

	// Chicken
	{
		GetSceneResource()->CreateAnimationSequence("Chicken",
			"Chicken", TEXT("Texture/Item/Chicken.bmp"), TEXTURE_PATH);

		for (int i = 0; i < 1; ++i)
		{
			GetSceneResource()->AddAnimationFrame("Chicken", 33.f * i, 0.f,
				33.f, 35.f);
		}

		GetSceneResource()->SetColorKey("Chicken", 255, 0, 255);
	}
}


Vector2 CMainScene::SetSpawnPosition()
{
	int Num = rand() % 8;

	// 서북
	if (Num == 0)
	{
		Vector2 Pos = m_Player -> GetPos() + Vector2(-750, 0) + Vector2(0.f, -(float)(rand() % 500));
		return Pos;
	}

	// 서남
	else if (Num == 1)
	{
		Vector2 Pos = m_Player->GetPos() + Vector2(-750, 0) + Vector2(0.f, (float)(rand() % 500));
		return Pos;
	}

	// 동북
	else if (Num == 2)
	{
		Vector2 Pos = m_Player->GetPos() + Vector2(750, 0) + Vector2(0.f, -(float)(rand() % 500));
		return Pos;
	}

	// 동남
	else if (Num == 3)
	{
		Vector2 Pos = m_Player->GetPos() + Vector2(750, 0) + Vector2(0.f, (float)(rand() % 500));
		return Pos;

	}

	// 남서
	else if (Num == 4)
	{
		Vector2 Pos = m_Player->GetPos() + Vector2(0, 500) + Vector2(-(float)(rand() % 750), 0.f);
		return Pos;

	}

	// 남동
	else if (Num == 5)
	{
		Vector2 Pos = m_Player->GetPos() + Vector2(0, 500) + Vector2((float)(rand() % 750), 0.f);
		return Pos;
	}

	// 북
	else if (Num == 6)
	{
		Vector2 Pos = m_Player->GetPos() + Vector2(0, -500) + Vector2(-(float)(rand() % 750), 0.f);
		return Pos;
	}

	// 북동
	else if (Num == 7)
	{
		Vector2 Pos = m_Player->GetPos() + Vector2(0, -500) + Vector2((float)(rand() % 750), 0.f);
		return Pos;
	}
}

// 꽃 동그랗게 생성하는 함수. 내가 만듬.
void CMainScene::CircleFlowerBundle()
{
	int MonsterNumber = 40;
	Vector2 BundleSize (1200.f, 675.f);

	for (int i = 0; i < MonsterNumber; ++i)
	{
		Vector2	Target;
		Target.x = m_Player->GetPos().x + cosf(DegreeToRadian((float)(360 / MonsterNumber) * i)) * BundleSize.x;
		Target.y = m_Player->GetPos().y + sinf(DegreeToRadian((float)(360 / MonsterNumber) * i)) * BundleSize.y;

		if (i % 2)
		{
			CFlower1* Flower1 = CreateObject<CFlower1>("Flower1", Target);
			AddMonster(Flower1);
			AddMonsterBundle(Flower1);
		}

		else
		{
			CFlower2* Flower2 = CreateObject<CFlower2>("Flower2", Target);
			AddMonster(Flower2);
			AddMonsterBundle(Flower2);
		}
	}
}

// 스켈레톤을 네모나게 생성하는 함수.
// 스켈레톤 무리는 한번에 삭제할 일이 없기 때문에 MosterBundle에 추가하지는 않는다.
void CMainScene::SquareSkeletonBundle()
{
	int MonsterNumber = 70;

	for (int i = 0; i < MonsterNumber; ++i)
	{
		int Num = i % 8;

		if (Num % 2) 
		{

			if (Num == 0)
			{
				Vector2 Pos = m_Player->GetPos() + Vector2(-750, 0) + Vector2(0, -(float)(rand() % 500));
				CSkeleton1* Skeleton1 = CreateObject<CSkeleton1>("Skeleton1", Pos);
				AddMonster(Skeleton1);
			}

			else if (Num == 1)
			{
				Vector2 Pos = m_Player->GetPos() + Vector2(-750, 0) + Vector2(0, (float)(rand() % 500));
				CSkeleton1* Skeleton1 = CreateObject<CSkeleton1>("Skeleton1", Pos);
				AddMonster(Skeleton1);
			}

			else if (Num == 2)
			{
				Vector2 Pos = m_Player->GetPos() + Vector2(750, 0) + Vector2(0, -(float)(rand() % 500));
				CSkeleton1* Skeleton1 = CreateObject<CSkeleton1>("Skeleton1", Pos);
				AddMonster(Skeleton1);
			}

			else if (Num == 3)
			{
				Vector2 Pos = m_Player->GetPos() + Vector2(750, 0) + Vector2(0, (float)(rand() % 500));
				CSkeleton1* Skeleton1 = CreateObject<CSkeleton1>("Skeleton1", Pos);
				AddMonster(Skeleton1);
			}

			else if (Num == 4)
			{
				Vector2 Pos = m_Player->GetPos() + Vector2(0, 500) + Vector2(-(float)(rand() % 750), 0);
				CSkeleton1* Skeleton1 = CreateObject<CSkeleton1>("Skeleton1", Pos);
				AddMonster(Skeleton1);
			}

			else if (Num == 5)
			{
				Vector2 Pos = m_Player->GetPos() + Vector2(0, 500) + Vector2((float)(rand() % 750), 0);
				CSkeleton1* Skeleton1 = CreateObject<CSkeleton1>("Skeleton1", Pos);
				AddMonster(Skeleton1);
			}

			else if (Num == 6)
			{
				Vector2 Pos = m_Player->GetPos() + Vector2(0, -500) + Vector2(-(float)(rand() % 750), 0);
				CSkeleton1* Skeleton1 = CreateObject<CSkeleton1>("Skeleton1", Pos);
				AddMonster(Skeleton1);
			}

			else if (Num == 7)
			{
				Vector2 Pos = m_Player->GetPos() + Vector2(0, -500) + Vector2((float)(rand() % 750), 0);
				CSkeleton1* Skeleton1 = CreateObject<CSkeleton1>("Skeleton1", Pos);
				AddMonster(Skeleton1);
			}
		}

		else 
		{

			if (Num == 0)
			{
				Vector2 Pos = m_Player->GetPos() + Vector2(-750, 0) + Vector2(0, -(float)(rand() % 500));
				CSkeleton2* Skeleton2 = CreateObject<CSkeleton2>("Skeleton2", Pos);
				AddMonster(Skeleton2);
			}

			else if (Num == 1)
			{
				Vector2 Pos = m_Player->GetPos() + Vector2(-750, 0) + Vector2(0, (float)(rand() % 500));
				CSkeleton2* Skeleton2 = CreateObject<CSkeleton2>("Skeleton2", Pos);
				AddMonster(Skeleton2);
			}

			else if (Num == 2)
			{
				Vector2 Pos = m_Player->GetPos() + Vector2(750, 0) + Vector2(0, -(float)(rand() % 500));
				CSkeleton2* Skeleton2 = CreateObject<CSkeleton2>("Skeleton2", Pos);
				AddMonster(Skeleton2);
			}

			else if (Num == 3)
			{
				Vector2 Pos = m_Player->GetPos() + Vector2(750, 0) + Vector2(0, (float)(rand() % 500));
				CSkeleton2* Skeleton2 = CreateObject<CSkeleton2>("Skeleton2", Pos);
				AddMonster(Skeleton2);
			}

			else if (Num == 4)
			{
				Vector2 Pos = m_Player->GetPos() + Vector2(0, 500) + Vector2(-(float)(rand() % 750), 0);
				CSkeleton2* Skeleton2 = CreateObject<CSkeleton2>("Skeleton2", Pos);
				AddMonster(Skeleton2);
			}

			else if (Num == 5)
			{
				Vector2 Pos = m_Player->GetPos() + Vector2(0, 500) + Vector2((float)(rand() % 750), 0);
				CSkeleton2* Skeleton2 = CreateObject<CSkeleton2>("Skeleton2", Pos);
				AddMonster(Skeleton2);
			}

			else if (Num == 6)
			{
				Vector2 Pos = m_Player->GetPos() + Vector2(0, -500) + Vector2(-(float)(rand() % 750), 0);
				CSkeleton2* Skeleton2 = CreateObject<CSkeleton2>("Skeleton2", Pos);
				AddMonster(Skeleton2);
			}

			else if (Num == 7)
			{
				Vector2 Pos = m_Player->GetPos() + Vector2(0, -500) + Vector2((float)(rand() % 750), 0);
				CSkeleton2* Skeleton2 = CreateObject<CSkeleton2>("Skeleton2", Pos);
				AddMonster(Skeleton2);
			}
		}
	}
}


void CMainScene::SquareGhostBundle()
{
	int MonsterNumber = 50;

	for (int i = 0; i < MonsterNumber; ++i)
	{
		int Num = i % 8;

		if (Num % 2)
		{

			if (Num == 0)
			{
				Vector2 Pos = m_Player->GetPos() + Vector2(-750, 0) + Vector2(0, -(float)(rand() % 500));
				CGhost* Ghost = CreateObject<CGhost>("Ghost", Pos);
				AddMonster(Ghost);
			}

			else if (Num == 1)
			{
				Vector2 Pos = m_Player->GetPos() + Vector2(-750, 0) + Vector2(0, (float)(rand() % 500));
				CGhost* Ghost = CreateObject<CGhost>("Ghost", Pos);
				AddMonster(Ghost);
			}

			else if (Num == 2)
			{
				Vector2 Pos = m_Player->GetPos() + Vector2(750, 0) + Vector2(0, -(float)(rand() % 500));
				CGhost* Ghost = CreateObject<CGhost>("Ghost", Pos);
				AddMonster(Ghost);
			}

			else if (Num == 3)
			{
				Vector2 Pos = m_Player->GetPos() + Vector2(750, 0) + Vector2(0, (float)(rand() % 500));
				CGhost* Ghost = CreateObject<CGhost>("Ghost", Pos);
				AddMonster(Ghost);
			}

			else if (Num == 4)
			{
				Vector2 Pos = m_Player->GetPos() + Vector2(0, 500) + Vector2(-(float)(rand() % 750), 0);
				CGhost* Ghost = CreateObject<CGhost>("Ghost", Pos);
				AddMonster(Ghost);
			}

			else if (Num == 5)
			{
				Vector2 Pos = m_Player->GetPos() + Vector2(0, 500) + Vector2((float)(rand() % 750), 0);
				CGhost* Ghost = CreateObject<CGhost>("Ghost", Pos);
				AddMonster(Ghost);
			}

			else if (Num == 6)
			{
				Vector2 Pos = m_Player->GetPos() + Vector2(0, -500) + Vector2(-(float)(rand() % 750), 0);
				CGhost* Ghost = CreateObject<CGhost>("Ghost", Pos);
				AddMonster(Ghost);
			}

			else if (Num == 7)
			{
				Vector2 Pos = m_Player->GetPos() + Vector2(0, -500) + Vector2((float)(rand() % 750), 0);
				CGhost* Ghost = CreateObject<CGhost>("Ghost", Pos);
				AddMonster(Ghost);
			}
		}

		else
		{

			if (Num == 0)
			{
				Vector2 Pos = m_Player->GetPos() + Vector2(-750, 0) + Vector2(0, -(float)(rand() % 500));
				CGhost* Ghost = CreateObject<CGhost>("Ghost", Pos);
				AddMonster(Ghost);
			}

			else if (Num == 1)
			{
				Vector2 Pos = m_Player->GetPos() + Vector2(-750, 0) + Vector2(0, (float)(rand() % 500));
				CGhost* Ghost = CreateObject<CGhost>("Ghost", Pos);
				AddMonster(Ghost);
			}

			else if (Num == 2)
			{
				Vector2 Pos = m_Player->GetPos() + Vector2(750, 0) + Vector2(0, -(float)(rand() % 500));
				CGhost* Ghost = CreateObject<CGhost>("Ghost", Pos);
				AddMonster(Ghost);
			}

			else if (Num == 3)
			{
				Vector2 Pos = m_Player->GetPos() + Vector2(750, 0) + Vector2(0, (float)(rand() % 500));
				CGhost* Ghost = CreateObject<CGhost>("Ghost", Pos);
				AddMonster(Ghost);
			}

			else if (Num == 4)
			{
				Vector2 Pos = m_Player->GetPos() + Vector2(0, 500) + Vector2(-(float)(rand() % 750), 0);
				CGhost* Ghost = CreateObject<CGhost>("Ghost", Pos);
				AddMonster(Ghost);
			}

			else if (Num == 5)
			{
				Vector2 Pos = m_Player->GetPos() + Vector2(0, 500) + Vector2((float)(rand() % 750), 0);
				CGhost* Ghost = CreateObject<CGhost>("Ghost", Pos);
				AddMonster(Ghost);
			}

			else if (Num == 6)
			{
				Vector2 Pos = m_Player->GetPos() + Vector2(0, -500) + Vector2(-(float)(rand() % 750), 0);
				CGhost* Ghost = CreateObject<CGhost>("Ghost", Pos);
				AddMonster(Ghost);
			}

			else if (Num == 7)
			{
				Vector2 Pos = m_Player->GetPos() + Vector2(0, -500) + Vector2((float)(rand() % 750), 0);
				CGhost* Ghost = CreateObject<CGhost>("Ghost", Pos);
				AddMonster(Ghost);
			}
		}
	}
}


void CMainScene::GamePause()
{
	if (m_GamePauseWindow && m_GamePauseWindow->GetActive())
	{
		m_GamePauseWindow->SetActive(false);
		CGameManager::GetInst()->SetTimeScale(1.f);
	}

	else if (CGameManager::GetInst()->GetTimeScale() == 1.f)
	{
		if (!m_GamePauseWindow || !m_GamePauseWindow->GetActive())
		{
			m_GamePauseWindow = CreateWidgetWindow<CGamePauseWindow>("GamePauseWindow");
			CGameManager::GetInst()->SetTimeScale(0.f);
		}
	}
}
