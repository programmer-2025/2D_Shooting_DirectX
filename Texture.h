#pragma once
#include "BaseObject.h"
#include <Windows.h>
#include <string>
#include <d3d11.h>
#include "DirectX3D.h"

class Texture : public BaseObject {
private:
	float leftX_, leftY_;
	UINT width_, height_;
	std::string path_;
	ID3D11Buffer* vertexBuffer_;
	ID3D11SamplerState* samplerState_;
	ID3D11ShaderResourceView* shaderResourceView_;
	ID3D11Buffer* constantBuffer_;
	Vertex vertices_[6];
public:
	Texture(std::string path, float leftX, float leftY);
	~Texture() {};
	void Init() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

