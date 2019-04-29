#pragma once
/// <summary>
/// アイテムクラス
/// </summary>
#include"status_sani.h"
enum item_group {
	ataac,
	defense,
	life,
	itemnum
};
class Item:public Noncopyable
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Item();
	/// <summary>
	/// デストラクタ。」
	/// </summary>
	~Item();	
	/// <summary>
	/// アイテムの種類のenum
	/// </summary>

	/// <summary>
	/// アイテムの出現位置のセット
	/// </summary>
	/// <param name="pos">
	/// アイテムの出現位置（CVector3）
	/// </param>
	void SetPosition(CVector3 pos)
	{
		m_pos = pos;
	}
	/// <summary>
	/// Gemeobjectから継承したLoat関数。
	/// </summary>
	/// <returns>
	/// 成功でtrue、失敗でfalse。
	/// </returns>
	bool Load();
	/// <summary>
 	/// 毎フレーム呼ばれる関数。
	/// </summary>
	bool Update();
	/// <summary>
	/// 表示用関数。
	/// </summary>
	void Draw();
	/// <summary>
	/// アイテムの種類のセット
	/// （しないと出ません！！）
	/// </summary>
	/// <param name="No">
	/// アイテムの種類のセット（Item::item_group）参照
	/// </param>
	void Setitemtype(item_group No)
	{
		m_item = No;
	}
private:	
	SkinModel m_model;											//モデルデータ
	Player* m_prayer = nullptr;									//プレイヤーのインスタンス
	CVector3 m_pos = CVector3::Zero();							//現在位置
	CQuaternion m_rotetion = CQuaternion::Identity();			//現在回転角度
	item_group m_item= itemnum;									//アイテムの種類
	bool m_hit = false;											//当たったかどうか
	Effekseer::Effect* m_sampleEffect = nullptr;			//エフェクトの実態のポインタ（？）
	Effekseer::Handle m_playEffectHandle;					//エフェクトのさすハンドル
};