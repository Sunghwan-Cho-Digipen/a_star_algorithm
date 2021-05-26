/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Texture.cpp
Purpose: source file for Texture Module
Project: CS230
Author: Kevin Wright
Creation date: 3/21/2020
-----------------------------------------------------------------*/

#include "doodle/drawing.hpp"

#include "Texture.h"
#include "TransformMatrix.h"


Texture::Texture() { }

Texture::Texture(const std::filesystem::path& filePath) : image(filePath) {
	size = { image.GetWidth(), image.GetHeight() };
}

void Texture::Load(const std::filesystem::path& filePath) {
	image = doodle::Image { filePath };
	size = { image.GetWidth(), image.GetHeight() };
}

void Texture::Draw(TransformMatrix displayMatrix, Vector2DInt texelPos, Vector2DInt frameSize) {
	doodle::push_settings();
	doodle::apply_matrix(displayMatrix[0][0], displayMatrix[1][0], displayMatrix[0][1], displayMatrix[1][1], displayMatrix[0][2], displayMatrix[1][2]);
	doodle::draw_image(image, 0, 0, static_cast<double>(frameSize.x), static_cast<double>(frameSize.y), texelPos.x, texelPos.y);
	doodle::pop_settings();
}

void Texture::Draw(TransformMatrix displayMatrix) {
	doodle::push_settings();
	doodle::apply_matrix(displayMatrix[0][0], displayMatrix[1][0], displayMatrix[0][1], displayMatrix[1][1], displayMatrix[0][2], displayMatrix[1][2]);
	doodle::draw_image(image, 0, 0);
	doodle::pop_settings();
}

Vector2DInt Texture::GetSize() { return size; }

Color Texture::GetPixel(Vector2DInt pos) {
	int index = pos.y * size.x + pos.x;
	return image[index].red << 24 | image[index].green << 16 | image[index].blue << 8 | image[index].alpha;
}