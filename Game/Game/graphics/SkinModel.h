#pragma once

#include "Skeleton.h"
#include"Buffer/StucturedBuffer.h"

/*!
*@brief	FBXの上方向。
*/
enum EnFbxUpAxis {
	enFbxUpAxisY,		//Y-up
	enFbxUpAxisZ,		//Z-up
};
/*!
*@brief	スキンモデルクラス。
*/
class SkinModel:public Noncopyable
{
public:
	//メッシュが見つかったときのコールバック関数。
	using OnFindMesh = std::function<void(const std::unique_ptr<DirectX::ModelMeshPart>&)>;
	/*!
	*@brief	デストラクタ。
	*/
	~SkinModel();
	
	/*!
	*@brief	初期化。
	*@param[in]	filePath		ロードするcmoファイルのファイルパス。
	*@param[in] enFbxUpAxis		fbxの上軸。デフォルトはenFbxUpAxisZ。
	*/
	void Init(const wchar_t* filePath,int maxInstance=1, EnFbxUpAxis enFbxUpAxis = enFbxUpAxisZ);
	/*!
	*@brief	インスタンスデータの更新開始時に呼び出してください。
	*/																					
	void BeginUpdateInstancingData()
	{
		m_numInstance = 0;
	}
	void UpdateInstancingData(
		const CVector3& trans,
		const CQuaternion& rot,
		const CVector3& scale
		/*EnFbxUpAxis enUpdateAxis*/);

	//void EndUpdateInstancingData()　　//まだああああああああああああああああ！！！！！！！！！！！！！！！！！
	/*!

	*@brief	モデルをワールド座標系に変換するためのワールド行列を更新する。
	*@param[in]	position	モデルの座標。
	*@param[in]	rotation	モデルの回転。
	*@param[in]	scale		モデルの拡大率。
	*/
	void UpdateWorldMatrix(CVector3 position, CQuaternion rotation, CVector3 scale, CVector2 pivot = {0.5,0.5});
	/*!
	*@brief	ボーンを検索。
	*@param[in]		boneName	ボーンの名前。
	*@return	見つかったボーン。見つからなかった場合はnullptrを返します。
	*/
	Bone* FindBone(const wchar_t* boneName)
	{
		int boneId = m_skeleton.FindBoneID(boneName);
		return m_skeleton.GetBone(boneId);
	}
	/*!
	*@brief	モデルを描画。
	*@param[in]	viewMatrix		カメラ行列。
	*  ワールド座標系の3Dモデルをカメラ座標系に変換する行列です。
	*@param[in]	projMatrix		プロジェクション行列。
	*  カメラ座標系の3Dモデルをスクリーン座標系に変換する行列です。
	*/
	void Draw( CMatrix viewMatrix, CMatrix projMatrix );
	/*!
	*@brief	スケルトンの取得。
	*/
	Skeleton& GetSkeleton() 
	{
		return m_skeleton;
	}
	/*!
	*@brief	メッシュを検索する。
	*@param[in] onFindMesh		メッシュが見つかったときのコールバック関数
	*/
	void FindMesh(OnFindMesh onFindMesh) const
	{
		for (auto& modelMeshs : m_modelDx->meshes) {
			for (std::unique_ptr<DirectX::ModelMeshPart>& mesh : modelMeshs->meshParts) {
				onFindMesh(mesh);
			}
		}
	}
	/*!
	*@brief	SRVのレジスタ番号。
	*/
	enum EnSkinModelSRVReg {
		enSkinModelSRVReg_DiffuseTexture = 0,		//!<ディフューズテクスチャ。
		enSkinModelSRVReg_BoneMatrix,				//!<ボーン行列。
	};
	/// <summary>
	/// シャドウレシーバーのフラグを設定する。
	/// </summary>
	/// <param name="flag">trueを渡すとシャドウレシーバーになる</param>
	/// <remarks>
	/// シャドウレシーバーとは影を落とされるオブジェクトのことです。
	/// シャドウキャスターによって生成された、シャドウマップを利用して
	/// 自身に影を落とします。
	/// オブジェクトがシャドウレシーバーかつシャドウキャスターになっている場合は
	/// セルフシャドウ(自分の影が自分に落ちる)を行うことができます。
	/// </remarks>
	void SetShadowReciever(bool flag)
	{
		m_isShadowReciever = flag;
	}
	void SetShadowCaster(bool flag)
	{
		m_isShadowCaster = flag;
	}
private:
	/*!
	*@brief	サンプラステートの初期化。
	*/
	void InitSamplerState(int maxInstance);
	/*!
	*@brief	定数バッファの作成。
	*/
	void InitConstantBuffer();
	/*!
	*@brief	スケルトンの初期化。
	*@param[in]	filePath		ロードするcmoファイルのファイルパス。
	*/
	void InitSkeleton(const wchar_t* filePath);
private:
	//定数バッファ。
	struct SVSConstantBuffer {
		CMatrix mWorld;
		CMatrix mView;
		CMatrix mProj;
		CMatrix mLightView;		//ライトビュー行列。
		CMatrix mLightProj;		//ライトプロジェクション行列。
		int isShadowReciever;	//シャドウレシーバーのフラグ。
	};	
	//定数バッファ。
	struct LightBuffer {
		CVector4 angle;
		CVector4 color;
		CVector4 Camerapos;
	};
	EnFbxUpAxis			m_enFbxUpAxis = enFbxUpAxisZ;	//!<FBXの上方向。
	ID3D11Buffer*		m_cb = nullptr;					//!<定数バッファ。
	ID3D11Buffer*		m_ritocb = nullptr;	         	//!<定数ライトバッファ。
	Skeleton			m_skeleton;						//!<スケルトン。
	CMatrix				m_worldMatrix;					//!<ワールド行列。
	DirectX::Model*		m_modelDx;						//!<DirectXTKが提供するモデルクラス。
	ID3D11SamplerState* m_samplerState = nullptr;		//!<サンプラステート。	
	std::unique_ptr<CMatrix[]>	m_instancingData;		//!<インスタンシング描画用のデータ。
	std::vector<CMatrix> m_Matrix;						//スキンモデル付きのインスタンシング用配列
	float m_colre = 0.0f;								//ライトの色
	bool result = false;									//スキンモデルにボーンがあるかどうか
	static const int m_Max = 100;						//インスタンシング用
	int m_numInstance = 0;								//!<インスタンシング用の個数
	int m_maxInstance = 0;							    //!<インスタンシングデータの最大数(これ以上は表示できません)
	StucturedBuffer	m_instancingDataSB;				    //!<インスタンシング描画用のストラクチャーバッファ。
	bool m_isShadowReciever = false;					//!<シャドーレシーバーにするかのフラグ

	bool m_isShadowCaster = false;
};

