#include "FontText.h"
#include "DirectX2D.h"
#include "ImGui/imgui.h"
#include "DirectX3D.h"
using namespace DirectX2D;

FontText::FontText(std::wstring text)
	: BaseObject("FontText", true) {
	this->text_ = text;
	this -> postion_ = { 0, 0, 0 };
	this->fontName_ = L"メイリオ";
	this->fontSize_ = 24.0f;
}

FontText::FontText(std::wstring text, DirectX::XMFLOAT3 pos)
	: BaseObject("FontText", true) {
	this->text_ = text;
	this->postion_ = pos;
	this->fontName_ = L"メイリオ";
	this->fontSize_ = 24.0f;
}

FontText::~FontText()
{
}

void FontText::Init() {
	writeFactory->CreateTextFormat(
		fontName_.c_str(),
		nullptr,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		fontSize_,
		L"",
		&textFormat
	);

	textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	textFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

	D2D1_COLOR_F color = D2D1::ColorF(color_.x, color_.y, color_.z, color_.w);
	renderTarget->CreateSolidColorBrush(color, &brush);
}

void FontText::Update()
{
}

void FontText::Draw()
{
	D2D1_SIZE_F size = DirectX2D::renderTarget->GetSize();
	DirectX2D::renderTarget->BeginDraw();
	D2D1_MATRIX_3X2_F transform_ = D2D1::Matrix3x2F::Scale(scale_.x, scale_.y) * D2D1::Matrix3x2F::Rotation(rotation_.z) * D2D1::Matrix3x2F::Translation(postion_.x, postion_.y);
	DirectX2D::renderTarget->SetTransform(transform_);

	DirectX2D::renderTarget->DrawTextW(
		text_.c_str(),
		text_.size(),
		textFormat,
		D2D1::RectF(postion_.x, postion_.y, size.width, size.height),
		brush
	);

	DirectX2D::renderTarget->EndDraw();

	ImGui::Begin("FontText");
	ImGui::SliderFloat("X", &postion_.x, 0, (int)size.width);
	ImGui::SliderFloat("Y", &postion_.y, -1280, (int)size.height);
	ImGui::SliderFloat("ScaleX", &scale_.x, 0.1f, 5.0f);
	ImGui::SliderFloat("ScaleY", &scale_.y, 0.1f, 5.0f);
	ImGui::End();
}

void FontText::Release()
{
}
