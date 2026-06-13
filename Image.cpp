#include "Image.h"
#include "BaseObject.h"
#include "BootScene.h"
#include "ImGUI/imgui.h"
#include <wincodec.h>
#include <vector>
#include "Camera.h"

using namespace DirectX;

Image::Image(const std::string& path, const float leftX, const float leftY)
	: BaseObject("Image", true) {
	this->path_ = path;

	// DirectXでは、2個の三角形を組み合わせて描画するイメージ
	//  |------------|
	//  |[0,1,2] /   |
	//  |       /    |
	//  |     /      |
	//  |   / [3,4,5]|
	//  |------------|

	vertices_[0] = { 0.0f, 0.0f, 0.0f, 0,1,0,1, 0, 0 }; // 左上 
	vertices_[1] = { 0.0f, leftY, 0.0f, 1,0,0,1, 0, 1 }; // 左下
	vertices_[2] = { leftX, 0.0f, 0.0f, 0,0,1,1, 1, 0 }; // 右上

	vertices_[3] = { leftX, 0.0f, 0.0f, 0,0,1,1, 1, 0 }; // 右上
	vertices_[4] = { leftX, leftY, 0.0f, 1,1,0,1, 1, 1 }; // 右下
	vertices_[5] = { 0.0f, leftY, 0.0f, 1,0,0,1, 0, 1 }; // 左下
	
}

void Image::Init() {
	HRESULT result = { 0 };
	std::wstring wPath(path_.begin(), path_.end());

	result = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pFactory));
	assert(SUCCEEDED(result));
	result = pFactory->CreateDecoderFromFilename(
		wPath.c_str(),
		nullptr,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
	);
	assert(SUCCEEDED(result));
	result = pDecoder->GetFrame(0, &pFrame);
	assert(SUCCEEDED(result));

	result = pFactory->CreateFormatConverter(&pConverter);

	pConverter->Initialize(
		pFrame,
		GUID_WICPixelFormat32bppRGBA,
		WICBitmapDitherTypeNone,
		nullptr,
		1.0f,
		WICBitmapPaletteTypeMedianCut
	);
	pConverter->GetSize(&width_, &height_);

	//参考：https://learn.microsoft.com/ja-jp/windows/win32/api/d3d11/ns-d3d11-d3d11_render_target_blend_desc
	D3D11_BLEND_DESC blendDesc = {};
	blendDesc.RenderTarget[0].BlendEnable = TRUE; //ブレンドを有効にする
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA; 
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	DirectX3D::d3d11Device_->CreateBlendState(&blendDesc, &blendState); //ブレンドステートを作成する

	//参考： https://learn.microsoft.com/ja-jp/windows/win32/api/d3d11/ns-d3d11-d3d11_rasterizer_desc
	D3D11_RASTERIZER_DESC rasterizerDesc = {};
	rasterizerDesc.FillMode = D3D11_FILL_SOLID; // レンダリング時に使用する塗りつぶしモード
	rasterizerDesc.CullMode = D3D11_CULL_NONE;
	rasterizerDesc.FrontCounterClockwise = FALSE;

	DirectX3D::d3d11Device_->CreateRasterizerState(&rasterizerDesc, &rasterizerState);

	//参考： https://learn.microsoft.com/ja-jp/windows/win32/api/d3d11/ns-d3d11-d3d11_texture2d_desc
	D3D11_TEXTURE2D_DESC desc = {};
	desc.Width = width_;
	desc.Height = height_;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	desc.MipLevels = 1;

	std::vector<BYTE> imageData;
	size_t rowBytes = static_cast<size_t>(width_) * 4;
	size_t imageSize = rowBytes * static_cast<size_t>(height_);
	imageData.resize(imageSize);
	result = pConverter->CopyPixels(nullptr, static_cast<UINT>(rowBytes), static_cast<UINT>(imageSize), imageData.data());

	// 参考：https://learn.microsoft.com/ja-jp/windows/win32/api/d3d11/ns-d3d11-d3d11_subresource_data
	D3D11_SUBRESOURCE_DATA textureData = {};
	textureData.pSysMem = imageData.data();
	textureData.SysMemPitch = static_cast<UINT>(rowBytes);
	DirectX3D::d3d11Device_->CreateTexture2D(
		&desc,
		&textureData,
		&DirectX3D::texture2D_
	);

	// 参考： https://learn.microsoft.com/ja-jp/windows/win32/api/d3d11/ns-d3d11-d3d11_shader_resource_view_desc
	D3D11_SHADER_RESOURCE_VIEW_DESC viewDesc = {};
	viewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	viewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	viewDesc.Texture2D.MipLevels = 1;
	DirectX3D::d3d11Device_->CreateShaderResourceView(DirectX3D::texture2D_, &viewDesc, &shaderResourceView_);

	// 参考： https://learn.microsoft.com/ja-jp/windows/win32/api/d3d11/ns-d3d11-d3d11_sampler_desc
	D3D11_SAMPLER_DESC samplerDesc = {};
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	DirectX3D::d3d11Device_->CreateSamplerState(&samplerDesc, &samplerState_);

	// 参考： https://learn.microsoft.com/ja-jp/windows/win32/api/d3d11/ns-d3d11-d3d11_buffer_desc
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(vertices_);
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	// 参考： https://learn.microsoft.com/ja-jp/windows/win32/api/d3d11/ns-d3d11-d3d11_subresource_data
	D3D11_SUBRESOURCE_DATA bufferData = {};
	bufferData.pSysMem = vertices_;

	// 参考： https://learn.microsoft.com/ja-jp/windows/win32/api/d3d11/ns-d3d11-d3d11_buffer_desc
	D3D11_BUFFER_DESC constantBufferDesc = {};
	constantBufferDesc.ByteWidth = sizeof(ConstantBuffer);
	constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	DirectX3D::d3d11Device_->CreateBuffer(&constantBufferDesc, nullptr, &constantBuffer_);

	DirectX3D::d3d11Device_->CreateBuffer(&bufferDesc, &bufferData, &vertexBuffer_);

	float blendFactor[4] = { 0, 0, 0, 0 };

	DirectX3D::d3d11Context_->OMSetBlendState(
		blendState,
		blendFactor,
		0xFFFFFFFF
	);

}

void Image::Update() {
	XMMATRIX scaleMat = XMMatrixScaling(scale_.x, scale_.y, scale_.z);
	XMMATRIX rotMat = XMMatrixRotationZ(rotation_.z) * XMMatrixRotationX(rotation_.x) * XMMatrixRotationY(rotation_.y);
	XMMATRIX transMat = XMMatrixTranslation(postion_.x, postion_.y, postion_.z);
	XMMATRIX world = scaleMat * rotMat * transMat;
	XMMATRIX view = CameraManager::getCurentCamera()->getMatrix();
	XMMATRIX projection = XMMatrixOrthographicOffCenterLH(
		0.0f, 1280.0f,
		720.0f, 0.0f,
		0.0f, 100.0f
	);

	ConstantBuffer cb = {};
	cb.worldViewProj = XMMatrixTranspose(world * view * projection);

	ImGui::Begin("Image");
	ImGui::SliderFloat("X", &postion_.x, -1.0f, 1.0f);
	ImGui::SliderFloat("Y", &postion_.y, -1.0f, 1.0f);
	ImGui::SliderFloat("Z", &postion_.z, -1.0f, 1.0f);
	ImGui::SliderFloat("angleX", &rotation_.x, -1.0f, 1.0f);
	ImGui::SliderFloat("angleY", &rotation_.y, -1.0f, 1.0f);
	ImGui::SliderFloat("angleZ", &rotation_.z, -1.0f, 1.0f);
	ImGui::SliderFloat("scaleX", &scale_.x, 0.5f, 2.0f);
	ImGui::SliderFloat("scaleY", &scale_.y, 0.5f, 2.0f);
	ImGui::SliderFloat("scaleZ", &scale_.z, 0.5f, 2.0f);
	ImGui::End();

	DirectX3D::d3d11Context_->UpdateSubresource(constantBuffer_, 0, nullptr, &cb, 0, 0);
}

void Image::Draw() {
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	DirectX3D::d3d11Context_->IASetInputLayout(DirectX3D::inputLayout);
	DirectX3D::d3d11Context_->IASetVertexBuffers(0, 1, &vertexBuffer_, &stride, &offset);
	DirectX3D::d3d11Context_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	DirectX3D::d3d11Context_->VSSetShader(DirectX3D::vertexShader, nullptr, 0);
	DirectX3D::d3d11Context_->PSSetShader(DirectX3D::pixelShader, nullptr, 0);
	DirectX3D::d3d11Context_->PSSetShaderResources(0, 1, &shaderResourceView_);
	DirectX3D::d3d11Context_->PSSetSamplers(0, 1, &samplerState_);
	DirectX3D::d3d11Context_->VSSetConstantBuffers(0, 1, &constantBuffer_);

	DirectX3D::d3d11Context_->RSSetState(rasterizerState);

	DirectX3D::d3d11Context_->Draw(6, 0);

	DirectX3D::d3d11Context_->RSSetState(nullptr);
}

void Image::Release() {
	if (samplerState_ != nullptr) samplerState_->Release();
	if (shaderResourceView_ != nullptr) shaderResourceView_->Release();
	if (constantBuffer_ != nullptr) constantBuffer_->Release();
	if (vertexBuffer_ != nullptr) vertexBuffer_->Release();
	if (pFactory != nullptr) pFactory->Release();
	if (pDecoder != nullptr) pDecoder->Release();
	if (pFrame != nullptr) pFrame->Release();
	if (pConverter != nullptr) pConverter->Release();
	if (blendState != nullptr) blendState->Release();
	if (rasterizerState != nullptr) rasterizerState->Release();
}
