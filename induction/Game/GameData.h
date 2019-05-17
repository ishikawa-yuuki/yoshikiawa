#pragma once
class GameData
{
private:
	GameData();
	~GameData();
public:
	static GameData& GetInstance()
	{
		static GameData gamedata;
		return gamedata;
	}
	enum StageNumber {
		enState_Stage1 = 1,
		enState_Stage2,
		enState_Stage3,
		enState_StageFirst = enState_Stage1,
		enState_StageLast = enState_Stage2
	};
	//ステージをクリアした！
	void SetStageClear() 
	{
		m_stageclear[m_stagenumber - 1] = true;
	}
	//ステージをクリアしているかどうかを取得
	bool GetisStageClear(const StageNumber& number)
	{
		return m_stageclear[number - 1];
	}
	//選択したステージの番号を設定
	void SetStageNumber(const StageNumber& number)
	{
		m_stagenumber = number;
	}
	//選択したステージを取得
	StageNumber GetStageNumber() const
	{
		return m_stagenumber;
	}
	//エフェクトの名前を取得
	const char* GetEffectName()
	{
		return m_effectname;
	}
	static const int m_stagelimit = 3;								//ステージの数
public:
	bool m_stageclear[m_stagelimit] = { false,false,false };		//各ステージのクリア状況
	StageNumber m_stagenumber = enState_Stage1;						//プレイヤーが選択したステージの番号
	const char* m_effectname = "Effect";							//ステージ終了時に強制的に消去したいエフェクトに名前を付けるときに使う
};

