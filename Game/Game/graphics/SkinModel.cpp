#include "stdafx.h"
#include "SkinModel.h"
#include "SkinModelDataManager.h"
#include"SkinModelEffect.h"

SkinModel::~SkinModel()
{
	if (m_cb != nullptr) {
		//定数バッファを解放。
		m_cb->Release();
	}
	if (m_samplerState != nullptr) {
		//サンプラステートを解放。
		m_samplerState->Release();
	}

}
void SkinModel::Init(const wchar_t* filePath, int maxInstance, EnFbxUpAxis enFbxUpAxis)
{
	//スケルトンのデータを読み込む。
	InitSkeleton(filePath);

	//定数バッファの作成。
	InitConstantBuffer();
	//サンプラステートの初期化。
	InitSamplerState(maxInstance);

	//SkinModelDataManagerを使用してCMOファイルのロード。
	m_modelDx = g_skinModelDataManager.Load(filePath, m_skeleton, maxInstance);

	m_enFbxUpAxis = enFbxUpAxis;
}
void SkinModel::InitSkeleton(const wchar_t* filePath)
{
	//スケルトンのデータを読み込む。
	//cmoファイルの拡張子をtksに変更する。
	std::wstring skeletonFilePath = filePath;
	//文字列から.cmoファイル始まる場所を検索。
	int pos = (int)skeletonFilePath.find(L".cmo");
	//.cmoファイルを.tksに置き換える。
	skeletonFilePath.replace(pos, 4, L".tks");
	//tksファイルをロードする。
	result = m_skeleton.Load(skeletonFilePath.c_str());
	if ( result == false ) {
		//スケルトンが読み込みに失敗した。
		//アニメーションしないモデルは、スケルトンが不要なので
		//読み込みに失敗することはあるので、ログ出力だけにしておく。
#ifdef _DEBUG
		char message[256];
		sprintf(message, "tksファイルの読み込みに失敗しました。%ls\n", skeletonFilePath.c_str());
		OutputDebugStringA(message);
#endif
	}
}
void SkinModel::InitConstantBuffer()
{
	//作成するバッファのサイズをsizeof演算子で求める。
	int bufferSize = sizeof(SVSConstantBuffer);
	//どんなバッファを作成するのかをせてbufferDescに設定する。
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));				//０でクリア。
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;						//バッファで想定されている、読み込みおよび書き込み方法。
	bufferDesc.ByteWidth = (((bufferSize - 1) / 16) + 1) * 16;	//バッファは16バイトアライメントになっている必要がある。
																//アライメントって→バッファのサイズが16の倍数ということです。
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;			//バッファをどのようなパイプラインにバインドするかを指定する。
																//定数バッファにバインドするので、D3D11_BIND_CONSTANT_BUFFERを指定する。
	bufferDesc.CPUAccessFlags = 0;								//CPU アクセスのフラグです。
																//CPUアクセスが不要な場合は0。
	//作成。
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_cb);
	int bufferSize1 = sizeof(LightBuffer);
	//どんなバッファを作成するのかをせてbufferDescに設定する。
	D3D11_BUFFER_DESC bufferDesc1;
	ZeroMemory(&bufferDesc1, sizeof(bufferDesc1));				//０でクリア。
	bufferDesc1.Usage = D3D11_USAGE_DEFAULT;					//バッファで想定されている、読み込みおよび書き込み方法。
	bufferDesc1.ByteWidth = (((bufferSize - 1) / 16) + 1) * 16;	//バッファは16バイトアライメントになっている必要がある。
																//アライメントって→バッファのサイズが16の倍数ということです。
	bufferDesc1.BindFlags = D3D11_BIND_CONSTANT_BUFFER;			//バッファをどのようなパイプラインにバインドするかを指定する。
																//定数バッファにバインドするので、D3D11_BIND_CONSTANT_BUFFERを指定する。
	bufferDesc1.CPUAccessFlags = 0;								//CPU アクセスのフラグです。
																//CPUアクセスが不要な場合は0。
																//作成。
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc1, NULL, &m_ritocb);
}
void SkinModel::InitSamplerState(int maxInstance)
{
	//テクスチャのサンプリング方法を指定するためのサンプラステートを作成。
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	g_graphicsEngine->GetD3DDevice()->CreateSamplerState(&desc, &m_samplerState);
	if (maxInstance > 1) {
		//インスタンシング用のデータを作成。
		m_instancingData.reset(new CMatrix[maxInstance]);
		m_Matrix.resize(maxInstance);
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;	//SRVとしてバインド可能。
		desc.ByteWidth = sizeof(CMatrix) * maxInstance;
		desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		desc.StructureByteStride = sizeof(CMatrix);
		m_instancingDataSB.Create(m_instancingData.get(), desc);
		m_maxInstance = maxInstance;
	}
}
void SkinModel::UpdateInstancingData(
	const CVector3& trans,
	const CQuaternion& rot,
	const CVector3& scale
	/*EnFbxUpAxis enUpdateAxis*/)
{
	UpdateWorldMatrix(trans, rot, scale);
	if (m_numInstance < m_maxInstance) {
		m_instancingData[m_numInstance] = m_worldMatrix;
		if (result) {	
			//3dsMaxと軸を合わせるためのバイアス。
			CMatrix mBias = CMatrix::Identity();
			if (m_enFbxUpAxis == enFbxUpAxisZ) {
				//Z-upttt
				mBias.MakeRotationX(CMath::PI * -0.5f);
			}
			//スキンあり用の行列を生成
			CMatrix transMatrix, rotMatrix, scaleMatrix;
			//平行移動行列を作成する。
			transMatrix.MakeTranslation(trans);
			//回転行列を作成する。
			rotMatrix=CMatrix::Identity();// MakeRotationFromQuaternion(rot);
			//拡大行列を作成する。
			scaleMatrix = CMatrix::Identity();
			//ワールド行列を作成する。
			//拡大×回転×平行移動の順番で乗算するように！
			//順番を間違えたら結果が変わるよ。
			m_worldMatrix = CMatrix::Identity();
			m_worldMatrix.Mul(scaleMatrix, rotMatrix);
			m_worldMatrix.Mul(m_worldMatrix, transMatrix);
			m_instancingData[m_numInstance] = m_worldMatrix;
			m_worldMatrix.Inverse(m_worldMatrix);
			for (int i = 0; i < m_numInstance; i++) {
				m_Matrix[i] = CMatrix::Identity();
				m_Matrix[i].Mul(m_instancingData[i], m_worldMatrix);
			}
		}
		m_numInstance++;
	}
}
//void SkinModel::EndUpdateInstancingData()
//{
//	GraphicsEngine().GetZPrepass().AddSkinModel(this);
//	GraphicsEngine().GetGBufferRender().AddSkinModel(this);				//まだああああああああああ！！！！
//	if (m_isShadowCaster) {
//		GraphicsEngine().GetShadowMap().Entry(&m_shadowCaster);
//	}
//}
void SkinModel::UpdateWorldMatrix(CVector3 position, CQuaternion rotation, CVector3 scale,CVector2 pivot)
{
	//3dsMaxと軸を合わせるためのバイアス。
	CMatrix mBias = CMatrix::Identity();
	if (m_enFbxUpAxis == enFbxUpAxisZ) {
		//Z-up
		mBias.MakeRotationX(CMath::PI * -0.5f);
	}
	CMatrix transMatrix, rotMatrix, scaleMatrix;

	//平行移動行列を作成する。
	transMatrix.MakeTranslation( position );
	//回転行列を作成する。
	rotMatrix.MakeRotationFromQuaternion( rotation );
	rotMatrix.Mul(mBias, rotMatrix);
	//拡大行列を作成する。
	scaleMatrix.MakeScaling(scale);
	//ワールド行列を作成する。
	//拡大×回転×平行移動の順番で乗算するように！
	//順番を間違えたら結果が変わるよ。
	m_worldMatrix.Mul(scaleMatrix, rotMatrix);
	m_worldMatrix.Mul(m_worldMatrix, transMatrix);
	//スケルトンの更新。
	m_skeleton.Update(m_worldMatrix);
}
void SkinModel::Draw(CMatrix viewMatrix, CMatrix projMatrix)
{
	ID3D11DeviceContext* d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	DirectX::CommonStates state(g_graphicsEngine->GetD3DDevice());	
	if (m_maxInstance > 1) {
		//インスタンシング用のデータを更新。
		if (result)
		{
			m_Matrix[m_maxInstance-1] = CMatrix::Identity();
			for (int i = 0; i < m_maxInstance; i++)
			{
				m_instancingData[i] = m_Matrix[i];
			}
		}
		d3dDeviceContext->UpdateSubresource(m_instancingDataSB.GetBody(),  0, NULL, m_instancingData.get(), 0, 0 );
		d3dDeviceContext->VSSetShaderResources(100,1, &(m_instancingDataSB.GetSRV()).GetBody());
	}
	//定数バッファの内容を更新。
	auto shadowMap = g_graphicsEngine->GetShadowMap();
	SVSConstantBuffer vsCb;
	if (result) {
		vsCb.mWorld = CMatrix::Identity();
	}
	else
	{
		vsCb.mWorld = m_worldMatrix;
	}
	vsCb.mProj = projMatrix;
	vsCb.mView = viewMatrix;
	vsCb.mLightProj = shadowMap->GetLightProjMatrix();
	vsCb.mLightView = shadowMap->GetLighViewMatrix();
	if (m_isShadowReciever == true) {
		vsCb.isShadowReciever = 1;
	}
	else {
		vsCb.isShadowReciever = 0;
	}
	LightBuffer LCb;
	LCb.angle = { 0.707f,-0.707f,0.0f,1.0f };
	//夕焼けをイメージした色のデータを作る
	m_colre = 17.0f / 360.0f;
	LCb.color = Color::HSVtoRGB({ m_colre,0.81f,1.0f });
	LCb.Camerapos = g_camera3D.GetPosition();
	d3dDeviceContext->UpdateSubresource(m_cb, 0, nullptr, &vsCb, 0, 0);
	d3dDeviceContext->UpdateSubresource(m_ritocb, 0, nullptr, &LCb, 0, 0);
	//定数バッファをGPUに転送。
	d3dDeviceContext->VSSetConstantBuffers(0, 1, &m_cb);
	d3dDeviceContext->PSSetConstantBuffers(0, 1, &m_cb);
	//ライト用の定数転送
	d3dDeviceContext->PSSetConstantBuffers(1, 1, &m_ritocb);
	//サンプラステートを設定。
	d3dDeviceContext->PSSetSamplers(0, 1, &m_samplerState);
	//ボーン行列をGPUに転送。
	m_skeleton.SendBoneMatrixArrayToGPU(); 
	FindMesh([&](auto& mesh)
	{
		ModelEffect* effect = reinterpret_cast<ModelEffect*>(mesh->effect.get());
		if(m_isShadowCaster)
		{
			if (m_numInstance > 1)
			{
				effect->ChangeShader(ShadowInstancing);
			}
			else
			{
				effect->ChangeShader(ShadowNormal);
			}
		}
		else
		{
			auto deviceContext = g_graphicsEngine->GetD3DDeviceContext();
			ID3D11ShaderResourceView* Resource = g_graphicsEngine->GetShadowMap()->GetShadowMapSRV();
			deviceContext->PSSetShaderResources(5, 1, &Resource);
			if (m_numInstance > 1) {
				effect->ChangeShader(Instancing);

			}
			else {
				effect->ChangeShader(Normal);
			}
		}
	});
	m_isShadowCaster = false;
	//描画。
	m_modelDx->Draw(
		d3dDeviceContext,
		state,
		m_worldMatrix,
		viewMatrix,
		projMatrix,
		false,
		nullptr,
		m_numInstance > 1 ? m_numInstance : 1
	);
}