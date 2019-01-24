#pragma once

#include "physics/PhysicsStaticObject.h"

class Level;
struct LevelObjectData;

/*!
* @brief	マップチップ。
*/
class MapChip {
public:
	/*!
	* @brief	コンストラクタ。
	*@param[in] objData			オブジェクト情報。
	*/
	MapChip(const LevelObjectData& objData);
	/*!
	* @brief	描画。
	*/
	void Draw();
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();
	PhysicsStaticObject* GetPhysicsStaticObject() 
	{
		return &m_physicsStaticObject;
	}
private:
	SkinModel m_model;		//!<モデル。
	PhysicsStaticObject m_physicsStaticObject;	//!<静的物理オブジェクト。
};