#include "stdafx.h"
#include "Human.h"
#include "Player.h"
#include "MistEnemy.h"
#include "Game.h"
#include "GameOver.h"
#include "MoveBed.h"
#include "MoveBed_zengo.h"
#include "Poison.h"
#include "Stone.h"
#include "Fade.h"
#include "Exit.h"
#include "Light_Object.h"
#include "Stage_Select.h"
#include "Title.h"
#include "TitleGround.h"
#include  "GameData.h"
//���C�g�̋������v�Z����B
float CalcLightPower(CVector3 charaPos, CVector3 lightPos, CVector4 attn)
{
	float len = (charaPos - lightPos).Length();
	float lightRate = len / attn.x;
	float lightPower = std::max<float>(1.0 - lightRate * lightRate, 0.0f);
	return pow(lightPower, attn.y);
}
Human::Human()
{
}


Human::~Human()
{
	DeleteGO(m_skinModelRender);
	if (m_title == nullptr) {
		DeleteGO(m_nearPointLight);
	}
}

bool Human::Start()
{

	m_player = FindGO<Player>("Player");
	m_game = FindGO<Game>("Game");
	m_fade = FindGO<Fade>("Fade");
	
	m_mistenemy = FindGO<MistEnemy>("mist");
	m_exit = FindGO<Exit>("Exit");
	m_title = FindGO<Title>("Title");
	if (m_title == nullptr) {
		m_animClip[enAnimationClip_idle].Load(L"animData/Human/idle.tka");
		//m_animClip[enAnimationClip_walk].Load(L"animData/unityChan/walk.tka");
		m_animClip[enAnimationClip_run].Load(L"animData/Human/run.tka");
		//m_animClip[enAnimationClip_jump].Load(L"animData/unityChan/jump.tka");
		//m_animClip[enAnimationClip_damage].Load(L"animData/unityChan/damage.tka");
		m_animClip[enAnimationClip_KneelDown].Load(L"animData/Human/KneelDown.tka");
		m_animClip[enAnimationClip_clear].Load(L"animData/Human/clear.tka");
		//�A�j���N���b�v�����ׂă��[�h�A�S���g���K�v�͓��ɂȂ��ł��B


		for (int i = 0; i < enAnimationClip_num; i++) {
			m_animClip[i].SetLoopFlag(true);
		}
		//for���łƂ肠�������[�h�����z�炷�ׂ�LoopFlag��true�ɂ����B

		//m_animClip[enAnimationClip_jump].SetLoopFlag(false);
		m_animClip[enAnimationClip_KneelDown].SetLoopFlag(false);
		//m_animClip[enAnimationClip_damage].SetLoopFlag(false);
		m_animClip[enAnimationClip_clear].SetLoopFlag(false);
		//true�ɂ������肪����z����false�ɒ������B

		m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
		m_skinModelRender->Init(L"modelData/Human/Human.cmo", m_animClip, enAnimationClip_num, enFbxUpAxisZ);
		m_charaCon.Init(
			20.0f,
			30.0f,
			m_position
		);
	}
	else {
		m_animClip[enAnimationClip_idle].Load(L"animData/Human/idle.tka");
		//m_animClip[enAnimationClip_walk].Load(L"animData/unityChan/walk.tka");
		m_animClip[enAnimationClip_run].Load(L"animData/Human/run.tka");
		//m_animClip[enAnimationClip_jump].Load(L"animData/unityChan/jump.tka");
		//m_animClip[enAnimationClip_damage].Load(L"animData/unityChan/damage.tka");
		m_animClip[enAnimationClip_KneelDown].Load(L"animData/Human/KneelDown.tka");
		m_animClip[enAnimationClip_clear].Load(L"animData/Human/clear.tka");
		//�A�j���N���b�v�����ׂă��[�h�A�S���g���K�v�͓��ɂȂ��ł��B


		for (int i = 0; i < enAnimationClip_num; i++) {
			m_animClip[i].SetLoopFlag(true);
		}
		//for���łƂ肠�������[�h�����z�炷�ׂ�LoopFlag��true�ɂ����B

		//m_animClip[enAnimationClip_jump].SetLoopFlag(false);
		m_animClip[enAnimationClip_KneelDown].SetLoopFlag(false);
		//m_animClip[enAnimationClip_damage].SetLoopFlag(false);
		m_animClip[enAnimationClip_clear].SetLoopFlag(false);
		//true�ɂ������肪����z����false�ɒ������B

		m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
		m_skinModelRender->Init(L"modelData/TitleGround/humant.cmo", m_animClip, enAnimationClip_num, enFbxUpAxisZ);
		//m_skinModelRender->Init(L"modelData/TitleGround/human_title.cmo");
		m_charaCon.Init(
			20.0f,
			30.0f,
			m_position
		);
		m_titleground = FindGO<TitleGround>("TitleGround");
	}
	m_skinModelRender->SetShadowCasterFlag(true);
	m_skinModelRender->SetEmissionColor({3.3f, 3.3f, 3.3f});
	m_skinModelRender->SetPosition(m_position);
	
	return true;
}

void Human::Update()
{
	if (m_title != nullptr) {
		if (m_title->isStop()) {
			m_degree -= m_titleground->GetCutSpeed() * m_speed * GameTime().GetFrameDeltaTime();
			CQuaternion rot;
			rot.SetRotationDeg(CVector3::AxisX, m_degree);
			m_skinModelRender->SetRotation(rot);
		}
		//m_skinModelRender->PlayAnimation(enAnimationClip_run, 0.2);
		return;
	}
	AnimeControll();
	//if (m_player->GetStartMove() == true) {
		if (!m_StartMoveFin) {
			GameStartMove();
		}
		else if (m_mistenemy->Getstate() == 2)
		{
			TakingMove();
		}
		else
		{
				/*QueryGOs<Light_Object>("LightObject", [&](Light_Object* light) {*/
					//light->GetlightOn() == true;
				//�����^���̐����AGetLightOn()�֐��𒲂ׂāA
				//���̒���GetLightOn��true�ɂȂ��Ă��郉���^���������m_nearlight�ɑ���B
				Light_Move();
		}
		Turn();
		Hanntei();
		CVector3 Pos = m_position + m_Bedspeed;
		isDead();
		isClear();
		m_charaCon.SetPosition(Pos);
		m_skinModelRender->SetPosition(Pos);
	//}
}

void Human::GameStartMove()
{
	CVector3 diff;
	diff = m_player->GetPosition() - m_position;
	diff.y = 0.0f;
	if (diff.LengthSq() <105.0f * 105.0f) {
		m_movespeed = CVector3::Zero;
		m_StartMoveFin = true;
	}
	else {
		m_movespeed.z = -400.0f;
		//m_position += m_movespeed;
	}

	if (m_charaCon.IsOnGround()) {
		m_movespeed.y = 0.0f;
	}
	else {
		m_movespeed.y -= 10000.0f*GameTime().GetFrameDeltaTime();
	}

	m_position = m_charaCon.Execute(m_movespeed, GameTime().GetFrameDeltaTime());
}

void Human::Move()
{
	/*const int light_Yellow = 0;
	const int light_Red = 1;
	if (!m_Clear_one) {
		if (m_player->GetColor() == light_Yellow) {
			//���ȂȂ����̕��ʂ̏���
			if (!m_isDead) {
				CVector3 diff = m_position - m_player->GetPosition();
				//Y�̐��l�͏��O
				diff.y = 0.0f;
				if (diff.LengthSq() <= 105.0f * 105.0f) {//�v���C���[�Ƌ߂����human�͎~�܂�
					m_movespeed = CVector3::Zero;
				}
				else {
					auto humanspeed = 30.0f;
					m_movespeed = m_player->GetPosition() - m_position;
					m_movespeed.y = 0.0f;
					m_movespeed.Normalize();

					m_movespeed *= diff.LengthSq() / (400.0f * 400.0f) * 12.0f;
					if (diff.LengthSq() >= 800.0f*800.0f) {//�v���C���[�Ɨ��ꂷ�����Ƃ��ɂ�����movespeed�̍ō���
						diff.y = 0.0f;
						diff.Normalize();
						diff *= -30.0f;//-���Ƌ߂Â�+�Ȃ牓�̂�
						m_movespeed = diff;
						m_movespeed = m_movespeed * humanspeed;// *GameTime().GetFrameDeltaTime();
					}
					else {//player�Ɨ��ꂷ�����߂����Ȃ��Ƃ��̏���
						m_movespeed = m_movespeed * humanspeed;// *GameTime().GetFrameDeltaTime();
					}
				}
			}
			else
			{
				//���񂾂Ƃ��̏���
				m_movespeed = CVector3::Zero;
			}
		}
		else if (m_player->GetColor() == light_Red) {//�ԐF�ɂȂ������̏����A�Ƃ肠�����~�܂��Ă�
			m_movespeed = CVector3::Zero;
			m_movespeed.y -= 10000.0f*GameTime().GetFrameDeltaTime();
		}

		if (m_charaCon.IsOnGround()) {
			m_movespeed.y = 0.0f;
		}
		else {
			m_movespeed.y -= 10000.0f*GameTime().GetFrameDeltaTime();
		}
	}
	//�������Ǝ����̃X�s�[�h�𑫂��B
	CVector3 pos = m_movespeed + m_Bedspeed;
	m_position = m_charaCon.Execute(pos, GameTime().GetFrameDeltaTime());*/
}

void Human::TakingMove()
{
	if (!m_Clear_one) {
			//���ȂȂ����̕��ʂ̏���
			if (!m_isDead) {
				CVector3 diff = m_position - m_mistenemy->GetPosition();
				CVector3 diff_p = m_position - m_player->GetPosition();
				//Y�̐��l�͏��O
				diff.y = 0.0f;
				diff_p.y = 0.0f;
				if (diff.LengthSq() <= 105.0f * 105.0f) {//�v���C���[�Ƌ߂����human�͎~�܂�
					m_movespeed = CVector3::Zero;
				}
				else {
					auto humanspeed = 30.0f;
					m_movespeed = m_mistenemy->GetPosition() - m_position;
					m_movespeed.y = 0.0f;
					m_movespeed.Normalize();

					m_movespeed *= diff.LengthSq() / (400.0f * 400.0f) * 12.0f;
					if (diff.LengthSq() >= 800.0f*800.0f) {//�v���C���[�Ɨ��ꂷ�����Ƃ��ɂ�����movespeed�̍ō���
						diff.y = 0.0f;
						diff.Normalize();
						diff *= -10.0f;//-���Ƌ߂Â�+�Ȃ牓�̂�
						m_movespeed = diff;
						m_movespeed = m_movespeed * humanspeed;// *GameTime().GetFrameDeltaTime();
					}
					else {//player�Ɨ��ꂷ�����߂����Ȃ��Ƃ��̏���
						m_movespeed = m_movespeed * humanspeed;// *GameTime().GetFrameDeltaTime();
					}
				}
			}
			else
			{
				//���񂾂Ƃ��̏���
				m_movespeed = CVector3::Zero;
			}
		}
		if (m_charaCon.IsOnGround()) {
			m_movespeed.y = 0.0f;
		}
		else {
			m_movespeed.y -= 10000.0f*GameTime().GetFrameDeltaTime();
		}
	//�������Ǝ����̃X�s�[�h�𑫂��B
	CVector3 pos = m_movespeed + m_Bedspeed;
	m_position = m_charaCon.Execute(pos, GameTime().GetFrameDeltaTime());
}

void Human::Light_Move()
{
	if (!m_Clear_one) {
		//���ȂȂ����̕��ʂ̏���
		if (!m_isDead) {
			
			m_nearLen = 100000.0f;
			//int nearLightNo = -1;
			m_nearPointLight = nullptr;
			/*Game* game = FindGO<Game>("Game");*/
			const auto& lightList = m_game->GetLightObjectList();
			float ligPowerMax = 0.0f;
			//��Ԍ��̋������������C�g�������^�����璲�ׂ�B
			for (int i = 0; i < lightList.size(); i++) {
				if (lightList[i]->GetLightOn()) {
					float ligPower = CalcLightPower(
						m_position, 
						lightList[i]->GetPosition(), 
						lightList[i]->GetPointLightAttn()
					);

					//�ǂ̃����^���̌�����ԉe����^���Ă��邩���ׂ�B
					if (ligPowerMax < ligPower) {
						ligPowerMax = ligPower;	
						m_nearPointLight = lightList[i]->GetPointLight();
					}
				}
			}
			//���͐�
			float ligPower = CalcLightPower(m_position, m_player->GetPosition(), m_player->GetPointLightAttn());
			if (ligPower > ligPowerMax) {
				m_nearPointLight = m_player->GetPointLight();
			}
			//�����͂��Ă��郉�C�g����������A�����ɂ��Ă����B
			if (m_nearPointLight != nullptr) {
				if (mistflag) {
					mistflag = false;
				}
				auto humanspeed = 300.0f;
				m_movespeed = m_nearPointLight->GetPosition() - m_position;
				auto len = m_movespeed.Length();
				if (len > 200.0f) {
					m_movespeed.y = 0.0f;
					m_movespeed.Normalize();
					m_movespeed = m_movespeed * humanspeed;
				}
				else {
					m_movespeed = CVector3::Zero;
				}
			}
			else {
				m_movespeed = CVector3::Zero;
				//�~�X�g�G�l�~�[���ĂԂ���
				if (!mistflag) {
					m_enemytimer--;
				}
				if (m_enemytimer < 0) {
					mistflag = true;
					m_enemytimer = Random().GetRandInt() % 500 + 200;
				}
			}
		}
		else
		{
			//���񂾂Ƃ��̏���
			m_movespeed = CVector3::Zero;
		}
	}
	if (m_charaCon.IsOnGround()) {
		m_movespeed.y = 0.0f;
	}
	else {
		m_movespeed.y -= 10000.0f*GameTime().GetFrameDeltaTime();
	}
	//�������Ǝ����̃X�s�[�h�𑫂��B
	CVector3 pos = m_movespeed + m_Bedspeed;
	m_position = m_charaCon.Execute(pos, GameTime().GetFrameDeltaTime());
}

void Human::Turn()
{
	if (!m_isDead) {
		if (fabsf(m_movespeed.x) <= 0.001f    //fabsf�͐�Βl�Bm_movespeed.x&m_movespeedz��
			&&fabsf(m_movespeed.z)<= 0.001f) {//0.001�ȉ��̎��ɂ͉������Ȃ��B
			return;
		}
		else {
			float angle = atan2(m_movespeed.x, m_movespeed.z);
			m_qrot.SetRotation(CVector3::AxisY, angle);
		}
		m_skinModelRender->SetRotation(m_qrot);
	}
}
void Human::Range()
{
	const float range = 800.0f * 800.0f;
	CVector3 diff = m_position - m_player->GetPosition();
	if (diff.LengthSq() < range) {
		m_volume = 0.5f;
	}
	else if (diff.LengthSq() < range * 1.5) {
		m_volume = 0.3f;
	}
	else if (diff.LengthSq() < range * 3) {
		m_volume = 0.15f;
	}
}
//�A�j���[�V�������Ǘ�����֐��A�v���C���[�̃X�s�[�h�ŕς��B
//�N���A�ƃQ�[���I�[�o�[�̎��͋@�\���Ȃ��B
void Human::AnimeControll()
{
	m_kari += GameTime().GetFrameDeltaTime();
	//prefab::CSoundSource* ss;
	if (!m_isDead) {
		if (!m_Clear_one) {
			const float run_true = 100.0f*100.0f;
			const float walk_true = 10.0f*10.0f;
			//	m_movespeed.y = 0.0f;
			if (m_position.y <= -200.0f) {
				m_isDead = true;
			}
			else if (m_movespeed.LengthSq() > run_true) {
				m_skinModelRender->PlayAnimation(enAnimationClip_run, 0.2);
				if (m_kari >= 0.4) {
					prefab::CSoundSource*ss = NewGO<prefab::CSoundSource>(0);
					ss->Init(L"sound/run.wav");
					Range();
					ss->SetVolume(m_volume);
					ss->Play(false);
					m_kari = 0;
				}
				
			}
		/*	else if (m_movespeed.LengthSq() > walk_true) {
				m_skinModelRender->PlayAnimation(enAnimationClip_walk, 0.2);
				if (m_kari >= 0.5) {
					prefab::CSoundSource*ss = NewGO<prefab::CSoundSource>(0);
					ss->Init(L"sound/walk.wav");
					ss->SetVolume(0.5f);
					ss->Play(false);
					m_kari = 0.0f;
				}*/
			//}
			else {
				m_skinModelRender->PlayAnimation(enAnimationClip_idle, 0.2);
			}
		}
	}
}

//void Human::PostRender(CRenderContext& renderContext) //�����𒲂ׂ邽�߂̃|�X�g�����_���A���͈ړ��X�s�[�h�B
//{
//	m_font.Begin(renderContext);
//	wchar_t MoveSPeeed[100];
//	swprintf(MoveSPeeed, L"x%f,y%f,z%f", m_movespeed.x, m_movespeed.y, m_movespeed.z);
//	m_font.Draw(MoveSPeeed, { 0,0 });
//	m_font.End(renderContext);
//}

void Human::isDead()
{
	if (!m_game->GetifPose()) {//!= true�C��
		//�G���M�~�b�N���Ȃ��̂ō��̂Ƃ���̓{�^�����������Ŏ��ʃX�y�����J�[�ł��B
		if (!m_Clear_one) {//�N���A��ԂłȂ��Ȃ牺��
			if (!m_siboustop) {
				if (Pad(0).IsTrigger(enButtonB)
					|| m_isDead) {
					//���ѐ�
					prefab::CSoundSource* sound = nullptr;
					sound = NewGO<prefab::CSoundSource>(0);
					sound->Init(L"sound/woman.wav");
					sound->SetVolume(0.05f);
					sound->Play(false);
					m_siboustop = true;
					m_isDead = true; //���ꂪtrue�ɂȂ�Ύ�
					m_game->GetDamage();//game�N���X�Ƀ_���[�W���ł��邱�Ƃ�m�点�Ă���B����ł邯�ǁE�E�E
					m_skinModelRender->PlayAnimation(enAnimationClip_KneelDown, 0.2f);
				}
			}
			else {
				//���S���̃A�j���[�V�������I�������GameOver�N���X��
				if (!m_skinModelRender->IsPlayingAnimation() //== false
					&& !m_isGameOver //!= true
					) {
					//�����ňÓ]
					m_isGameOver = true;
				}
			}
		}
	}
}
//�����I�u�W�F�N�g�̔���
void Human::Hanntei()
{
	 m_Bedspeed = CVector3::Zero;
		QueryGOs<MoveBed>("MoveBed1", [&](MoveBed* move) {
			CPhysicsGhostObject* ghostObj = move->GetGhost();
			PhysicsWorld().ContactTest(m_charaCon, [&](const btCollisionObject& contactObject) {
				if (ghostObj->IsSelf(contactObject) ) {//== true
					//���̃t���[���̃{�b�N�X�̈ړ��ʂ��v�Z
					CVector3 boxMoveValue;
					boxMoveValue = move->GetPosition() - move->GetLastPos();
					//�{�b�N�X�̈ړ����x�����߂�
					//CVector3 boxMoveSpeed;
					//boxMoveSpeed = boxMoveValue;
						// GameTime().GetFrameDeltaTime();
					m_Bedspeed += boxMoveValue; //boxMoveSpeed;
				}
			});
			return true;
		});

		QueryGOs<MoveBed_zengo>("MoveBed2", [&](MoveBed_zengo* move) {
			CPhysicsGhostObject* ghostObj = move->GetGhost();
			PhysicsWorld().ContactTest(m_charaCon, [&](const btCollisionObject& contactObject) {
				if (ghostObj->IsSelf(contactObject) ) {//== true
					//���̃t���[���̃{�b�N�X�̈ړ��ʂ��v�Z
					CVector3 boxMoveValue;
					boxMoveValue = move->GetPosition() - move->GetLastPos();
					//�{�b�N�X�̈ړ����x�����߂�
					//CVector3 boxMoveSpeed;
					//boxMoveSpeed = boxMoveValue;
					// GameTime().GetFrameDeltaTime();
					m_Bedspeed += boxMoveValue;//boxMoveSpeed;
				}
			});
			return true;
		});
		QueryGOs<Poison>("Poison", [&](Poison* move) {
			CPhysicsGhostObject* ghostObj = move->GetGhost();
			PhysicsWorld().ContactTest(m_charaCon, [&](const btCollisionObject& contactObject) {
				if (ghostObj->IsSelf(contactObject)) {//== true
					isKill();
				}
			});
			return true;
		});
		QueryGOs<Stone>("Stone", [&](Stone * move) {
			CPhysicsGhostObject* ghostObj = move->GetGhost();
			PhysicsWorld().ContactTest(m_charaCon, [&](const btCollisionObject & contactObject) {
				if (ghostObj->IsSelf(contactObject)) {//== true
					isKill();
				}
			});
			return true;
		});
}
//�N���A�������ǂ����B
void Human::isClear()
{
	//m_lightObject�͒��ԃ|�C���g�ɂȂ����̂ŁA�S�[���̂��߂̃I�u�W�F�ɂ͂Ȃ�܂���B
	//����ɈႤ��g���܂Ђ�B
	CVector3 diff = m_position - m_exit->GetPosition();
	diff.y = 0.0f;
	if (!m_skinModelRender->IsPlayingAnimation()  && m_Clear_one) {
		m_skinModelRender->PlayAnimation(enAnimationClip_run, 0.2f);
		m_movespeed.z -= 6000.0f * GameTime().GetFrameDeltaTime();
	}
	else {
		if (diff.LengthSq() < 70.0f*70.0f
			&& !m_Clear_one) {
			m_skinModelRender->PlayAnimation(enAnimationClip_clear, 0.2f);
			m_Clear_one = true;
			m_movespeed = CVector3::Zero;
			GameData::GetInstance().SetStageClear();
		}
	}
	if (m_Clear_one) {
		m_timer += 1 * GameTime().GetFrameDeltaTime();
		//m_timerfrag����B
		if (m_timer >= 6.0f) {
			m_timer = 0.0f;
			m_game->GameOwari();
			NewGO<Stage_Select>(0,"Stage_Select");
		}
		else if (m_timer >= 3.0f) {
			m_fade->StartFadeOut();
		}
	}
}

void Human::lanpos(CVector3 pos)
{
	CVector3 diff = pos - m_position;

	if (diff.LengthSq() <= 105.0f * 105.0f) {//�v���C���[�Ƌ߂����human�͎~�܂�
		m_movespeed = CVector3::Zero;
	}
	else {
		auto humanspeed = 300.0f;
		m_movespeed = diff;
		m_movespeed.y = 0.0f;
		m_movespeed.Normalize();
		m_movespeed = m_movespeed * humanspeed;
	}
	CVector3 tpos = m_movespeed + m_Bedspeed;
	m_position = m_charaCon.Execute(tpos, GameTime().GetFrameDeltaTime());
}