#pragma once
#include"GameobjectList.h"
/// <summary>
/// Gemeobjectのマネージャークラス
/// </summary>
class GameobjectManager : Noncopyable
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	GameobjectManager();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~GameobjectManager();
	/// <summary>
	/// デリートの処理関数。1フレームでdeleteGOしたものを一括で削除。
	/// エンジン側の処理のため外で呼ばないで！！
	/// </summary>
	void DeleteExecution();
	/// <summary>
	/// オブジェクトの更新処理。
	/// 1フレームで2回以上呼ぶとおかしくなるので注意。
	/// </summary>
	void Execute();
	/// <summary>
	/// Gemeobjectで発生させたい時のNew関数。
	/// </summary>
	/// <param name="No">
	/// 優先度、基本0。（int）
	/// </param>
	/// <param name="name">
	/// 名前、なければNULLもしくは書かない。（char*）
	/// </param>
	/// <returns>
	/// 発生させたインスタンスのポインタ。
	/// </returns>
	template<class T>
	T* NewGO(int No, char* name="NULL")
	{
		return List.at(No).NewGo<T>(No,name);
	}
	/// <summary>
	/// ポインタによるDelete処理。
	/// </summary>
	/// <remarks>
	/// ここでは検索だけで削除自体はDeleteExecutionでしています。
	/// </remarks>
	/// <param name="pointa">
	/// 削除したいインスタンスのポインタ。（Gameobject*）
	/// </param>
	/// <returns>
	/// 検索成功でtrue、失敗でfalse。
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
	/// 名前によるDelete処理。
	/// （複数ある場合は最初のみ削除のため注意！！）
	/// </summary>
	/// <remarks>
	/// ここでは検索だけで削除自体はDeleteExecutionでしています。
	/// </remarks>
	/// <param name="pointa">
	/// 削除したいインスタンスの名前。（char*）
	/// </param>
	/// <returns>
	/// 検索成功でtrue、失敗でfalse。
	/// </returns>
	bool DereteGO(char* Name);
	template<class T>
	/// <summary>
	/// 名前を使ったインスタンス検索
	/// （複数ある場合は最初に積んだものが返ってくるので注意！！）
	/// （検索は重たいので注意！！）
	/// <param name="Name">
	/// 検索したいオブジェクトにつけた名前
	/// </param>
	/// <returns>
	/// 検索成功で検索したインスタンスのポインタ、失敗でNullptr。
	/// </returns>
	T* FindGO(char* Name)
	{
		int No = 0;
		for (const auto& ka : List) {
			No = 0;
			const auto& list = ka.GetName();
			for (const auto& kaa : list) {
				if (Name == kaa) {
					const auto& map = ka.GetList();
					return (T*)map[No];
				}
				No++;
			}
		}
		return nullptr;
	}
private:
	int DeleteNo = 0;								//DeleteListの番号
	std::vector<GameobjectList> List;				//Gemeobjectのリスト（優先度付き）
	std::map<Gameobject*, int> DeleteList[2];		//deleteの際の保存場所（2つあるのはデストラクタでDeleteGOが呼ばれた時の対策）
};