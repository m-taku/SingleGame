#pragma once

/// <summary>
/// GameObject�̗D�揇��
/// </summary>
/// <remarks>
/// �l�����������̂قǐ�Ɏ��s�����B
/// </remarks>
enum GameObjectPriority{
	GameObjectPriority_Game,			//�Q�[������I�u�W�F�N�g�B
	GameObjectPriority_Default,			//�f�t�H���g�̗D�揇�ʁB
	GameObjectPriority_Player,			//�v���C���[�B
	GameObjectPriority_EnemyLeader,		//�G�l�~�[�̃��[�_�[�B
	GameObjectPriority_ta,		//�Q�[���I�[�o�[�͕\���̊֌W�ōŌ�̂ق���
	GameObjectPriority_Gameover,		//�Q�[���I�[�o�[�͕\���̊֌W�ōŌ�̂ق���
	GameObjectPriority_Camera = 10		//�J�����͐�΂Ɉ�ԍŌ�B

};
