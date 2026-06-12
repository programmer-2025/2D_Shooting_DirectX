#pragma once
#include "BaseObject.h"
#include <string>
#include <dwrite.h>
#include "DirectX2D.h"
#include <Windows.h>
#include <d2d1.h>

/// <summary>
/// インストールされているフォントから描画するクラス。（※凝った文字などは画像での描画を推奨）
/// </summary>
class FontText : public BaseObject {
private:
	std::wstring fontName_;
	std::wstring text_;
	float fontSize_;
	DirectX::XMFLOAT4 color_ = { 0, 0, 0, 1 };
	IDWriteTextFormat* textFormat = nullptr;
	ID2D1SolidColorBrush* brush = nullptr;
public:
	FontText(std::wstring text);
	FontText(std::wstring text, DirectX::XMFLOAT3 pos);
	~FontText();
	void Init() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void SetText(std::wstring text) { text_ = text; }
	void SetPosition(DirectX::XMFLOAT3 pos) { postion_ = pos; }
	void SetColor(DirectX::XMFLOAT4 color) { color_ = color; }
};

