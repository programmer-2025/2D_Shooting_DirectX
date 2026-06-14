#include "Texture.h"
#include "BaseObject.h"
#include <wincodec.h>
#include <assert.h>
#include <vector>
#include "Input.h"
#include <directxmath.h>
#include "BootScene.h"
#include "ImGUI/imgui.h"
#include "Camera.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;
using namespace DirectX3D;

Texture::Texture(const std::string path, const float leftX, const float leftY)
	: BaseObject("Texture", true) {
	path_ = path;

	// スクリーン座標 → 画像の座標
	vertices_[0] = { {leftX, leftY + 1.0f, 0.0f}, {0,1,0,1}, {0, 0} }; // スクリーン座標: 左下 → 画像の座標: 左上 
	vertices_[1] = { {leftX, leftY, 0.0f }, { 1,0,0,1 }, { 0, 1 } }; // 左上 → 左下
	vertices_[2] = { {leftX + 1.0f, leftY, 0.0f}, {1,1,0,1}, {1, 1} }; // 右上 → 右下

	vertices_[3] = { {leftX + 1.0f, leftY, 0.0f}, {1,0,0,1}, {1, 1 } }; // 右上 → 右下
	vertices_[4] = { {leftX, leftY + 1.0f, 0.0f}, {1,1,0,1}, {0, 0} }; // 左下 → 左上
	vertices_[5] = { {leftX + 1.0f, leftY + 1.0f, 0.0f}, {0,0,1,1}, {1, 0} }; // 右下 → 右上
}

void Texture::Init() {
	static HRESULT result = { 0 };
	IWICImagingFactory* pFactory = nullptr;
	IWICBitmapDecoder* pDecoder = nullptr;
	IWICBitmapFrameDecode* pFrame = nullptr;
	IWICFormatConverter* pConverter = nullptr;
	std::wstring wPath(path_.begin(), path_.end());

	result = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	assert(SUCCEEDED(result));
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

	auto texure2D = GetTexture2D();
	D3D11_SUBRESOURCE_DATA textureData = {};
	textureData.pSysMem = imageData.data();
	textureData.SysMemPitch = static_cast<UINT>(rowBytes);
	GetDXDevice()->CreateTexture2D(
		&desc,
		&textureData,
		&texure2D
	);

	D3D11_SHADER_RESOURCE_VIEW_DESC viewDesc = {};
	viewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	viewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	viewDesc.Texture2D.MipLevels = 1;
	GetDXDevice()->CreateShaderResourceView(texure2D, &viewDesc, &shaderResourceView_);

	D3D11_SAMPLER_DESC samplerDesc = {};
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	GetDXDevice()->CreateSamplerState(&samplerDesc, &samplerState_);

	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(vertices_);
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA bufferData = {};
	bufferData.pSysMem = vertices_;

	D3D11_BUFFER_DESC constantBufferDesc = {};
	constantBufferDesc.ByteWidth = sizeof(ConstantBuffer);
	constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	GetDXDevice()->CreateBuffer(&constantBufferDesc, nullptr, &constantBuffer_);

	GetDXDevice()->CreateBuffer(&bufferDesc, &bufferData, &vertexBuffer_);

}

void Texture::Update() {
	XMMATRIX scaleMat = XMMatrixScaling(scale_.x, scale_.y, scale_.z);
	XMMATRIX rotMat = XMMatrixRotationZ(rotation_.z) * XMMatrixRotationX(rotation_.x) * XMMatrixRotationY(rotation_.y);
	XMMATRIX transMat = XMMatrixTranslation(postion_.x, postion_.y, postion_.z);
	XMMATRIX world = scaleMat * rotMat * transMat;
	XMMATRIX view = CameraManager::getCurentCamera()->getMatrix();
	XMMATRIX projection = DirectX::XMMatrixPerspectiveFovLH(XMConvertToRadians(90.0f), 1280.0f / 720.0f, 0.1f, 100.0f);

	ConstantBuffer cb = {};
	cb.worldViewProj = XMMatrixTranspose(world * view * projection);
	GetDXContext()->UpdateSubresource(constantBuffer_, 0, nullptr, &cb, 0, 0);
}

void Texture::Draw() {
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	GetDXContext()->IASetInputLayout(GetShaderInputType());
	GetDXContext()->IASetVertexBuffers(0, 1, &vertexBuffer_, &stride, &offset);
	GetDXContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	GetDXContext()->VSSetShader(GetVertexShader(VertexShaderType::TEST_VERTEX_SHADER), nullptr, 0);
	GetDXContext()->PSSetShader(GetPixelShader(PixelShaderType::TEST_PIXEL_SHADER), nullptr, 0);
	GetDXContext()->PSSetShaderResources(0, 1, &shaderResourceView_);
	GetDXContext()->PSSetSamplers(0, 1, &samplerState_);
	GetDXContext()->VSSetConstantBuffers(0, 1, &constantBuffer_);

	D3D11_RASTERIZER_DESC rasterizerDesc = {};
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_NONE;
	rasterizerDesc.FrontCounterClockwise = FALSE;
	ID3D11RasterizerState* rasterizerState = nullptr;
	GetDXDevice()->CreateRasterizerState(&rasterizerDesc, &rasterizerState);
	GetDXContext()->RSSetState(rasterizerState);

	//GetDXContext()->Draw(6, 0);

	GetDXContext()->RSSetState(nullptr);
}

void Texture::Release() {
}
