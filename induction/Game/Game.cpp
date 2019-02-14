#include "stdafx.h"
#include "Game.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "Human.h"
#include "Player.h"
#include "GameCamera.h"
Game::Game()
{
}


Game::~Game()
{
	DeleteGO(m_human);
}
bool Game::Start()
{
	m_player = NewGO<Player>(0, "Player");
	m_human = NewGO<Human>(0, "Human");
	m_gamecamera = NewGO<GameCamera>(0, "GameCamera");

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/stage_test.cmo");//���X�e�[�W
	m_skinModelRender->SetScale({ 20.0f,20.0f,20.0f });//�v������菬���������̂�20�{
	return true;
}

void Game::Update()
{
}