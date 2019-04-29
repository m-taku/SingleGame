#pragma once
class Player;
class Gamecamera;
class Stage;
class EnemyManager;
class ItemManager;
class HitObjict;
/// <summary>
/// �Q�[���N���X�B
/// </summary>
class Game : public Gameobject
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	Game();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~Game();
	/// <summary>
	/// Gemeobject����p������Loat�֐��B
	/// </summary>
	/// <returns>
	/// ������true�A���s��false�B
	/// </returns>
	bool Load() override;
	/// <summary>
	/// Gameobject����p������Update�֐�
	/// </summary>
	void Update() override;
	/// <summary>
	/// Gameobject����p������Draw�֐�
	/// </summary>
	void PostDraw() override;
	/// <summary>
	/// Gameobject����p������OnDestroy�֐�
	/// </summary>
	void OnDestroy() override;
private:
	Player* m_player=nullptr;						//�v���C���[�̃C���X�^���X
	Gamecamera* m_camera = nullptr;					//�Q�[���J�����̃C���X�^���X
	Stage* m_stage = nullptr;						//�X�e�[�W�̃C���X�^���X
	EnemyManager* m_enemyManager = nullptr;			//�G�l�~�[�̃}�l�[�W���[�N���X�̃C���X�^���X
	UI* m_ui = nullptr;								//���[�U�[�C���^�[�t�F�[�X�̃C���X�^���X
	ItemManager* m_item = nullptr;
	Score* m_score = nullptr;						//�X�R�A�̃C���X�^���X
	Font m_font;											//�����\���̃C���X�^���X
	Timer m_timer;											//�^�C�}�[�N���X�̃C���X�^���X

};

