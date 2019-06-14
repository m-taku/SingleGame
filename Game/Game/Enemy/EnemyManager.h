#pragma once
#include"Player/Player.h"
#include"Enemyleader/Enemyleader.h"
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
	void SpawnEnemy(CVector3 pos,Ability* k,int count=0);
private:
	Player * m_player = nullptr;
	std::vector<Enemyleader*> m_enemy;
	Font* m_font = nullptr;											//�����\���̃C���X�^���X
	int m_No = 0;
	int m_count = 0;
	bool m_BossSpoon = false;
	int m_Maxsporn = 10;
	Score* m_Score = nullptr;
	std::vector<CVector3> m_spawnpos;
	Timer* m_timer = nullptr;
};