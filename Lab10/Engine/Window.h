/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Window.h
Purpose: Header file for Window
Project: CS230
Author: Kevin Wright
Creation date: 3/19/2020
-----------------------------------------------------------------*/

#pragma once
#include "BasicDataTypes.h"

class Window {
public:
	void Init(std::string windowName);
	void Resize(int newWidth, int newHeight);
	Vector2DInt GetSize();
	void Clear(Color color);
	void Update();
private:
	Vector2DInt screenSize;
};
