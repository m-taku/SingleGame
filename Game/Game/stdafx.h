#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <math.h>
#include <vector>
#include <list>
#include <D3Dcompiler.h>
#include <Windows.h>
#include <d3d11.h>
#include <map>
#include <functional>
#include <algorithm>
#include <array>

#define _CRTDBG_MAP_ALLOC #include <stdlib.h> #include <crtdbg.h>  
#include "btBulletDynamicsCommon.h"
#include "BulletCollision\CollisionDispatch\btGhostObject.h"
#include"Noncopyable/Noncopyable.h"

#include"Gameobject/GameobjectManager.h"
//DirectXTK�̃C���N���[�h�t�@�C���B
#include "DirectXTK/Inc/Model.h"
#include "DirectXTK/Inc/Effects.h"	
#include "DirectXTK/Inc/CommonStates.h"
#include "DirectXTK/Inc/SpriteFont.h"
#include "DirectXTK/Inc/DDSTextureLoader.h"

#include "HID/Pad.h"

#include "math/Vector.h"
#include "math/Matrix.h"
#include "graphics/Camera.h"
#include "graphics/GraphicsEngine.h"

#include "graphics/SkinModel.h"
#include "graphics/Skeleton.h"

#include "graphics/animation/Animation.h"
#include "graphics/animation/AnimationClip.h"
#include "graphics/sprite.h"
#include "Gameobject/Gameobject.h"
#include "VectorDraw.h"
#include "color.h"
#include "physics/Physics.h"
#include "GameObjectPriority.h"
#include "GameObjectName.h"
#include"font.h"
#include"Timer.h"
extern GameobjectManager* g_objectManager;
extern bool frame(CVector3 position);
const float GRAVITY = 9.8f * 30;
const float FRAME_BUFFER_W = 1280.0f;				//�t���[���o�b�t�@�̕��B
const float FRAME_BUFFER_H = 720.0f;				//�t���[���o�b�t�@�̍����B

static const int MAX_BONE = 512;	//!<�{�[���̍ő吔�B
