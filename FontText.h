#pragma once
#include "BaseObject.h"

/// <summary>
/// インストールされているフォントから描画するクラス。（※凝った文字などは画像での描画を推奨）
/// </summary>
class FontText : public BaseObject {
private:
	std::wstring text_;
public:
	FontText(std::wstring text);
	FontText(std::wstring text, DirectX::XMFLOAT3 pos);
	~FontText();
	void Init() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

