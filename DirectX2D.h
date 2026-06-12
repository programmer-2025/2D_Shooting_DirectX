#pragma once
#include <Windows.h>
#include <d2d1.h>
#include <dwrite.h>

namespace DirectX2D {
	inline ID2D1Factory* factory = nullptr;
	inline IDWriteFactory* writeFactory = nullptr;
	inline ID2D1RenderTarget* renderTarget = nullptr;

	void Init();
}