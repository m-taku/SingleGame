#pragma once

#include "physics/PhysicsStaticObject.h"

class Level;
struct LevelObjectData;

/*!
* @brief	�}�b�v�`�b�v�B
*/
class MapChip {
public:
	/*!
	* @brief	�R���X�g���N�^�B
	*@param[in] objData			�I�u�W�F�N�g���B
	*/
	MapChip(const LevelObjectData& objData);
	/*!
	* @brief	�`��B
	*/
	void Draw();
	PhysicsStaticObject* GetPhysicsStaticObject() 
	{
		return &m_physicsStaticObject;
	}
private:
	SkinModel m_model;		//!<���f���B
	PhysicsStaticObject m_physicsStaticObject;	//!<�ÓI�����I�u�W�F�N�g�B
};