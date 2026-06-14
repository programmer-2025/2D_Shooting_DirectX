#pragma once
#include <Windows.h>
#include <d3d11.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

struct Color {
	float r, g, b, a;


};

struct Vertex {
	DirectX::XMFLOAT3 postion;
	Color color;
	DirectX::XMFLOAT2 uv;
};

enum VertexShaderType {
	TEST_VERTEX_SHADER
};

enum PixelShaderType {
	TEST_PIXEL_SHADER
};

namespace DirectX3D {
	void initShader();
	int initializeDevice(HWND hwnd);
	void release();

	ID3D11Device* GetDXDevice();
	ID3D11DeviceContext* GetDXContext();
	IDXGISwapChain* GetSwapChain();
	ID3D11RenderTargetView* GetRenderTargetView();
	ID3D11Texture2D* GetTexture2D();
	ID3D11InputLayout* GetShaderInputType();

	ID3D11VertexShader* GetVertexShader(const VertexShaderType type);
	ID3D11PixelShader* GetPixelShader(const PixelShaderType type);
	
}