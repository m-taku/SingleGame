#pragma once

/// <summary>
/// GameObject�̗D�揇��
/// </summary>
/// <remarks>
/// �l�����������̂قǐ�Ɏ��s�����B
/// </remarks>
enum GameObjectPriority{
	GameObjectPriority_Default,			//�f�t�H���g�̗D�揇�ʁB
	GameObjectPriority_Game,			//�Q�[������I�u�W�F�N�g�B
	GameObjectPriority_Player,			//�v���C���[�B
	GameObjectPriority_EnemyLeader,		//�G�l�~�[�̃��[�_�[�B
	GameObjectPriority_Camera = 10,		//�J�����͐�΂Ɉ�ԍŌ�B

};
