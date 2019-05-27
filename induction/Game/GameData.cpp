#include "stdafx.h"
#include "GameData.h"


GameData::GameData()
{
	//ここに各チェックポイントの角度を入れていくぅ
	m_cameradegreelist.push_back({ 100.0f,100.0f });			//←これステージ1ね
	m_cameradegreelist.push_back({ 0.0f,0.0f });
}


GameData::~GameData()
{
}
