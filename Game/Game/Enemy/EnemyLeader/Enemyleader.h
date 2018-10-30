#pragma once
#include"../../Player/Player.h"
#include "character/CharacterController.h"
#include"../../Path.h"
#include <array> 
class Enemy;
class Enemyleader:public Gameobject
{
public:
	Enemyleader();
	~Enemyleader();
	//�O���[�v�̏��
	enum State{
		group,
		person,
		gathering
	};
	/*
	*@brief	�|�W�V�����Z�b�g
	*@ CVector3
	*/
	void Setposition(CVector3 Position)
	{
		position = Position;
	}
	/*
	*@brief	�C���X�^���V���O�̃C���X�^���X
	*return SkinModel
	*/
	SkinModel& GetSkinmdel()
	{
		return m_model;
	}
	/*
	*@brief	�v���C���[�̃C���X�^���X�Z�b�g
	*@ Player
	*/
	void Setplayer(Player* pa)
	{
		player = pa;
	}
	/*
	*@brief	�O���[�v�̏�ԃZ�b�g
	*@ Enemyleader::State
	*/
	void SetSteat(State s)
	{
		state = s;
	}
	/*
	*@brief	���[�_�[�̃|�W�V�����Q�b�g
	*@return CVector3
	*/
	CVector3 Getposition()
	{
		return position;
	}
	bool Load();
	void Update();
	void Draw();

	void move();
private:
	CVector3 haiti[5] = {
	{ 70.0f,0.0f,0.0f },
	{-70.0f,0.0f,0.0f},
	{0.0f,0.0f,-70.0f},
	{0.0f,0.0f,70.0f},
	{0.0f,0.0f,0.0f}
	};
	CVector3 haiti2[5] = {
		{ 70.0f,0.0f,0.0f },
	{ -70.0f,0.0f,70.0f },
	{ -70.0f,0.0f,-70.0f },
	{ 70.0f,0.0f,-70.0f },
	{ 0.0f,0.0f,70.0f }
	};													        //���S����ړ���
	CVector3 position = { 0.0f,100.0f,0.0f };				    //�ˋ�̃��[�_�[�̃|�W�V����
	Path* path=nullptr;										    //�o�H�T���p�̃C���X�^���X
	CVector3 m_nextpos = CVector3::Zero();						//�p�X�ړ��p�̎��|�W�V����
	CVector3 m_oldposition = CVector3::Zero();					//1�t���[���O�̃|�W�V�����i�ǎC��Ȃǂ̔���ȂǂȂǁj
	CharacterController m_collider;								//�L�����N�^�[�R���g���[���[
	SkinModel m_model;											//�C���X�^���V���O�p�̕`��C���X�^���X
	static const int SOLDIER = 5;								//���[�_�[���܂ޕ����̑���
	State state = { group };									//�O���[�v�̍��̏��
	Player* player;												//�v���C���[�̃C���X�^���X
	std::array<Enemy*, SOLDIER> enemy;							//�G�l�~�[�̃C���X�^���X�iSOLDIER�j
	//std::vector<Enemy*> enemy;									
	int No = 0;
	int remaining = SOLDIER;									//�����݂̃G�l�~�[����
	int m_time = 0;		//���H�H
};

