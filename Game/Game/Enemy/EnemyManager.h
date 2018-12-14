#pragma once
#include"Player/Player.h"
#include "Enemyleader/Enemyleader.h"
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
	/// �v���C���[�̃C���X�^���X�̃Z�b�g�B
	/// </summary>
	/// <param name="player">
	/// �Z�b�g�������v���C���[�̃C���X�^���X�B(Player*)
	/// </param>
	void SetPlayer(Player* pleyer)
	{
		m_player = pleyer;
	}
private:
	Player * m_player = nullptr;
	std::vector<Enemyleader*> m_enemy;
	Font* m_font = nullptr;											//�����\���̃C���X�^���X
	int m_No = 0;
	Timer* m_timer = nullptr;
};