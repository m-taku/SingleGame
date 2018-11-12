#pragma once
#include"Gameobject.h"
/// <summary>
/// Gameobject�̃C���X�^���X�̃��X�g�N���X
/// </summary>
class GameobjectList
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	GameobjectList();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~GameobjectList();
	template<class T>
	/// <summary>
	/// Gemeobject�Ŕ���������������New�֐��B
	/// </summary>
	/// <param name="No">
	/// �D��x�A��{0�B�iint�j
	/// </param>
	/// <param name="name">
	/// ���O�A�Ȃ����NULL�B�ichar*�j
	/// </param>
	/// <returns>
	/// �����������C���X�^���X�̃|�C���^�B
	/// </returns>
	T* NewGo(int No=0,char* name="NULL")
	{
		T* object = new T;
		object->SetPriority(No);
		m_ObjectList.push_back(object);
		m_Name.push_back(name);
		return object;
	}
	//template<class T>
	//T* NewGo(int No)
	//{
	//	T* object = new T;
	//	object->setpriority(No);
	//	ObjectList.push_back(object);
	//	Name.push_back("NULL");
	//	return object;
	//}	
	/// <summary>
	/// 1�P��Delete�������ꍇ��Delete�֐��B
	/// �G���W�����̏����̂��ߊO�ŌĂ΂Ȃ��ŁI�I
	/// </summary>
	/// <param name="object">
	/// �폜���������C���X�^���X�̃|�C���^�B
	/// </param>
	/// <param name="no">
	/// ���Ԗڂɂ��邩�B
	/// </param>
	/// <returns>
	/// �폜������true�A���s��false�B
	/// </returns>
	bool DereteGo(Gameobject* object,int no);
	/// <summary>
	/// ����D��x�̒��ɂ���Gameobject�̃��X�g�̎擾�B
	/// �G���W�����̏����̂��ߊO�ŌĂ΂Ȃ��ŁI�I
	/// </summary>
	/// <returns>
	/// Gemeobjject�̉ϒ��z��B(std::vector<Gameobject*>)
	/// </returns>
    std::vector<Gameobject*> GetList() const
	{
		return m_ObjectList;

	}
	/// <summary>
	/// ����D��x�̒��ɂ��閼�O�̃��X�g�擾�B
	/// �G���W�����̏����̂��ߊO�ŌĂ΂Ȃ��ŁI�I
	/// </summary>
	/// <returns>
	/// ������̉ϒ��z��B�iconst std::vector<std::string>&�j
	/// </returns>
	const std::vector<std::string>& GetName() const
	{
		return m_Name;
	}
private:
	std::vector<std::string> m_Name;				//�C���X�^���X�̖��O
	std::vector<Gameobject*> m_ObjectList;			//�C���X�^���X�̔z��
};

