#pragma once


/*
*GameObject�̗D�揇�ʁB
*�l�����������̂قǐ�Ɏ��s�����B
*/
enum GameObjectPriority{
	GameObjectPriority_Default,				//�f�t�H���g�̗D�揇�ʁB
	GameObjectPriority_Game = 1,			//�Q�[������I�u�W�F�N�g�B
	GameObjectPriority_Player = 1,			//�v���C���[�B
	GameObjectPriority_EnemyLeader = 1,		//�G�l�~�[�̃��[�_�[�B
	GameObjectPriority_Camera = 10,			//�J�����͐�΂Ɉ�ԍŌ�B

};
