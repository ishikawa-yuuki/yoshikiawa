#include "stdafx.h"
#include "Stage_Number.h"
#include "SSPlayer.h"

Stage_Number::Stage_Number()
{
}


Stage_Number::~Stage_Number()
{
}

bool Stage_Number::Start()
{
	ssplayer = FindGO<SSPlayer>("SSPlayer");
	return true;
}

void Stage_Number::Update()
{
	if (ssplayer != nullptr) {
		switch (ssplayer->GetStagenum())
		{
		case 1:
			m_stage = stage1;
			break;
		case 2:
			m_stage = stage2;
			break;
		case 3:
			m_stage = stage3;
			break;
		}
	}
	else {
			m_stage = m_stage;
		}
	if (isTitle == true) {
		DeleteGO(this);
	}
}