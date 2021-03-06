#pragma once
#include "HitReceive.h"
/// <summary>
/// 簡易な当たり判定
/// </summary>
namespace time1 {
	class HitObjict
	{
	public:
		/// <summary>
		/// コンストラクタ
		/// </summary>
		HitObjict()
		{

		}
		/// <summary>
		/// デストラクタ
		/// </summary>
		~HitObjict()
		{
			Release();
		}
		/// <summary>
		/// Hitオブジェクトのインスタンスのゲット
		/// </summary>
		/// <returns>
		/// Hitオブジェクトのインスタンスの
		/// </returns>
		static inline HitObjict& GetHitObjict()
		{
			static HitObjict t;
			return t;
		}
		const HitReceive* Create(const CVector3* pos, float radius, std::function<void(float damage)> objict, HitReceive::objict_Name name)
		{
			auto ka = new HitReceive;
			ka->Create(pos, radius, objict, name);
			m_objict.push_back(ka);
			return ka;
		}
		/// <summary>
		/// 当たり判定の発生（球）
		/// </summary>
		/// <param name="pos">
		/// 当たり判定の中心座標
		/// </param>
		/// <param name="Circle">
		/// 当たり判定の球の大きさ
		/// </param>
		/// <param name="damage">
		/// 与えたいダメージの量
		/// </param>
		/// <param name="name">
		/// 当てたい対象
		/// </param>
		/// <returns>
		/// 当たったらtrue
		/// </returns>
		bool HitTest(CVector3 pos, float Circle, float damage, HitReceive::objict_Name name)
		{
			bool furag = false;
			for (auto hit : m_objict)
			{
				//当てたい物体を検索する
				if (hit->Getobjict_Name() == name) {
					//当たり判定を行う。
					if (hit->HitTest(pos, Circle, damage)) {
						furag = true;
					}
				}
			}
			return furag;
		}
		void Deleteobjict(const HitReceive* objict)
		{
			m_objict.erase(std::find(m_objict.begin(), m_objict.end(), objict));
			delete objict;
		}
		void Release()
		{
			for (auto k : m_objict)
			{
				delete k;
			}
			m_objict.clear();
		}
	private:
		std::list<HitReceive*> m_objict;
	};
	static HitObjict& GetHitObjict()
	{
		return  HitObjict::GetHitObjict();
	}
}