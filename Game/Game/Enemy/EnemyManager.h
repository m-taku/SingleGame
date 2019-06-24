#pragma once
#include"Player/Player.h"
#include"Enemyleader/Enemyleader.h"
#include <random>
/// <summary>
/// �G�l�~�[�̃}�l�[�W���[�N���X
/// </summary>
class EnemyManager :public Gameobject
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	EnemyManager();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~EnemyManager();
	/// <summary>
	/// Gameobject����p�������ŏ��ɌĂ΂��֐��B
	/// </summary>
	/// <returns>
	/// Load������true�A���s��false�B
	/// </returns>
	bool Load() override;
	/// <summary>
	/// GemeObject����p������Update�֐��B
	/// </summary>
	void Update() override;
	/// <summary>
	/// Gameobject����p������comeback�֐�
	/// </summary>
	void Comeback() override;
	/// <summary>
	/// �v���C���[�̃C���X�^���X�̃Z�b�g�B
	/// </summary>
	/// <param name="player">
	/// �Z�b�g�������v���C���[�̃C���X�^���X�B(Player*)
	/// </param>
	void SetPlayer(Player* pleyer)
	{
		m_player = pleyer;
	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="score"></param>
	void SetScore(Score* score)
	{
		m_Score = score;
	}
	bool SpawnEnemy(CVector3 ispos)
	{
		//�����̏���ɒB���Ă��Ȃ����
		if (m_Maxsporn >= m_enemy.size()) {
			float lengthMax = FLT_MAX;
			int No;
			for (int i = 0; i < m_spawnpos.size(); i++)
			{
				auto len = (m_spawnpos[i] - ispos).Length();
				if (lengthMax >= len)
				{
					No = i;
					lengthMax = len;
				}
			}
			
			std::random_device rnd;     // �񌈒�I�ȗ���������𐶐�
			std::mt19937 mt(rnd());     //  �����Z���k�E�c�C�X�^��32�r�b�g�ŁA�����͏����V�[�h�l
			std::uniform_int_distribution<> rand2(1,5);        // [0, 99] �͈͂̈�l����
			Ability* ability;
			switch (rand2(mt))
			{
			case 1:
			case 2:
			case 3:			
			case 4:
				ability = new enemy_hero;
				ability->m_Spawnnum = 3;
				break;
			case 5:
				ability = new enemy_Lance;
				break;
			default:
				break;
			}
			SpawnEnemy(m_spawnpos[No], ability);
			return true;
		}
		return false;
	}
	void SpawnEnemy(CVector3 pos,  Ability* ability, CQuaternion angle=CQuaternion::Identity(), int count=0);
private:
	Player * m_player = nullptr;
	std::vector<Enemyleader*> m_enemy;
	Font* m_font = nullptr;											//�����\���̃C���X�^���X
	int m_No = 0;
	int m_count = 0;
	bool m_BossSpoon = false;
	int m_Maxsporn = 30;
	Score* m_Score = nullptr;
	std::vector<CVector3> m_spawnpos;
	Timer* m_timer = nullptr;
};