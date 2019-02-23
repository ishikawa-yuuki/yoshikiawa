#pragma once
//ステージのposition
class SSPoint : public IGameObject
{
public:
	SSPoint();
	~SSPoint();
	bool Start();
	void Update();
	CVector3 m_position = CVector3::Zero;
private:
	prefab::CSkinModelRender* m_skin = nullptr;
	
};

