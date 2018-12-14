#pragma once
#include"GameobjectList.h"
class Font;
class Timer;
/// <summary>
/// Gemeobject�̃}�l�[�W���[�N���X
/// </summary>
class GameobjectManager : Noncopyable
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	GameobjectManager();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~GameobjectManager();
	/// <summary>
	/// �f���[�g�̏����֐��B1�t���[����deleteGO�������̂��ꊇ�ō폜�B
	/// �G���W�����̏����̂��ߊO�ŌĂ΂Ȃ��ŁI�I
	/// </summary>
	void DeleteExecution();
	/// <summary>
	/// New�̏����֐��B1�t���[����NewGO�������̂��ꊇ�œo�^�B
	/// �G���W�����̏����̂��ߊO�ŌĂ΂Ȃ��ŁI�I
	/// </summary>
	void NewExecution();
	/// <summary>
	/// �������
	/// </summary>
	void Release();
	/// <summary>
	/// �I�u�W�F�N�g�̍X�V�����B
	/// 1�t���[����2��ȏ�ĂԂƂ��������Ȃ�̂Œ��ӁB
	/// </summary>
	void Execute();
	/// <summary>
	/// Gemeobject�Ŕ���������������New�֐��B
	/// </summary>
	/// <param name="No">
	/// �D��x�A��{0�B�iint�j
	/// </param>
	/// <param name="name">
	/// ���O�A�Ȃ����NULL�������͏����Ȃ��B�ichar*�j
	/// </param>
	/// <returns>
	/// �����������C���X�^���X�̃|�C���^�B
	/// </returns>
	template<class T>
	T* NewGO(int No, const char* name="NULL")
	{
		T* object = new T;
		object->SetName(name);
		object->SetPriority(No);
		m_newLest.insert({ object, No });
		return object;
	}
	/// <summary>
	/// �|�C���^�ɂ��Delete�����B
	/// </summary>
	/// <remarks>
	/// �����ł͌��������ō폜���̂�DeleteExecution�ł��Ă��܂��B
	/// </remarks>
	/// <param name="pointa">
	/// �폜�������C���X�^���X�̃|�C���^�B�iGameobject*�j
	/// </param>
	/// <returns>
	/// ����������true�A���s��false�B
	/// </returns>
	bool DereteGO(Gameobject* pointa);
	//{
	//	No = 0;
	//	for (auto kaa : List[pointa->Getpriority()].GetList())
	//	{
	//		if (kaa == pointa)
	//		{
	//			DeleteList[DeleteNo].insert(std::make_pair(pointa, No));
	//			return true;
	//		}
	//		No++;
	//	}
	//	return false;
	//}
	/// <summary>
	/// ���O�ɂ��Delete�����B
	/// �i��������ꍇ�͍ŏ��̂ݍ폜�̂��ߒ��ӁI�I�j
	/// </summary>
	/// <remarks>
	/// �����ł͌��������ō폜���̂�DeleteExecution�ł��Ă��܂��B
	/// </remarks>
	/// <param name="pointa">
	/// �폜�������C���X�^���X�̖��O�B�ichar*�j
	/// </param>
	/// <returns>
	/// ����������true�A���s��false�B
	/// </returns>
	bool DereteGO(char* Name);
	template<class T>
	/// <summary>
	/// ���O���g�����C���X�^���X����
	/// �i��������ꍇ�͍ŏ��ɐς񂾂��̂��Ԃ��Ă���̂Œ��ӁI�I�j
	/// �i�����͏d�����̂Œ��ӁI�I�j
	/// <param name="Name">
	/// �����������I�u�W�F�N�g�ɂ������O
	/// </param>
	/// <returns>
	/// ���������Ō��������C���X�^���X�̃|�C���^�A���s��Nullptr�B
	/// </returns>
	T* FindGO(char* Name)
	{
		int No = 0;
		for (const auto& list : m_List) {
			No = 0;
			for (const auto& objedct : list.GetList()) {
				if (Name == objedct->GetName()) {
					const auto& map = list.GetList();
					return (T*)map[No];
				}
				No++;
			}
		}
		return nullptr;
	}
private:
	enum { NUM_PRIORITY = 20 };								//�D�揇�ʂ̐��B
	int m_DeleteNo = 0;										//DeleteList�̔ԍ�
	std::array<GameobjectList, NUM_PRIORITY>	m_List;		//Gemeobject�̃��X�g�i�D��x�t���j
	std::map<Gameobject*, int> m_DeleteList[2];				//delete�̍ۂ̕ۑ��ꏊ�i2����̂̓f�X�g���N�^��DeleteGO���Ă΂ꂽ���̑΍�j
	std::map<Gameobject*, int> m_newLest;					//new�̍ۂ̕ۑ��ꏊ�i�j
};