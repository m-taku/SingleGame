#pragma once
#include"level/Level.h"
#include"Navimake.h"
#include"font.h"
#include"physics/PhysicsStaticObject.h"
/// <summary>
/// �X�e�[�W�N���X�B
/// </summary>
class Stage: public Gameobject
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	Stage();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~Stage();
	/// <summary>
	/// Gemeobject����p������Loat�֐��B
	/// </summary>
	/// <returns>
	/// ������true�A���s��false�B
	/// </returns>
	bool Load() override;
	/// <summary>
	/// Gameobject����p������Update�֐��B
	/// </summary>
	void Update() override;
	/// <summary>
	/// Gameobject����p������Draw�֐��B
	/// </summary>
	void Draw() override;
	/// <summary>
	/// Gameobject����p������postDraw�֐��B
	/// </summary>
	void PostDraw() override;
private:
//	PhysicsStaticObject Stege;
	//SkinModel m_model;

	Font m_font;						//�����\���̃C���X�^���X
	Level m_level;						//�X�e�[�W�\���p�̃��x���C���X�^���X					
	Navimake* m_navimake = nullptr;		//�i�r�Q�[�V�������b�V���쐬�����B

};

