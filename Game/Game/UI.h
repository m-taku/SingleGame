#pragma once
#include"Score.h"
#include"status_sani.h"
class Player;
/// <summary>
/// ユーザーインターフェースクラス。
/// </summary>
class UI :public Gameobject
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	UI();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~UI();
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
	/// プレイヤーに対するダメージによるゲージの減少処理
	/// </summary>
	/// <param name="damage">
	/// ダメージ量（1.0ｆで死亡）（float）
	/// </param>
	void SetDamage(float damage)
	{
		m_Damage = damage;
	}
	/// <summary>
	/// プレイヤーのMpを増やす処理
	/// </summary>
	/// <param name="damage">
	/// MP量（1.0ｆでMax）（float）
	/// </param>
	void AddMp(float Mp)
	{
		m_MP = Mp;
	}
	/// <summary>
	/// 残りの体力を取得（0.0ｆ～1.0ｆ）
	/// </summary>
	/// <returns>
	/// 残りの体力（float）
	/// </returns>
	const float GetHP() const
	{
		return m_HP- m_Damage;
	}
	/// <summary>
	/// スコア計算クラスのインスタンスセット
	/// </summary>
	/// <param name="score">
	/// セットしたいインスタンス（Score*）
	/// </param>
	void SetScore(Score* score)
	{
		m_Score = score;
	}
	void SetPlayer(Player* player)
	{
		m_player = player;
	}
	void SetStetus(Status_bairitu na,float toumei)
	{
		m_status[na].SetclearColor(toumei);
	}
private:
	ShaderResourceView m_Texture_bar_waku;					//HPバーの枠のリソース
	sprite m_HP_bar_waku;									//HPバーの枠の表示用インスタンス
	const CVector3 m_HP_waku_position = {-660.0f,-230.0f,0.0f};	//HPバーの枠の画面上の位置
	ShaderResourceView m_Texture_bar;						//HPバーの中身のリソース
	sprite m_HP_bar;										//HPバーの中身の表示用インスタンス
	const CVector3 m_HP_position = { -657.0f,-232.0f,0.0f };	//HPバーの中身の画面上の位置
	ShaderResourceView m_texture_status_bar;						//HPバーの中身のリソース
	sprite m_status_bar;										//HPバーの中身の表示用インスタンス
	const CVector3 m_status_bar_position = { -620.0f,-220.0f,0.0f };	//HPバーの中身の画面上の位置
	ShaderResourceView m_Texture_bar_waku_MP;						//MPバーの中身のリソース
	sprite m_MP_bar_waku;										//MPバーの中身の表示用インスタンス
	const CVector3 m_MP_waku_position = { -645.0f,-300.0f,0.0f };	//HPバーの枠の画面上の位置
	ShaderResourceView m_Texture_bar_MP;						//MPバーの中身のリソース
	sprite m_MP_bar;										//MPバーの中身の表示用インスタンス
	const CVector3 m_MP_position = { -637.0f,-302.0f,0.0f };	//HPバーの中身の画面上の位置
	ShaderResourceView m_texture_status[num];					//ステータス遷移表示用テクスチャのリソース
	sprite m_status[num];										//ステータス遷移表示用テクスチャのインスタンス
	const CVector3 m_status_position[num] = {
		{-620.0f,-210.0f,0.0f},
	{m_status_position[0].x+30.0f,m_status_position[0].y,m_status_position[0].z },
	{ m_status_position[1].x + 30.0f,m_status_position[1].y,m_status_position[1].z} 
	};														//ステータス遷移表示用テクスチャの画面上の位置
	Score* m_Score = nullptr;								//スコア計算のクラスのインスタンス
	Color m_Color_Mp;
	float m_Damage = 0.0f;									//ダメージ量
	CSoundSource m_bgmA;									//BGM用のインスタンス
	bool m_bool = true;
	float m_MP = 0.0f;
	float m_HP=1.0f;										//残りHP（1で最大）	
	Font m_font;											//文字表示のインスタンス
	Player* m_player = nullptr;
};
