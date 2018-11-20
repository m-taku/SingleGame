#pragma once
class Player;
class Gamecamera;
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
	void Draw() override;
private:
	Player* m_player=nullptr;					//�v���C���[�̃C���X�^���X
	Gamecamera* m_camera = nullptr;					//�Q�[���J�����̃C���X�^���X
};

