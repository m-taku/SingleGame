#pragma once


/*
*GameObject�̗D�揇�ʁB
*�l�����������̂قǐ�Ɏ��s�����B
*/
enum GameObjectPriority{
	GameObjectPriority_Default,				//�f�t�H���g�̗D�揇�ʁB
	GameObjectPriority_Game,			//�Q�[������I�u�W�F�N�g�B
	GameObjectPriority_Player,			//�v���C���[�B
	GameObjectPriority_EnemyLeader,		//�G�l�~�[�̃��[�_�[�B
	GameObjectPriority_Camera = 10,			//�J�����͐�΂Ɉ�ԍŌ�B

};
