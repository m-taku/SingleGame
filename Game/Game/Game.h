#pragma once
class Player;
class Gamecamera;
class Stage;
class EnemyManager;
class ItemManager;
class HitObjict;
/// <summary>
/// ゲームクラス。
/// </summary>
class Game : public Gameobject
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	Game();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~Game();
	/// <summary>
	/// Gemeobjectから継承したLoat関数。
	/// </summary>
	/// <returns>
	/// 成功でtrue、失敗でfalse。
	/// </returns>
	bool Load() override;
	/// <summary>
	/// Gameobjectから継承したUpdate関数
	/// </summary>
	void Update() override;
	/// <summary>
	/// Gameobjectから継承したDraw関数
	/// </summary>
	void PostDraw() override;
	/// <summary>
	/// Gameobjectから継承したOnDestroy関数
	/// </summary>
	void OnDestroy() override;
private:
	Player* m_player=nullptr;						//プレイヤーのインスタンス
	Gamecamera* m_camera = nullptr;					//ゲームカメラのインスタンス
	Stage* m_stage = nullptr;						//ステージのインスタンス
	EnemyManager* m_enemyManager = nullptr;			//エネミーのマネージャークラスのインスタンス
	UI* m_ui = nullptr;								//ユーザーインターフェースのインスタンス
	ItemManager* m_item = nullptr;
	Score* m_score = nullptr;						//スコアのインスタンス
	Font m_font;											//文字表示のインスタンス
	Timer m_timer;											//タイマークラスのインスタンス

};

