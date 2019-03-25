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
#include <xaudio2.h>
#include <x3daudio.h>
#include <xaudio2fx.h>
#include <array>
//
//#define _CRTDBG_MAP_ALLOC #include <stdlib.h> #include <crtdbg.h>  
#include "btBulletDynamicsCommon.h"
#include "BulletCollision\CollisionDispatch\btGhostObject.h"
#include"Noncopyable/Noncopyable.h"

#include "Effekseer.h" 
#include "EffekseerRendererDX11.h"
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
#include "color.h"
#include "physics/Physics.h"
#include "GameObjectPriority.h"
#include"font.h"
#include"Timer.h"
#include "VectorDraw.h"
#include "HitObjict.h"
#include"GameTime.h"
using namespace time1;
extern GameobjectManager* g_objectManager;
const float GRAVITY = 9.8f * 10.0f;
const float FRAME_BUFFER_W = 1280.0f;				//�t���[���o�b�t�@�̕��B
const float FRAME_BUFFER_H = 720.0f;				//�t���[���o�b�t�@�̍����B

static const int MAX_BONE = 512;	//!<�{�[���̍ő吔�B
