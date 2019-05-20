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
		enState_StageLast = enState_Stage3
	};
	//ステージをクリアした！
	void SetStageClear() 
	{
		m_stageclear[m_stagenumber - 1] = true;
	}
	//チェックポイント通過した！
	void SetStageCheck()
	{
		m_stagecheck[m_stagenumber - 1] = true;
	}
	//ステージをクリアしているかどうかを取得
	bool GetisStageClear(const StageNumber& number)
	{
		return m_stageclear[number - 1];
	}
	//チェックポイントを通過しているかどうかを取得
	bool GetisStageCheck(const StageNumber& number)
	{
		return m_stagecheck[number - 1];
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
	//チェックポイントから始めるかどうかを設定
	void SetCheckPoint(bool start) 
	{
		m_startcheckpoint = start;
	}
	//チェックポイントから始めるかどうかを取得
	bool GetisStartCheckPoint()
	{
		return m_startcheckpoint;
	}
	//始めてステージに入ったかどうかを取得
	bool GetisFirstEnterStage()
	{
		return m_isfirstenterstage;
	}
	//ステージに入った！
	void SetisEnterStage()
	{
		m_isfirstenterstage = true;
	}
	static const int m_stagelimit = 3;								//ステージの数
public:
	bool m_stageclear[m_stagelimit] = { true,true,false };			//各ステージのクリア状況
	bool m_stagecheck[m_stagelimit] = { false,false,false };		//チェックポイントの通過状況
	StageNumber m_stagenumber = enState_Stage1;						//プレイヤーが選択したステージの番号
	const char* m_effectname = "Effect";							//ステージ終了時に強制的に消去したいエフェクトに名前を付けるときに使う
	bool m_startcheckpoint = false;									//チェックポイントから始めるかどうか
	bool m_isfirstenterstage = false;
};

