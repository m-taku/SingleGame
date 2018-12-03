#include "stdafx.h"
#include "PhysicsDebugDraw.h"


void PhysicsDebugDraw::Init()
{
	m_primitive.Create(
		D3D_PRIMITIVE_TOPOLOGY_LINELIST,
		static_cast<int>(m_vertexBuffer.size()),
		sizeof(CVector4),
		&m_vertexBuffer[0],
		0,
		indexBuffer::enIndexType_32,
		nullptr
	);
	m_vs.Load("Assets/shader/linePrimitive.fx", "VSMain", Shader::EnType::VS);
	m_ps.Load("Assets/shader/linePrimitive.fx", "PSMain", Shader::EnType::PS);
	m_cb.Create(nullptr, sizeof(SConstantBuffer));
	m_cb2.Create(nullptr, sizeof(CVector4));
}
void PhysicsDebugDraw::BeginDraw()
{
	DeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	m_numLine = 0;
}
void PhysicsDebugDraw::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{
	int baseIndex = m_numLine * 2;
	m_vertexBuffer[baseIndex].Set(CVector3(from.x(), from.y(), from.z()));
	m_vertexBuffer[baseIndex + 1].Set(CVector3(to.x(), to.y(), to.z()));
	m_numLine++;
}
void PhysicsDebugDraw::EndDraw()
{
	//定数バッファの更新。
	SConstantBuffer cb;
	cb.mView = g_camera3D.GetViewMatrix();
	cb.mProj = g_camera3D.GetProjectionMatrix();
	CVector4 colr;


	colr = { 1.0f,1.0f,1.0f,1.0f };
	DeviceContext->UpdateSubresource(m_cb2.GetBody(), 0, NULL, &colr, 0, 0);
	DeviceContext->PSSetConstantBuffers(1, 1, &(m_cb2.GetBody()));
	DeviceContext->UpdateSubresource(m_cb.GetBody(), 0, NULL, &cb, 0, 0);
	DeviceContext->VSSetShader((ID3D11VertexShader*)m_vs.GetBody(), NULL, 0);
	DeviceContext->PSSetShader((ID3D11PixelShader*)m_ps.GetBody(), NULL, 0);
	DeviceContext->VSSetConstantBuffers(0, 1, &(m_cb.GetBody()));
	//入力レイアウトを設定。
	DeviceContext->IASetInputLayout(m_vs.GetInputLayout());
	DeviceContext->UpdateSubresource(m_primitive.GetVertexBuffer().GetBody(),0, NULL, &m_vertexBuffer[0], 0, 0);
	m_primitive.Draw(*DeviceContext, m_numLine * 2);
}