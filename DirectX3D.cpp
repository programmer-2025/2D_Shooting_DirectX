#include "DirectX3D.h"
#include "framework.h"
#include <assert.h>
#include <d3dcompiler.h>

namespace DirectX3D {
	inline ID3D11Device* d3d11Device_ = nullptr;
	inline ID3D11DeviceContext* d3d11Context_ = nullptr;
	inline IDXGISwapChain* swapChain_ = nullptr;
	inline ID3D11RenderTargetView* renderTargetView_ = nullptr;
	inline ID3D11Texture2D* texture2D_ = nullptr;

	//シェーダー
	inline ID3D11VertexShader* vertexShader = nullptr;
	inline ID3D11PixelShader* pixelShader = nullptr;
	inline ID3D11InputLayout* inputLayout = nullptr;
}

int DirectX3D::initializeDevice(HWND hwnd) {
    DXGI_SWAP_CHAIN_DESC desc = {};
    desc.BufferDesc.Width = Screen::WIDTH;
    desc.BufferDesc.Height = Screen::HEIGHT;
    desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.BufferDesc.RefreshRate.Numerator = 60;
    desc.BufferDesc.RefreshRate.Denominator = 1;

    desc.Windowed = TRUE;
    desc.OutputWindow = hwnd;
    desc.BufferCount = 1;
    desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;

    D3D_FEATURE_LEVEL level = {};
    HRESULT result = {};
    result = D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        D3D11_CREATE_DEVICE_BGRA_SUPPORT,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &desc,
        &swapChain_,
        &d3d11Device_,
        &level,
        &d3d11Context_
    );

    if (FAILED(result)) {
        return -1;
    }

    result = swapChain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&texture2D_);

    if (FAILED(result)) {
        return -1;
    }

    result = d3d11Device_->CreateRenderTargetView(texture2D_, NULL, &renderTargetView_);

    if (FAILED(result)) {
        return -1;
    }

    D3D11_VIEWPORT vp = {};
    vp.Width = Screen::WIDTH;
    vp.Height = Screen::HEIGHT;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;

    d3d11Context_->RSSetViewports(1, &vp);

    return 0;
}

void DirectX3D::initShader() {
	ID3DBlob* vsBlob = nullptr; //頂点シェーダのデータ
	ID3DBlob* psBlob = nullptr; //ピクセルシェーダのデータ
	HRESULT result = {}; //結果を保存するやつ

	//参考：https://learn.microsoft.com/ja-jp/windows/win32/api/d3dcompiler/nf-d3dcompiler-d3dcompilefromfile
	result = D3DCompileFromFile(
		L"TexturePixelShader.hlsl", //シェーダーのファイル
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"main", //シェーダーのメイン関数
		"ps_5_0", //シェーダーの種類（参考：https://learn.microsoft.com/ja-jp/windows/win32/direct3dhlsl/specifying-compiler-targets）
		D3DCOMPILE_ENABLE_STRICTNESS, //シェーダーコンパイルオプション（参考：https://learn.microsoft.com/ja-jp/windows/win32/direct3dhlsl/d3dcompile-constants）
		0, //オプション（参考：https://learn.microsoft.com/ja-jp/windows/win32/direct3dhlsl/d3dcompile-effect-constants）
		&psBlob, //コンパイルしたデータを指定する
		NULL //コンパイル失敗時のデータを保存するやつ
	);

	result = D3DCompileFromFile(
		L"TestVertexShader.hlsl",
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"main",
		"vs_5_0",
		D3DCOMPILE_ENABLE_STRICTNESS,
		0,
		&vsBlob,
		NULL
	);

	result = DirectX3D::d3d11Device_->CreateVertexShader(
		vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(),
		NULL,
		&vertexShader);

	result = DirectX3D::d3d11Device_->CreatePixelShader(
		psBlob->GetBufferPointer(), psBlob->GetBufferSize(),
		NULL,
		&pixelShader);

	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, offsetof(Vertex, postion), D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, offsetof(Vertex, color),    D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{"TEXCOORD",       0, DXGI_FORMAT_R32G32_FLOAT,  0, offsetof(Vertex, uv),    D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	result = DirectX3D::d3d11Device_->CreateInputLayout(
		layout,
		ARRAYSIZE(layout),
		vsBlob->GetBufferPointer(),
		vsBlob->GetBufferSize(),
		&inputLayout
	);
	assert(SUCCEEDED(result));
}

void DirectX3D::release() {
	d3d11Device_->Release();
	d3d11Context_->Release();
    swapChain_->Release();
    renderTargetView_->Release();
    texture2D_->Release();
}

ID3D11Device* DirectX3D::GetDXDevice() {
	return d3d11Device_;
}

ID3D11DeviceContext* DirectX3D::GetDXContext() {
	return d3d11Context_;
}

IDXGISwapChain* DirectX3D::GetSwapChain() {
	return swapChain_;
}

ID3D11RenderTargetView* DirectX3D::GetRenderTargetView() {
	return renderTargetView_;
}

ID3D11Texture2D* DirectX3D::GetTexture2D() {
	return texture2D_;
}

ID3D11InputLayout* DirectX3D::GetShaderInputType() {
	return inputLayout;
}

ID3D11VertexShader* DirectX3D::GetVertexShader(const VertexShaderType type) {
	switch (type) {
	case TEST_VERTEX_SHADER: 
		return vertexShader;
	default:
		return vertexShader;
	}
	return nullptr;
}

ID3D11PixelShader* DirectX3D::GetPixelShader(const PixelShaderType type) {
	switch (type) {
	case TEST_PIXEL_SHADER:
		return pixelShader;
	default:
		return pixelShader;
	}
	return nullptr;
}
