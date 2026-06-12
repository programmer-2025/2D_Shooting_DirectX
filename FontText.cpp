#include "FontText.h"
#include "DirectX2D.h"

FontText::FontText(std::wstring text)
	: BaseObject("FontText", true) {
	this->text_ = text;
	this -> postion_ = { 0, 0, 0 };
}

FontText::FontText(std::wstring text, DirectX::XMFLOAT3 pos)
	: BaseObject("FontText", true) {
	this->text_ = text;
	this->postion_ = pos;
}

FontText::~FontText()
{
}

void FontText::Init()
{
}

void FontText::Update()
{
}

void FontText::Draw()
{
	D2D1_SIZE_F size = DirectX2D::renderTarget->GetSize();
	DirectX2D::renderTarget->BeginDraw();
	DirectX2D::renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	DirectX2D::renderTarget->DrawTextW(
		text_.c_str(),
		text_.size(),
		DirectX2D::textFormat,
		D2D1::RectF(postion_.x, postion_.y, size.width, size.height),
		DirectX2D::brush
	);

	DirectX2D::renderTarget->EndDraw();
}

void FontText::Release()
{
}
