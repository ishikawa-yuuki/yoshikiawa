#pragma once
class SSPlayer;
class Stage_Number : public IGameObject
{
public:
	Stage_Number();
	~Stage_Number();
	bool Start();
	void Update();
	//選択したステージの番号を返す
	//backGroundクラスに届ける用
	int GetStageNumber()
	{
		return m_stage;
	}
	//タイトルに戻るときに呼ばれます
	//タイトルに戻った時にこのクラスを処理します。
	bool IsTitle()
	{
		isTitle = true;
		return isTitle;
	}
	enum StageNum {
		stage1 = 1,
		stage2,
		stage3,
		stagenum
	};
	StageNum m_stage = stagenum;
private:
	SSPlayer* ssplayer;
	bool isTitle = false;
};

