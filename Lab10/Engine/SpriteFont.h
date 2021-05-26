/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: SpriteFont.h
Purpose: SpriteFont header file
Project: CS230
Author: Kevin Wright
Creation date: 3/21/2020
-----------------------------------------------------------------*/

#pragma once
#include <string>
#include "Texture.h"
#include "BasicDataTypes.h"		//RectInt Vector2DInt Color

class SpriteFont {
public:
	enum class Justified {
		Left,
		CenterX, 
		Right
	};
	SpriteFont(std::string fileName);
	void DrawText(Vector2DInt pos, std::string text, Justified justify, Color color);
	void SetupCharRects(RectInt[], int numOfChars, int yStart, int xStart);
private:
	RectInt &GetCharRect(char c);
	Vector2DInt MeasureText(std::string text);
	void DrawChar(TransformMatrix& matrix, char c);

	Texture texture;
	RectInt numbers[':' - '0' + 1];
};