/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Input.cpp
Purpose: Source file for Input Modle
Project: CS230
Author: Kevin Wright
Creation date: 3/19/2020
-----------------------------------------------------------------*/

#include "Input.h"
#include "Engine.h"

Input::Input() {
	keyDown.resize(static_cast<int>(ButtonType::Count));
	wasKeyDown.resize(static_cast<int>(ButtonType::Count));
}

bool Input::IsKeyDown(ButtonType key) const {
	return keyDown[static_cast<int>(key)];
}

bool Input::IsKeyUp(ButtonType key) const {
	return keyDown[static_cast<int>(key)] == false;
}

bool Input::IsKeyReleased(ButtonType key) const {
	return keyDown[static_cast<int>(key)] == false && wasKeyDown[static_cast<int>(key)] == true;
}

void Input::SetKeyDown(ButtonType key, bool value) { 
	keyDown[static_cast<int>(key)] = value; 
}

void Input::SetMousePos(Vector2DInt newMousePos) {
	mousePos = newMousePos;
}

Vector2DInt Input::GetMousePos() {
	return mousePos;
}

void Input::Update() {
	wasKeyDown = keyDown;
}

Input::InputKey::InputKey(ButtonType button) : button(button) {}

bool Input::InputKey::IsKeyDown() const {
	return Engine::GetInput().IsKeyDown(button);
}

bool Input::InputKey::IsKeyReleased() const {
	return Engine::GetInput().IsKeyReleased(button);
}
