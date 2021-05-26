/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Texture.h
Purpose: Header file for Texture Module
Project: CS230
Author: Kevin Wright
Creation date: 3/21/2020
-----------------------------------------------------------------*/

#pragma once

#include "doodle/image.hpp"
#include "BasicDataTypes.h"

class TransformMatrix;

class Texture {
public:
	Texture();
	Texture(const std::filesystem::path& filePath);
	void Load(const std::filesystem::path& filePath);
	void Draw(TransformMatrix displayMatrix);
	void Draw(TransformMatrix matrix, Vector2DInt texelPos, Vector2DInt frameSize);
	Vector2DInt GetSize();
	Color GetPixel(Vector2DInt pos);
private:
	doodle::Image image;
	Vector2DInt size;
};
