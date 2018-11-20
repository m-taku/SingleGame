#pragma once
#include"Gameobject.h"
/// <summary>
/// Gameobjectのインスタンスのリストクラス
/// </summary>
class GameobjectList
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	GameobjectList();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~GameobjectList();
	/// <summary>
	/// Gemeobjectで発生させたい時のNew関数。
	/// エンジン側の処理のため外で呼ばないで！！
	/// </summary>
	/// <param name="object">
	/// プッシュしたいインスタンスのポインタ
	/// </param>
	void PushObject(Gameobject* object)
	{
		m_ObjectList.push_back(object);
		
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
	/// 1つ１つDeleteしたい場合のDelete関数。
	/// エンジン側の処理のため外で呼ばないで！！
	/// </summary>
	/// <param name="object">
	/// 削除させたいインスタンスのポインタ。
	/// </param>
	/// <param name="no">
	/// 何番目にいるか。
	/// </param>
	/// <returns>
	/// 削除成功でtrue、失敗でfalse。
	/// </returns>
	bool DereteGo(Gameobject* object,int no);
	/// <summary>
	/// ある優先度の中にあるGameobjectのリストの取得。
	/// エンジン側の処理のため外で呼ばないで！！
	/// </summary>
	/// <returns>
	/// Gemeobjjectの可変長配列。(std::vector(ameobject*))
	/// </returns>
    const std::vector<Gameobject*>& GetList() const
	{
		return m_ObjectList;

	}
	///// <summary>
	///// ある優先度の中にある名前のリスト取得。
	///// エンジン側の処理のため外で呼ばないで！！
	///// </summary>
	///// <returns>
	///// 文字列の可変長配列。（const std::vector<std::string>&）
	///// </returns>
	//const std::vector<std::string>& GetName() const
	//{
	//	return m_Name;
	//}
private:
	//std::vector<std::string> m_Name;				//インスタンスの名前
	std::vector<Gameobject*> m_ObjectList;			//インスタンスの配列
};

