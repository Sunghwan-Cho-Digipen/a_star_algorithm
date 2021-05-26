/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: SpriteFont.cpp
Purpose: SpriteFont source file
Project: CS230
Author: Kevin Wright
Creation date: 3/21/2020
-----------------------------------------------------------------*/

#include "doodle/drawing.hpp"	//set_tint_color

#include "Engine.h"
#include "SpriteFont.h"
#include "TransformMatrix.h"

SpriteFont::SpriteFont(std::string fileName) : texture(fileName), numbers{ 0 } {
	Color white = 0xFFFFFFFF;

	// The top right pixel MUST be white (0xFFFFFFFF)
	Color color = texture.GetPixel({ 0, 0 });
	if (color != white) {
		Engine::GetLogger().LogError("Sprite font " + fileName + " not setup correctly");
		return;
	}

	// Build our rects
	SetupCharRects(numbers, ':' - '0' + 1, 0, 1);
}

void SpriteFont::SetupCharRects(RectInt charRectData[], int numOfChars, int yStart, int xStart) {
	Color testColor = texture.GetPixel({ 0, yStart });
	Color nextColor;
	
	// Measure the height, count the pixels until the next color is not the same
	int height = 0;
	do {
		height++;
		nextColor = texture.GetPixel({ 0, yStart + height + 1 });
	} while (testColor == nextColor);

	int xPos = xStart;
	testColor = texture.GetPixel({ xPos, yStart });
	for (int letter = 0; letter < numOfChars; letter++) {
		// Measure the width, count the pixels until the next color is not the same
		int width = 0;
		do {
			width++;
			nextColor = texture.GetPixel({ xPos + width, yStart });
		} while (testColor == nextColor);

		// Test color becomes our next color, so this we be the color we are using to count
		testColor = nextColor;

		// Set the bottomLeft and topRight for each of our rectangles
		charRectData[letter].topRight = { xPos + width - 1, yStart + 1 };
		charRectData[letter].bottomLeft = { xPos, charRectData[letter].topRight.y + height - 1 };
		xPos += width;
	}
}

RectInt & SpriteFont::GetCharRect(char c) {
	if (c >= '0' && c <= ':') {
		return numbers[c - '0'];
	} else {
		Engine::GetLogger().LogError( "character '" + std::to_string(c) + "' not found in spriteFont");
		return numbers[0];
	}
}

Vector2DInt SpriteFont::MeasureText(std::string text) {
	Vector2DInt size = { 0,0 };
	// For use each characters rect information to find the string size
	for (char c : text) {
		RectInt charRect = GetCharRect(c);
		size.x += GetCharRect(c).Size().x;
		if (charRect.Size().y > size.y) {
			size.y = charRect.Size().y;
		}
	}
	return size;
}

void SpriteFont::DrawText(Vector2DInt pos, std::string text, Justified justify, Color color) {
	TransformMatrix matrix;

	switch (justify) {
	case Justified::Left:
		// The given pos is the bottom left corner of where the text will be written
		matrix *= TranslateMatrix(pos);
		break;
	case Justified::CenterX: 
		// The given pos is the bottom left corner of where the text will be written
		matrix *= TranslateMatrix(Vector2DInt { pos.x - MeasureText(text).x / 2, pos.y });
		break;
	case Justified::Right:
		// The given pos is the bottom right corner of where the text will be written
		matrix *= TranslateMatrix(Vector2DInt { pos.x - MeasureText(text).x, pos.y });
		break;
	}

	// draw in white using the shadow position
	doodle::set_tint_color(doodle::HexColor(color));
	for (char c : text) {
		DrawChar(matrix, c);
	}
	doodle::set_tint_color(doodle::HexColor(0xFFFFFFFF));
}

void SpriteFont::DrawChar(TransformMatrix& matrix, char c) {
	RectInt& displayRect = GetCharRect(c);
	Vector2DInt topLeftTexel = { displayRect.Left(), displayRect.Top() };
	Vector2DInt sizeTexel = { displayRect.Size().x, -displayRect.Size().y };
	if (c != ' ') {
		texture.Draw(matrix, topLeftTexel, sizeTexel);
	}
	matrix *= TranslateMatrix(Vector2DInt{ sizeTexel.x, 0 });
}