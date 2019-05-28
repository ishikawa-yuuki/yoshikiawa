#include "stdafx.h"
#include "GameData.h"
#include "GameCamera.h"

GameData::GameData()
{
	//ここに各チェックポイントの角度を入れていくぅ
	m_cameradegreelist.push_back({ 0.0f,degleeY });			//←これステージ1ね
	m_cameradegreelist.push_back({ 0.0f,degleeY });         //←ステージ2
	m_cameradegreelist.push_back({ 0.0f,degleeY });         //←ステージ3
	m_cameradegreelist.push_back({ -90.0f,degleeY });       //←ステージ4
	m_cameradegreelist.push_back({ -30.0f,degleeY });       //←ステージ5
}


GameData::~GameData()
{
}