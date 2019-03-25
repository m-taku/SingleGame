#pragma once
#include"level/Level.h"
#include"Navimake.h"
#include"font.h"
#include"physics/PhysicsStaticObject.h"
/// <summary>
/// ステージクラス。
/// </summary>
class Stage: public Gameobject
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	Stage();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~Stage();
	/// <summary>
	/// Gemeobjectから継承したLoat関数。
	/// </summary>
	/// <returns>
	/// 成功でtrue、失敗でfalse。
	/// </returns>
	bool Load() override;
	/// <summary>
	/// Gameobjectから継承したUpdate関数。
	/// </summary>
	void Update() override;
	/// <summary>
	/// Gameobjectから継承したDraw関数。
	/// </summary>
	void Draw() override;
	/// <summary>
	/// Gameobjectから継承したpostDraw関数。
	/// </summary>
	void PostDraw() override;
	/// <summary>
	/// Gameobjectから継承したOnDestroy関数
	/// </summary>
	void OnDestroy() override;
private:
	CSoundSource m_bgmA;						//BGM用のインスタンス
	Level m_level;								//ステージ表示用のレベルインスタンス					
	Navimake* m_navimake = nullptr;				//ナビゲーションメッシュ作成処理。

};

